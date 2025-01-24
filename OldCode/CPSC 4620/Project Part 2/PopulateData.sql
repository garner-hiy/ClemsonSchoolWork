
INSERT INTO baseprice (baseprice_Size, baseprice_CrustType, baseprice_CustPrice, baseprice_BusPrice)
VALUES
('small', 'Thin', 3.00, 0.50),
('small', 'Original', 3.00, 0.75),
('small', 'Pan', 3.50, 1.00),
('small', 'Gluten-Free', 4.00, 2.00),
('medium', 'Thin', 5.00, 1.00),
('medium', 'Original', 5.00, 1.50),
('medium', 'Pan', 6.00, 2.25),
('medium', 'Gluten-Free', 6.25, 3.00),
('Large', 'Thin', 8.00, 1.25),
('Large', 'Original', 8.00, 2.00),
('Large', 'Pan', 9.00, 3.00),
('Large', 'Gluten-Free', 9.50, 4.00),
('XLarge', 'Thin', 10.00, 2.00),
('XLarge', 'Original', 10.00, 3.00),
('XLarge', 'Pan', 11.50, 4.50),
('XLarge', 'Gluten-Free', 12.50, 6.00);

INSERT INTO topping (topping_TopName, topping_SmallAMT, topping_MedAMT, topping_LgAMT, topping_XLAMT, topping_CustPrice, topping_BusPrice, topping_MinINVT, topping_CurINVT)
VALUES
('Pepperoni', 2.00, 2.75, 3.50, 4.50, 1.25, 0.20, 50, 100),
('Sausage', 2.50, 3.00, 3.50, 4.25, 1.25, 0.15, 50, 100),
('Ham', 2.00, 2.50, 3.25, 4.00, 1.50, 0.15, 25, 78),
('Chicken', 1.50, 2.00, 2.25, 3.00, 1.75, 0.25, 25, 56),
('Green Pepper', 1.00, 1.50, 2.00, 2.50, 0.50, 0.02, 25, 79),
('Onion', 1.00, 1.50, 2.00, 2.75, 0.50, 0.02, 25, 85),
('Roma Tomato', 2.00, 3.00, 3.50, 4.50, 0.75, 0.03, 10, 86),
('Mushrooms', 1.50, 2.00, 2.50, 3.00, 0.75, 0.10, 50, 52),
('Black Olives', 0.75, 1.00, 1.50, 2.00, 0.60, 0.10, 25, 39),
('Pineapple', 1.00, 1.25, 1.75, 2.00, 1.00, 0.25, 0, 15),
('Jalapenos', 0.50, 0.75, 1.25, 1.75, 0.50, 0.05, 0, 64),
('Banana Peppers', 0.60, 1.00, 1.30, 1.75, 0.50, 0.05, 0, 36),
('Regular Cheese', 2.00, 3.50, 5.00, 7.00, 0.50, 0.12, 50, 250),
('Four Cheese Blend', 2.00, 3.50, 5.00, 7.00, 1.00, 0.15, 25, 150),
('Feta Cheese', 1.75, 3.00, 4.00, 5.50, 1.50, 0.18, 0, 75),
('Goat Cheese', 1.60, 2.75, 4.00, 5.50, 1.50, 0.20, 0, 54),
('Bacon', 1.00, 1.50, 2.00, 3.00, 1.50, 0.25, 0, 89);

INSERT INTO discount (discount_DiscountName, discount_Amount, discount_IsPercent)
VALUES
('Employee', 15.00, 1),
('Lunch Special Medium', 1.00, 0),
('Lunch Special Large', 2.00, 0),
('Specialty Pizza', 1.50, 0),
('Happy Hour', 10.00, 1),
('Gameday Special', 20.00, 1);


