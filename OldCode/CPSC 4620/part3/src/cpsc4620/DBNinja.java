package cpsc4620;

import java.io.IOException;
import java.sql.*;
import java.util.*;

/*
 * This file is where you will implement the methods needed to support this application.
 * You will write the code to retrieve and save information to the database and use that
 * information to build the various objects required by the applicaiton.
 * 
 * The class has several hard coded static variables used for the connection, you will need to
 * change those to your connection information
 * 
 * This class also has static string variables for pickup, delivery and dine-in. 
 * DO NOT change these constant values.
 * 
 * You can add any helper methods you need, but you must implement all the methods
 * in this class and use them to complete the project.  The autograder will rely on
 * these methods being implemented, so do not delete them or alter their method
 * signatures.
 * 
 * Make sure you properly open and close your DB connections in any method that
 * requires access to the DB.
 * Use the connect_to_db below to open your connection in DBConnector.
 * What is opened must be closed!
 */

/*
 * A utility class to help add and retrieve information from the database
 */

public final class DBNinja {
	private static Connection conn;

	// DO NOT change these variables!
	public final static String pickup = "pickup";
	public final static String delivery = "delivery";
	public final static String dine_in = "dinein";

	public final static String size_s = "Small";
	public final static String size_m = "Medium";
	public final static String size_l = "Large";
	public final static String size_xl = "XLarge";

	public final static String crust_thin = "Thin";
	public final static String crust_orig = "Original";
	public final static String crust_pan = "Pan";
	public final static String crust_gf = "Gluten-Free";

	public enum order_state {
		PREPARED,
		DELIVERED,
		PICKEDUP
	}


	private static boolean connect_to_db() throws SQLException, IOException 
	{

		try {
			conn = DBConnector.make_connection();
			return true;
		} catch (SQLException e) {
			return false;
		} catch (IOException e) {
			return false;
		}

	}

	public static void addOrder(Order o) throws SQLException, IOException 
	{
		/*
		 * add code to add the order to the DB. Remember that we're not just
		 * adding the order to the order DB table, but we're also recording
		 * the necessary data for the delivery, dinein, pickup, pizzas, toppings
		 * on pizzas, order discounts and pizza discounts.
		 * 
		 * This is a KEY method as it must store all the data in the Order object
		 * in the database and make sure all the tables are correctly linked.
		 * 
		 * Remember, if the order is for Dine In, there is no customer...
		 * so the cusomter id coming from the Order object will be -1.
		 * 
		 */
		connect_to_db(); // Establish connection

		// Query to insert the order into the database
		String orderQuery = "INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete) " +
				"VALUES (?, ?, ?, ?, ?, ?);";

		try {
			PreparedStatement stmt = conn.prepareStatement(orderQuery, Statement.RETURN_GENERATED_KEYS);

			// Handle cases where CustID is -1 (Dine-In Order, no customer)
			if (o.getCustID() == -1) {
				stmt.setNull(1, Types.INTEGER);
			} else {
				stmt.setInt(1, o.getCustID());
			}

			stmt.setString(2, o.getDate());
			stmt.setString(3, o.getOrderType());
			stmt.setDouble(4, o.getCustPrice());
			stmt.setDouble(5, o.getBusPrice());
			stmt.setBoolean(6, o.getIsComplete());
			stmt.executeUpdate();

			// Retrieve the generated OrderID
			ResultSet rs = stmt.getGeneratedKeys();
			int orderID = -1;
			if (rs.next()) {
				orderID = rs.getInt(1);
			}

			// Insert into the appropriate order type table
			if (o.getOrderType().equals(DBNinja.dine_in)) {
				String dineInQuery = "INSERT INTO dinein (ordertable_OrderID, dinein_TableNum) VALUES (?, ?);";
				PreparedStatement dineInStmt = conn.prepareStatement(dineInQuery);
				dineInStmt.setInt(1, orderID);
				dineInStmt.setInt(2, ((DineinOrder) o).getTableNum());
				dineInStmt.executeUpdate();
			} else if (o.getOrderType().equals(DBNinja.delivery)) {
				String deliveryQuery = "INSERT INTO delivery (ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip) " +
						"VALUES (?, ?, ?, ?, ?, ?);";
				PreparedStatement deliveryStmt = conn.prepareStatement(deliveryQuery);

				String[] addressParts = ((DeliveryOrder) o).getAddress().split(" ", 5);
				deliveryStmt.setInt(1, orderID);
				deliveryStmt.setInt(2, Integer.parseInt(addressParts[0]));
				deliveryStmt.setString(3, addressParts[1]);
				deliveryStmt.setString(4, addressParts[2]);
				deliveryStmt.setString(5, addressParts[3]);
				deliveryStmt.setString(6, addressParts[4]);
				deliveryStmt.executeUpdate();
			} else if (o.getOrderType().equals(DBNinja.pickup)) {
				String pickupQuery = "INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp) VALUES (?, ?);";
				PreparedStatement pickupStmt = conn.prepareStatement(pickupQuery);
				pickupStmt.setInt(1, orderID);
				pickupStmt.setBoolean(2, ((PickupOrder) o).getIsPickedUp());
				pickupStmt.executeUpdate();
			}

			// Insert pizzas in the order
			for (Pizza pizza : o.getPizzaList()) {
				DBNinja.addPizza(new java.util.Date(), orderID, pizza);
			}

			// Insert order discounts
			for (Discount discount : o.getDiscountList()) {
				String discountQuery = "INSERT INTO order_discount (ordertable_OrderID, discount_DiscountID) VALUES (?, ?);";
				PreparedStatement discountStmt = conn.prepareStatement(discountQuery);
				discountStmt.setInt(1, orderID);
				discountStmt.setInt(2, discount.getDiscountID());
				discountStmt.executeUpdate();
			}

		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}
	}
	
