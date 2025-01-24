-- Show the data in each table

-- Display data from baseprice table
SELECT * FROM baseprice;

-- Display data from customer table
SELECT * FROM customer;

-- Display data from ordertable table
SELECT * FROM ordertable;

-- Display data from pizza table
SELECT * FROM pizza;

-- Display data from topping table
SELECT * FROM topping
ORDER BY topping_TopName;

-- Display data from pizza_topping table
SELECT * FROM pizza_topping;

-- Display data from discount table
SELECT * FROM discount;

-- Display data from pizza_discount table
SELECT * FROM pizza_discount;

-- Display data from order_discount table
SELECT * FROM order_discount;

-- Display data from pickup table
SELECT * FROM pickup;

-- Display data from delivery table
SELECT * FROM delivery;

-- Display data from dinein table
SELECT * FROM dinein;

-- Show the data in each view

-- Display data from ToppingPopularity view
SELECT * FROM ToppingPopularity;

-- Display data from ProfitByPizza view
SELECT * FROM ProfitByPizza;

-- Display data from ProfitByOrderType view
SELECT * FROM ProfitByOrderType;