INSERT INTO customer (customer_FName, customer_LName, customer_PhoneNum)
VALUES
('Andrew', 'Wilkes-Krier', '8642545861'),
('Matt', 'Engers', '8644749953'),
('Frank', 'Turner', '8642328944'),
('Milo', 'Auckerman', '8648785679');


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (NULL, '2024-03-05 12:03:00', 'dinein', 19.75, 3.68, 1);
INSERT INTO dinein (ordertable_OrderID, dinein_TableNum) VALUES (1, 21);
INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (1, 'Thin', 'Large', 'Completed', '2024-03-05 12:03:00', 19.75, 3.68, 1);
INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES (1, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Regular Cheese'), 1),
       (1, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Pepperoni'), 0),
       (1, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Sausage'), 0);
INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID)
VALUES (1, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Lunch Special Large'));



INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES (NULL, '2024-04-03 12:05:00', 'dinein', 19.78, 4.63, 1);
INSERT INTO dinein (ordertable_OrderID, dinein_TableNum) VALUES (2, 4);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (2, 'Pan', 'Medium', 'Completed', '2024-04-03 12:05:00', 12.85, 3.23, 2);
INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES (2, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Feta Cheese'), 0),
       (2, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Black Olives'), 0),
       (2, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Roma Tomato'), 0),
       (2, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Mushrooms'), 0),
       (2, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Banana Peppers'), 0);
INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID)
VALUES (2, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Lunch Special Medium')),
       (2, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Specialty Pizza'));

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (3, 'Original', 'Small', 'Completed', '2024-04-03 12:05:00', 6.93, 1.40, 2);
INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble

)
VALUES (3, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Regular Cheese'), 0),
       (3, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Chicken'), 0),
       (3, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Banana Peppers'), 0);


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES ((SELECT customer_CustID FROM customer WHERE customer_FName = 'Andrew' AND customer_LName = 'Wilkes-Krier'), '2024-03-03 21:30:00', 'pickup', 89.28, 19.80, 1);
INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp) VALUES (3, 1);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES
(4, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3),
(5, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3),
(6, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3),
(7, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3),
(8, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3),
(9, 'Original', 'Large', 'Completed', '2024-03-03 21:30:00', 14.88, 3.30, 3);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
SELECT pizza_PizzaID, topping_TopID, 0 FROM pizza, topping WHERE topping_TopName = 'Regular Cheese' AND pizza_PizzaID BETWEEN 4 AND 9;
INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
SELECT pizza_PizzaID, topping_TopID, 0 FROM pizza, topping WHERE topping_TopName = 'Pepperoni' AND pizza_PizzaID BETWEEN 4 AND 9;


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES ((SELECT customer_CustID FROM customer WHERE customer_FName = 'Andrew' AND customer_LName = 'Wilkes-Krier'), '2024-04-20 19:11:00', 'delivery', 86.19, 23.62, 1);
INSERT INTO delivery (ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (4, 115, 'Party Blvd', 'Anderson', 'SC', 29621, 1);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES
(10, 'Original', 'XLarge', 'Completed', '2024-04-20 19:11:00', 27.94, 9.19, 4),
(11, 'Original', 'XLarge', 'Completed', '2024-04-20 19:11:00', 31.50, 6.25, 4),
(12, 'Original', 'XLarge', 'Completed', '2024-04-20 19:11:00', 26.75, 8.18, 4);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(10, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Pepperoni'), 0),
(10, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Sausage'), 0);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(11, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Ham'), 1),
(11, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Pineapple'), 1);

INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID)
VALUES
(11, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Specialty Pizza')),
(10, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Gameday Special')),
(11, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Gameday Special')),
(12, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Gameday Special'));


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES ((SELECT customer_CustID FROM customer WHERE customer_FName = 'Matt' AND customer_LName = 'Engers'), '2024-03-02 17:30:00', 'pickup', 27.45, 7.88, 1);
INSERT INTO pickup (ordertable_OrderID, pickup_IsPickedUp) VALUES (5, 1);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (13, 'Gluten-Free', 'XLarge', 'Completed', '2024-03-02 17:30:00', 27.45, 7.88, 5);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Green Pepper'), 0),
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Onion'), 0),
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Roma Tomato'), 0),
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Mushrooms'), 0),
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Black Olives'), 0),
(13, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Goat Cheese'), 0);
INSERT INTO pizza_discount (pizza_PizzaID, discount_DiscountID)
VALUES (13, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Specialty Pizza'));


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES ((SELECT customer_CustID FROM customer WHERE customer_FName = 'Frank' AND customer_LName = 'Turner'), '2024-03-02 18:17:00', 'delivery', 25.81, 4.24, 1);
INSERT INTO delivery (ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (6, 6745, 'Wessex St', 'Anderson', 'SC', 29621, 1);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES (14, 'Thin', 'Large', 'Completed', '2024-03-02 18:17:00', 25.81, 4.24, 6);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(14, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Chicken'), 0),
(14, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Green Pepper'), 0),
(14, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Onion'), 0),
(14, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Mushrooms'), 0),
(14, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Four Cheese Blend'), 1);


INSERT INTO ordertable (customer_CustID, ordertable_OrderDateTime, ordertable_OrderType, ordertable_CustPrice, ordertable_BusPrice, ordertable_IsComplete)
VALUES ((SELECT customer_CustID FROM customer WHERE customer_FName = 'Milo' AND customer_LName = 'Auckerman'), '2024-04-13 20:32:00', 'delivery', 31.66, 6.00, 1);

INSERT INTO delivery (ordertable_OrderID, delivery_HouseNum, delivery_Street, delivery_City, delivery_State, delivery_Zip, delivery_IsDelivered)
VALUES (7, 8879, 'Suburban', 'Anderson', 'SC', 29621, 1);

INSERT INTO pizza (pizza_PizzaID, pizza_CrustType, pizza_Size, pizza_PizzaState, pizza_PizzaDate, pizza_CustPrice, pizza_BusPrice, ordertable_OrderID)
VALUES
(15, 'Thin', 'Large', 'Completed', '2024-04-13 20:32:00', 18.00, 2.75, 7),
(16, 'Thin', 'Large', 'Completed', '2024-04-13 20:32:00', 19.25, 3.25, 7);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(15, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Four Cheese Blend'), 1);

INSERT INTO pizza_topping (pizza_PizzaID, topping_TopID, pizza_topping_IsDouble)
VALUES
(16, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Regular Cheese'), 1),
(16, (SELECT topping_TopID FROM topping WHERE topping_TopName = 'Pepperoni'), 1);

INSERT INTO order_discount (ordertable_OrderID, discount_DiscountID)
VALUES
(7, (SELECT discount_DiscountID FROM discount WHERE discount_DiscountName = 'Employee'));