	public static int addPizza(java.util.Date d, int orderID, Pizza p) throws SQLException, IOException
	{
		/*
		 * Add the code needed to insert the pizza into into the database.
		 * Keep in mind you must also add the pizza discounts and toppings 
		 * associated with the pizza.
		 * 
		 * NOTE: there is a Date object passed into this method so that the Order
		 * and ALL its Pizzas can be assigned the same DTS.
		 * 
		 * This method returns the id of the pizza just added.
		 * 
		 */

		connect_to_db(); // Establish connection

		String pizzaQuery = "INSERT INTO pizza (pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID) " +
				"VALUES (?, ?, ?, ?, ?, ?, ?);";

		try {
			// Insert the pizza details
			PreparedStatement stmt = conn.prepareStatement(pizzaQuery, Statement.RETURN_GENERATED_KEYS);
			stmt.setString(1, p.getCrustType());
			stmt.setString(2, p.getSize());
			stmt.setString(3, p.getPizzaState());
			stmt.setString(4, new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(d));
			stmt.setDouble(5, p.getCustPrice());
			stmt.setDouble(6, p.getBusPrice());
			stmt.setInt(7, orderID);
			stmt.executeUpdate();

			// Retrieve the auto-generated PizzaID
			ResultSet rs = stmt.getGeneratedKeys();
			int pizzaID = -1;
			if (rs.next()) {
				pizzaID = rs.getInt(1);
			}

			// Insert toppings associated with the pizza
			String toppingQuery = "INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble) VALUES (?, ?, ?);";
			PreparedStatement toppingStmt = conn.prepareStatement(toppingQuery);

			for (Topping topping : p.getToppings()) {
				toppingStmt.setInt(1, pizzaID);
				toppingStmt.setInt(2, topping.getTopID());
				toppingStmt.setBoolean(3, false); // Assuming no double toppings initially
				toppingStmt.executeUpdate();
			}

			// Insert discounts associated with the pizza
			String discountQuery = "INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID) VALUES (?, ?);";
			PreparedStatement discountStmt = conn.prepareStatement(discountQuery);

			for (Discount discount : p.getDiscounts()) {
				discountStmt.setInt(1, pizzaID);
				discountStmt.setInt(2, discount.getDiscountID());
				discountStmt.executeUpdate();
			}

			return pizzaID; // Return the generated PizzaID

		} catch (SQLException e) {
			e.printStackTrace();
			return -1; // Return -1 if an exception occurs
		} finally {
			conn.close(); // Ensure the connection is closed
		}
	}
	
	public static int addCustomer(Customer c) throws SQLException, IOException
	 {
		/*
		 * This method adds a new customer to the database.
		 * 
		 */

		 connect_to_db(); // Establish connection
		 String query = "INSERT INTO customer (customer_FName, customer_LName, customer_PhoneNum) VALUES (?, ?, ?);";

		 try {
			 PreparedStatement stmt = conn.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
			 stmt.setString(1, c.getFName());
			 stmt.setString(2, c.getLName());
			 stmt.setString(3, c.getPhone());

			 stmt.executeUpdate();
			 ResultSet rs = stmt.getGeneratedKeys(); // Retrieve the auto-generated CustID
			 if (rs.next()) {
				 return rs.getInt(1); // Return the newly generated customer ID
			 }
		 } catch (SQLException e) {
			 e.printStackTrace(); // Log SQL exceptions for debugging
		 } finally {
			 conn.close(); // Ensure the connection is closed
		 }

		 return -1; // Return -1 if the operation fails
	}

	public static void completeOrder(int OrderID, order_state newState ) throws SQLException, IOException
	{
		/*
		 * Mark that order as complete in the database.
		 * Note: if an order is complete, this means all the pizzas are complete as well.
		 * However, it does not mean that the order has been delivered or picked up!
		 *
		 * For newState = PREPARED: mark the order and all associated pizza's as completed
		 * For newState = DELIVERED: mark the delivery status
		 * FOR newState = PICKEDUP: mark the pickup status
		 * 
		 */
		connect_to_db(); // Establish connection

		try {
			if (newState == order_state.PREPARED) {
				// Mark the order and pizzas as completed
				String orderCompleteQuery = "UPDATE ordertable SET ordertable_IsComplete = 1 WHERE ordertable_OrderID = ?;";
				PreparedStatement orderStmt = conn.prepareStatement(orderCompleteQuery);
				orderStmt.setInt(1, OrderID);
				orderStmt.executeUpdate();

				String pizzaCompleteQuery = "UPDATE pizza SET pizza_PizzaState = 'PREPARED' WHERE ordertable_OrderID = ?;";
				PreparedStatement pizzaStmt = conn.prepareStatement(pizzaCompleteQuery);
				pizzaStmt.setInt(1, OrderID);
				pizzaStmt.executeUpdate();
			} else if (newState == order_state.DELIVERED) {
				// Mark the delivery order as delivered
				String deliveryCompleteQuery = "UPDATE delivery SET delivery_IsDelivered = 1 WHERE ordertable_OrderID = ?;";
				PreparedStatement deliveryStmt = conn.prepareStatement(deliveryCompleteQuery);
				deliveryStmt.setInt(1, OrderID);
				deliveryStmt.executeUpdate();
			} else if (newState == order_state.PICKEDUP) {
				// Mark the pickup order as picked up
				String pickupCompleteQuery = "UPDATE pickup SET pickup_IsPickedUp = 1 WHERE ordertable_OrderID = ?;";
				PreparedStatement pickupStmt = conn.prepareStatement(pickupCompleteQuery);
				pickupStmt.setInt(1, OrderID);
				pickupStmt.executeUpdate();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}
	}

	//Helpers for getOrders
	private static int getDineinTableNum(int orderID) throws SQLException {
		String query = "SELECT dinein_TableNum FROM dinein WHERE ordertable_OrderID = ?;";
		PreparedStatement stmt = conn.prepareStatement(query);
		stmt.setInt(1, orderID);
		ResultSet rs = stmt.executeQuery();
		if (rs.next()) {
			return rs.getInt("dinein_TableNum");
		}
		return -1; // Return -1 if no table number is found
	}

	private static String getDeliveryAddress(int orderID) throws SQLException {
		String query = "SELECT delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip FROM delivery WHERE ordertable_OrderID = ?;";
		PreparedStatement stmt = conn.prepareStatement(query);
		stmt.setInt(1, orderID);
		ResultSet rs = stmt.executeQuery();
		if (rs.next()) {
			return rs.getInt("delivery_HouseNum") + " " +
					rs.getString("delivery_Street") + " " +
					rs.getString("delivery_City") + " " +
					rs.getString("delivery_State") + " " +
					rs.getInt("delivery_Zip");
		}
		return null; // Return null if no address is found
	}

	private static boolean getPickupStatus(int orderID) throws SQLException {
		String query = "SELECT pickup_IsPickedUp FROM pickup WHERE ordertable_OrderID = ?;";
		PreparedStatement stmt = conn.prepareStatement(query);
		stmt.setInt(1, orderID);
		ResultSet rs = stmt.executeQuery();
		if (rs.next()) {
			return rs.getBoolean("pickup_IsPickedUp");
		}
		return false; // Return false if no status is found
	}

	public static ArrayList<Order> getOrders(int status) throws SQLException, IOException
	 {
	/*
	 * Return an ArrayList of orders.
	 * 	status   == 1 => return a list of open (ie oder is not completed)
	 *           == 2 => return a list of completed orders (ie order is complete)
	 *           == 3 => return a list of all the orders
	 * Remember that in Java, we account for supertypes and subtypes
	 * which means that when we create an arrayList of orders, that really
	 * means we have an arrayList of dineinOrders, deliveryOrders, and pickupOrders.
	 *
	 * You must fully populate the Order object, this includes order discounts,
	 * and pizzas along with the toppings and discounts associated with them.
	 * 
	 * Don't forget to order the data coming from the database appropriately.
	 *
	 */
		 ArrayList<Order> orders = new ArrayList<>();
		 connect_to_db(); // Establish connection

		 String query;
		 if (status == 1) {
			 query = "SELECT * FROM ordertable WHERE ordertable_IsComplete = 0 ORDER BY ordertable_OrderDateTime;";
		 } else if (status == 2) {
			 query = "SELECT * FROM ordertable WHERE ordertable_IsComplete = 1 ORDER BY ordertable_OrderDateTime;";
		 } else {
			 query = "SELECT * FROM ordertable ORDER BY ordertable_OrderDateTime;";
		 }

		 try {
			 Statement stmt = conn.createStatement();
			 ResultSet rs = stmt.executeQuery(query);

			 while (rs.next()) {
				 int orderID = rs.getInt("ordertable_OrderID");
				 int custID = rs.getInt("customer_CustID");
				 String orderType = rs.getString("ordertable_OrderType");
				 String date = rs.getString("ordertable_OrderDateTime");
				 double custPrice = rs.getDouble("ordertable_CustPrice");
				 double busPrice = rs.getDouble("ordertable_BusPrice");
				 boolean isComplete = rs.getBoolean("ordertable_IsComplete");

				 Order order;
				 if (orderType.equals("dinein")) {
					 int tableNum = getDineinTableNum(orderID);
					 order = new DineinOrder(orderID, custID, date, custPrice, busPrice, isComplete, tableNum);
				 } else if (orderType.equals("delivery")) {
					 String address = getDeliveryAddress(orderID);
					 order = new DeliveryOrder(orderID, custID, date, custPrice, busPrice, isComplete, address);
				 } else {
					 boolean isPickedUp = getPickupStatus(orderID);
					 order = new PickupOrder(orderID, custID, date, custPrice, busPrice, isComplete, isPickedUp);
				 }

				 order.setPizzaList(getPizzas(order));
				 order.setDiscountList(getDiscounts(order));
				 orders.add(order);
			 }
		 } catch (SQLException e) {
			 e.printStackTrace();
		 } finally {
			 conn.close(); // Close the connection
		 }

		 return orders;
	}
	
	public static Order getLastOrder() throws SQLException, IOException 
	{
		/*
		 * Query the database for the LAST order added
		 * then return an Order object for that order.
		 * NOTE...there will ALWAYS be a "last order"!
		 */
		connect_to_db(); // Establish connection

		Order lastOrder = null;

		String query = "SELECT * FROM ordertable ORDER BY ordertable_OrderDateTime DESC LIMIT 1;";

		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			if (rs.next()) {
				int orderID = rs.getInt("ordertable_OrderID");
				int custID = rs.getInt("customer_CustID");
				String orderType = rs.getString("ordertable_OrderType");
				String date = rs.getString("ordertable_OrderDateTime");
				double custPrice = rs.getDouble("ordertable_CustPrice");
				double busPrice = rs.getDouble("ordertable_BusPrice");
				boolean isComplete = rs.getBoolean("ordertable_IsComplete");

				// Determine the order subtype
				if (orderType.equals("dinein")) {
					int tableNum = getDineinTableNum(orderID);
					lastOrder = new DineinOrder(orderID, custID, date, custPrice, busPrice, isComplete, tableNum);
				} else if (orderType.equals("delivery")) {
					String address = getDeliveryAddress(orderID);
					lastOrder = new DeliveryOrder(orderID, custID, date, custPrice, busPrice, isComplete, address);
				} else {
					boolean isPickedUp = getPickupStatus(orderID);
					lastOrder = new PickupOrder(orderID, custID, date, custPrice, busPrice, isComplete, isPickedUp);
				}

				// Attach pizzas and discounts
				lastOrder.setPizzaList(getPizzas(lastOrder));
				lastOrder.setDiscountList(getDiscounts(lastOrder));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return lastOrder;
	}

	public static ArrayList<Order> getOrdersByDate(String date) throws SQLException, IOException
	 {
		/*
		 * Query the database for ALL the orders placed on a specific date
		 * and return a list of those orders.
		 *  
		 */
		 ArrayList<Order> orders = new ArrayList<>();
		 connect_to_db(); // Establish connection

		 String query = "SELECT * FROM ordertable WHERE DATE(ordertable_OrderDateTime) = ? ORDER BY ordertable_OrderDateTime;";

		 try {
			 PreparedStatement stmt = conn.prepareStatement(query);
			 stmt.setString(1, date); // Format: "YYYY-MM-DD"
			 ResultSet rs = stmt.executeQuery();

			 while (rs.next()) {
				 int orderID = rs.getInt("ordertable_OrderID");
				 int custID = rs.getInt("customer_CustID");
				 String orderType = rs.getString("ordertable_OrderType");
				 String orderDate = rs.getString("ordertable_OrderDateTime");
				 double custPrice = rs.getDouble("ordertable_CustPrice");
				 double busPrice = rs.getDouble("ordertable_BusPrice");
				 boolean isComplete = rs.getBoolean("ordertable_IsComplete");

				 Order order;
				 if (orderType.equals("dinein")) {
					 int tableNum = getDineinTableNum(orderID);
					 order = new DineinOrder(orderID, custID, orderDate, custPrice, busPrice, isComplete, tableNum);
				 } else if (orderType.equals("delivery")) {
					 String address = getDeliveryAddress(orderID);
					 order = new DeliveryOrder(orderID, custID, orderDate, custPrice, busPrice, isComplete, address);
				 } else {
					 boolean isPickedUp = getPickupStatus(orderID);
					 order = new PickupOrder(orderID, custID, orderDate, custPrice, busPrice, isComplete, isPickedUp);
				 }

				 // Attach pizzas and discounts
				 order.setPizzaList(getPizzas(order));
				 order.setDiscountList(getDiscounts(order));
				 orders.add(order);
			 }
		 } catch (SQLException e) {
			 e.printStackTrace();
		 } finally {
			 conn.close(); // Close the connection
		 }

		 return orders;
	}
		
	public static ArrayList<Discount> getDiscountList() throws SQLException, IOException 
	{
		/* 
		 * Query the database for all the available discounts and 
		 * return them in an arrayList of discounts ordered by discount name.
		 * 
		*/
		ArrayList<Discount> discounts = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM discount ORDER BY discount_DiscountName;";

		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			while (rs.next()) {
				int discountID = rs.getInt("discount_DiscountID");
				String discountName = rs.getString("discount_DiscountName");
				double amount = rs.getDouble("discount_Amount");
				boolean isPercent = rs.getBoolean("discount_IsPercent");

				Discount discount = new Discount(discountID, discountName, amount, isPercent);
				discounts.add(discount);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return discounts;
	}

	public static Discount findDiscountByName(String name) throws SQLException, IOException 
	{
		/*
		 * Query the database for a discount using it's name.
		 * If found, then return an OrderDiscount object for the discount.
		 * If it's not found....then return null
		 *  
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM discount WHERE discount_DiscountName = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, name);
			ResultSet rs = stmt.executeQuery();

			if (rs.next()) {
				int discountID = rs.getInt("discount_DiscountID");
				String discountName = rs.getString("discount_DiscountName");
				double amount = rs.getDouble("discount_Amount");
				boolean isPercent = rs.getBoolean("discount_IsPercent");

				return new Discount(discountID, discountName, amount, isPercent);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return null; // Return null if no discount is found
	}


	public static ArrayList<Customer> getCustomerList() throws SQLException, IOException 
	{
		/*
		 * Query the data for all the customers and return an arrayList of all the customers. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		*/
		ArrayList<Customer> customers = new ArrayList<>();
		connect_to_db(); // Establish database connection

		String query = "SELECT customer_CustID, customer_FName, customer_LName, customer_PhoneNum FROM customer ORDER BY customer_LName, customer_FName;";

		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			while (rs.next()) {
				int custID = rs.getInt("customer_CustID");
				String fName = rs.getString("customer_FName");
				String lName = rs.getString("customer_LName");
				String phone = rs.getString("customer_PhoneNum");

				Customer customer = new Customer(custID, fName, lName, phone);
				customers.add(customer);
			}
		} catch (SQLException e) {
			e.printStackTrace(); // Handle SQL exceptions
		} finally {
			conn.close(); // Close the connection
		}

		return customers;
	}

	public static Customer findCustomerByPhone(String phoneNumber)  throws SQLException, IOException 
	{
		/*
		 * Query the database for a customer using a phone number.
		 * If found, then return a Customer object for the customer.
		 * If it's not found....then return null
		 *  
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM customer WHERE customer_PhoneNum = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, phoneNumber);
			ResultSet rs = stmt.executeQuery();

			if (rs.next()) {
				int custID = rs.getInt("customer_CustID");
				String fName = rs.getString("customer_FName");
				String lName = rs.getString("customer_LName");

				return new Customer(custID, fName, lName, phoneNumber);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return null; // Return null if no customer is found
	}

	public static String getCustomerName(int CustID) throws SQLException, IOException 
	{
		/*
		 * COMPLETED...WORKING Example!
		 * 
		 * This is a helper method to fetch and format the name of a customer
		 * based on a customer ID. This is an example of how to interact with
		 * your database from Java.  
		 * 
		 * Notice how the connection to the DB made at the start of the 
		 *
		 */

		 connect_to_db();

		/* 
		 * an example query using a constructed string...
		 * remember, this style of query construction could be subject to sql injection attacks!
		 * 
		 */
		String cname1 = "";
		String cname2 = "";
		String query = "Select customer_FName, customer_LName From customer WHERE customer_CustID=" + CustID + ";";
		Statement stmt = conn.createStatement();
		ResultSet rset = stmt.executeQuery(query);
		
		while(rset.next())
		{
			cname1 = rset.getString(1) + " " + rset.getString(2); 
		}

		/* 
		* an BETTER example of the same query using a prepared statement...
		* with exception handling
		* 
		*/
		try {
			PreparedStatement os;
			ResultSet rset2;
			String query2;
			query2 = "Select customer_FName, customer_LName From customer WHERE customer_CustID=?;";
			os = conn.prepareStatement(query2);
			os.setInt(1, CustID);
			rset2 = os.executeQuery();
			while(rset2.next())
			{
				cname2 = rset2.getString("customer_FName") + " " + rset2.getString("customer_LName"); // note the use of field names in the getSting methods
			}
		} catch (SQLException e) {
			e.printStackTrace();
			// process the error or re-raise the exception to a higher level
		}

		conn.close();

		return cname1;
		// OR
		// return cname2;

	}


	public static ArrayList<Topping> getToppingList() throws SQLException, IOException 
	{
		/*
		 * Query the database for the aviable toppings and 
		 * return an arrayList of all the available toppings. 
		 * Don't forget to order the data coming from the database appropriately.
		 * 
		 */
		ArrayList<Topping> toppings = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM topping ORDER BY topping_TopName;";

		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			while (rs.next()) {
				int toppingID = rs.getInt("topping_TopID");
				String name = rs.getString("topping_TopName");
				double smallAmt = rs.getDouble("topping_SmallAMT");
				double medAmt = rs.getDouble("topping_MedAMT");
				double lgAmt = rs.getDouble("topping_LgAMT");
				double xlAmt = rs.getDouble("topping_XLAMT");
				double busPrice = rs.getDouble("topping_BusPrice");
				double custPrice = rs.getDouble("topping_CustPrice");
				int minINVT = rs.getInt("topping_MinINVT");
				int curINVT = rs.getInt("topping_CurINVT");

				Topping topping = new Topping(toppingID, name, smallAmt, medAmt, lgAmt, xlAmt, busPrice, custPrice, minINVT, curINVT);
				toppings.add(topping);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return toppings;
	}

	public static Topping findToppingByName(String name) throws SQLException, IOException 
	{
		/*
		 * Query the database for the topping using it's name.
		 * If found, then return a Topping object for the topping.
		 * If it's not found....then return null
		 *  
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM topping WHERE topping_TopName = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, name);
			ResultSet rs = stmt.executeQuery();

			if (rs.next()) {
				int toppingID = rs.getInt("topping_TopID");
				double smallAmt = rs.getDouble("topping_SmallAMT");
				double medAmt = rs.getDouble("topping_MedAMT");
				double lgAmt = rs.getDouble("topping_LgAMT");
				double xlAmt = rs.getDouble("topping_XLAMT");
				double custPrice = rs.getDouble("topping_BusPrice");
				double busPrice = rs.getDouble("topping_CustPrice");
				int minINVT = rs.getInt("topping_MinINVT");
				int curINVT = rs.getInt("topping_CurINVT");

				return new Topping(toppingID, name, smallAmt, medAmt, lgAmt, xlAmt, busPrice, custPrice, minINVT, curINVT);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return null; // Return null if no topping is found
	}

	public static ArrayList<Topping> getToppingsOnPizza(Pizza p) throws SQLException, IOException 
	{
		/* 
		 * This method builds an ArrayList of the toppings ON a pizza.
		 * The list can then be added to the Pizza object elsewhere in the
		 */

		ArrayList<Topping> toppings = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT t.* FROM pizza_topping pt " +
				"JOIN topping t ON pt.topping_TopID = t.topping_TopID " +
				"WHERE pt.pizza_PizzaID = ?;";

		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setInt(1, p.getPizzaID());
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				int toppingID = rs.getInt("topping_TopID");
				String name = rs.getString("topping_TopName");
				double smallAmt = rs.getDouble("topping_SmallAMT");
				double medAmt = rs.getDouble("topping_MedAMT");
				double lgAmt = rs.getDouble("topping_LgAMT");
				double xlAmt = rs.getDouble("topping_XLAMT");
				double busPrice = rs.getDouble("topping_BusPrice");
				double custPrice = rs.getDouble("topping_CustPrice");
				int minINVT = rs.getInt("topping_MinINVT");
				int curINVT = rs.getInt("topping_CurINVT");

				Topping topping = new Topping(toppingID, name, smallAmt, medAmt, lgAmt, xlAmt, busPrice, custPrice, minINVT, curINVT);
				toppings.add(topping);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return toppings;
	}

	public static void addToInventory(int toppingID, double quantity) throws SQLException, IOException 
	{
		/*
		 * Updates the quantity of the topping in the database by the amount specified.
		 * 
		 * */
		connect_to_db(); // Establish connection

		String query = "UPDATE topping SET topping_CurINVT = topping_CurINVT + ? WHERE topping_TopID = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setDouble(1, quantity); // Amount to add to the current inventory
			stmt.setInt(2, toppingID); // Topping ID to update
			stmt.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace(); // Handle SQL exception
		} finally {
			conn.close(); // Close the connection
		}
	}
	
	
	public static ArrayList<Pizza> getPizzas(Order o) throws SQLException, IOException 
	{
		/*
		 * Build an ArrayList of all the Pizzas associated with the Order.
		 * 
		 */
		ArrayList<Pizza> pizzas = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM pizza WHERE ordertable_OrderID = ?;";

		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setInt(1, o.getOrderID());
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				int pizzaID = rs.getInt("pizza_PizzaID");
				String size = rs.getString("pizza_Size");
				String crustType = rs.getString("pizza_CrustType");
				int orderID = rs.getInt("ordertable_OrderID"); // Matches the constructor's fourth argument
				String state = rs.getString("pizza_PizzaState");
				String date = rs.getString("pizza_PizzaDate");
				double custPrice = rs.getDouble("pizza_CustPrice");
				double busPrice = rs.getDouble("pizza_BusPrice");

				// Create the Pizza object with corrected parameter order
				Pizza pizza = new Pizza(pizzaID, size, crustType, orderID, state, date, custPrice, busPrice);

				// Retrieve toppings and attach them
				ArrayList<Topping> toppings = getToppingsOnPizza(pizza);
				pizza.setToppings(toppings); // Method exists in the Pizza class

				// Retrieve discounts and attach them
				ArrayList<Discount> discounts = getDiscounts(pizza); // Overloaded getDiscounts for Pizza
				pizza.setDiscounts(discounts); // Method exists in the Pizza class

				pizzas.add(pizza);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return pizzas;
	}

	public static ArrayList<Discount> getDiscounts(Order o) throws SQLException, IOException 
	{
		/* 
		 * Build an array list of all the Discounts associted with the Order.
		 * 
		 */

		ArrayList<Discount> discounts = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT d.* FROM order_discount od " +
				"JOIN discount d ON od.discount_DiscountID = d.discount_DiscountID " +
				"WHERE od.ordertable_OrderID = ?;";

		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setInt(1, o.getOrderID());
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				int discountID = rs.getInt("discount_DiscountID");
				String discountName = rs.getString("discount_DiscountName");
				double amount = rs.getDouble("discount_Amount");
				boolean isPercent = rs.getBoolean("discount_IsPercent");

				Discount discount = new Discount(discountID, discountName, amount, isPercent);
				discounts.add(discount);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return discounts;
	}

	public static ArrayList<Discount> getDiscounts(Pizza p) throws SQLException, IOException 
	{
		/* 
		 * Build an array list of all the Discounts associted with the Pizza.
		 * 
		 */

		ArrayList<Discount> discounts = new ArrayList<>();
		connect_to_db(); // Establish connection

		String query = "SELECT d.* FROM pizza_discount pd " +
				"JOIN discount d ON pd.discount_DiscountID = d.discount_DiscountID " +
				"WHERE pd.pizza_PizzaID = ?;";

		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setInt(1, p.getPizzaID());
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				int discountID = rs.getInt("discount_DiscountID");
				String discountName = rs.getString("discount_DiscountName");
				double amount = rs.getDouble("discount_Amount");
				boolean isPercent = rs.getBoolean("discount_IsPercent");

				Discount discount = new Discount(discountID, discountName, amount, isPercent);
				discounts.add(discount);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return discounts;
	}

	public static double getBaseCustPrice(String size, String crust) throws SQLException, IOException 
	{
		/* 
		 * Query the database fro the base customer price for that size and crust pizza.
		 * 
		*/
		connect_to_db(); // Establish connection

		String query = "SELECT baseprice_CustPrice FROM baseprice WHERE baseprice_Size = ? AND baseprice_CrustType = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, size);
			stmt.setString(2, crust);
			ResultSet rs = stmt.executeQuery();

			if (rs.next()) {
				return rs.getDouble("baseprice_CustPrice");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return 0.0; // Return 0.0 if the query fails
	}

	public static double getBaseBusPrice(String size, String crust) throws SQLException, IOException 
	{
		/* 
		 * Query the database fro the base business price for that size and crust pizza.
		 * 
		*/
		connect_to_db(); // Establish connection

		String query = "SELECT baseprice_BusPrice FROM baseprice WHERE baseprice_Size = ? AND baseprice_CrustType = ?;";
		try {
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, size);
			stmt.setString(2, crust);
			ResultSet rs = stmt.executeQuery();

			if (rs.next()) {
				return rs.getDouble("baseprice_BusPrice");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}

		return 0.0; // Return 0.0 if the query fails
	}

	
	public static void printToppingPopReport() throws SQLException, IOException
	{
		/*
		 * Prints the ToppingPopularity view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT * FROM ToppingPopularity ORDER BY ToppingName;";
		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			// Print the header
			System.out.printf("%-20s %-20s\n", "Topping", "Topping Count");
			System.out.printf("%-20s %-20s\n", "-------", "-------------");

			// Print each row of the report
			while (rs.next()) {
				String toppingName = rs.getString("ToppingName");
				int popularity = rs.getInt("Popularity");
				System.out.printf("%-20s %-20d\n", toppingName, popularity);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}
	}
	
	public static void printProfitByPizzaReport() throws SQLException, IOException 
	{
		/*
		 * Prints the ProfitByPizza view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 * 
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT PizzaSize, PizzaCrust, Profit, LastOrderDate FROM ProfitByPizza ORDER BY LastOrderDate;";
		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			// Print the header
			System.out.printf("%-20s %-20s %-20s %-20s\n", "Pizza Size", "Pizza Crust", "Profit", "Last Order Date");
			System.out.printf("%-20s %-20s %-20s %-20s\n", "----------", "-----------", "------", "---------------");

			// Print each row of the report
			while (rs.next()) {
				String size = rs.getString("PizzaSize");
				String crust = rs.getString("PizzaCrust");
				double profit = rs.getDouble("Profit");
				String lastOrderDate = rs.getString("LastOrderDate");

				System.out.printf("%-20s %-20s $%-19.2f %-20s\n", size, crust, profit, lastOrderDate);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}
	}
	
	public static void printProfitByOrderType() throws SQLException, IOException
	{
		/*
		 * Prints the ProfitByOrderType view. Remember that this view
		 * needs to exist in your DB, so be sure you've run your createViews.sql
		 * files on your testing DB if you haven't already.
		 * 
		 * The result should be readable and sorted as indicated in the prompt.
		 *
		 * HINT: You need to match the expected output EXACTLY....I would suggest
		 * you look at the printf method (rather that the simple print of println).
		 * It operates the same in Java as it does in C and will make your code
		 * better.
		 * 
		 */
		connect_to_db(); // Establish connection

		String query = "SELECT CustomerType, OrderMonth, SUM(TotalOrderPrice) AS TotalOrderPrice, " +
				"SUM(TotalOrderCost) AS TotalOrderCost, SUM(Profit) AS Profit " +
				"FROM ProfitByOrderType GROUP BY CustomerType, OrderMonth " +
				"WITH ROLLUP ORDER BY CustomerType, OrderMonth;";
		try {
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);

			// Print the header
			System.out.printf("%-20s %-15s %-20s %-20s %-10s\n", "Customer Type", "Order Month", "Total Order Price", "Total Order Cost", "Profit");
			System.out.printf("%-20s %-15s %-20s %-20s %-10s\n", "-------------", "-----------", "-----------------", "----------------", "------");

			// Variables to track grand totals
			double grandTotalOrderPrice = 0.0;
			double grandTotalOrderCost = 0.0;
			double grandTotalProfit = 0.0;

			// Print each row of the report
			while (rs.next()) {
				String customerType = rs.getString("CustomerType");
				String orderMonth = rs.getString("OrderMonth");
				double totalOrderPrice = rs.getDouble("TotalOrderPrice");
				double totalOrderCost = rs.getDouble("TotalOrderCost");
				double profit = rs.getDouble("Profit");

				// Check if it's a grand total row (ROLLUP)
				if (customerType == null) {
					System.out.printf("%-20s %-15s $%-19.2f $%-19.2f $%-9.2f\n", "", "Grand Total", totalOrderPrice, totalOrderCost, profit);
					grandTotalOrderPrice += totalOrderPrice;
					grandTotalOrderCost += totalOrderCost;
					grandTotalProfit += profit;
				} else {
					System.out.printf("%-20s %-15s $%-19.2f $%-19.2f $%-9.2f\n", customerType, orderMonth, totalOrderPrice, totalOrderCost, profit);
				}
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			conn.close(); // Close the connection
		}
	}
	
	
	
	/*
	 * These private methods help get the individual components of an SQL datetime object. 
	 * You're welcome to keep them or remove them....but they are usefull!
	 */
	private static int getYear(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(0,4));
	}
	private static int getMonth(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(5, 7));
	}
	private static int getDay(String date)// assumes date format 'YYYY-MM-DD HH:mm:ss'
	{
		return Integer.parseInt(date.substring(8, 10));
	}

	public static boolean checkDate(int year, int month, int day, String dateOfOrder)
	{
		if(getYear(dateOfOrder) > year)
			return true;
		else if(getYear(dateOfOrder) < year)
			return false;
		else
		{
			if(getMonth(dateOfOrder) > month)
				return true;
			else if(getMonth(dateOfOrder) < month)
				return false;
			else
			{
				if(getDay(dateOfOrder) >= day)
					return true;
				else
					return false;
			}
		}
	}


}