
DROP SCHEMA IF EXISTS PizzaDB;
CREATE SCHEMA PizzaDB;
USE PizzaDB;

CREATE TABLE baseprice (
    baseprice_Size VARCHAR(30) NOT NULL,
    baseprice_CrustType VARCHAR(30) NOT NULL,
    baseprice_CustPrice DECIMAL(5,2) NOT NULL,
    baseprice_BusPrice DECIMAL(5,2) NOT NULL,
    PRIMARY KEY (baseprice_CrustType, baseprice_Size)
);

CREATE TABLE customer (
    customer_CustID INT PRIMARY KEY AUTO_INCREMENT,
    customer_FName VARCHAR(30) NOT NULL,
    customer_LName VARCHAR(30) NOT NULL,
    customer_PhoneNum VARCHAR(30) NOT NULL
);

CREATE TABLE ordertable (
    ordertable_OrderID INT PRIMARY KEY AUTO_INCREMENT,
    customer_CustID INT,
    ordertable_OrderDateTime DATETIME NOT NULL,
    ordertable_OrderType VARCHAR(30) NOT NULL,
    ordertable_CustPrice DECIMAL(5,2) NOT NULL,
    ordertable_BusPrice DECIMAL(5,2) NOT NULL,
    ordertable_IsComplete TINYINT DEFAULT 0,
    FOREIGN KEY (customer_CustID) REFERENCES customer(customer_CustID)
);

CREATE TABLE pizza (
    pizza_PizzaID INT PRIMARY KEY,
	pizza_CrustType VARCHAR(30) NOT NULL,
    pizza_Size VARCHAR(30) NOT NULL,
    pizza_PizzaState VARCHAR(30),
    pizza_PizzaDate DATETIME,
    pizza_CustPrice DECIMAL(5,2),
    pizza_BusPrice DECIMAL(5,2),
    ordertable_OrderID INT,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
    FOREIGN KEY (pizza_CrustType, pizza_Size) REFERENCES baseprice(baseprice_CrustType, baseprice_Size)
);

CREATE TABLE topping (
    topping_TopID INT PRIMARY KEY AUTO_INCREMENT,
    topping_TopName VARCHAR(30) NOT NULL,
    topping_SmallAMT DECIMAL(5,2) NOT NULL,
    topping_MedAMT DECIMAL(5,2) NOT NULL,
    topping_LgAMT DECIMAL(5,2) NOT NULL,
    topping_XLAMT DECIMAL(5,2) NOT NULL,
    topping_BusPrice DECIMAL(5,2) NOT NULL,
    topping_CustPrice DECIMAL(5,2) NOT NULL,
    topping_MinINVT INT NOT NULL,
    topping_CurINVT INT NOT NULL
);

CREATE TABLE pizza_topping (
    pizza_PizzaID INT NOT NULL,
    topping_TopID INT NOT NULL,
    pizza_topping_IsDouble INT NOT NULL,
    PRIMARY KEY (pizza_PizzaID, topping_TopID),
    FOREIGN KEY (pizza_PizzaID) REFERENCES pizza(pizza_PizzaID),
    FOREIGN KEY (topping_TopID) REFERENCES topping(topping_TopID)
);

CREATE TABLE discount (
    discount_DiscountID INT PRIMARY KEY AUTO_INCREMENT,
    discount_DiscountName VARCHAR(30) NOT NULL,
    discount_Amount DECIMAL(5,2) NOT NULL,
    discount_IsPercent TINYINT NOT NULL
);

CREATE TABLE pizza_discount (
    pizza_PizzaID INT NOT NULL,
    discount_DiscountID INT NOT NULL,
    PRIMARY KEY (pizza_PizzaID, discount_DiscountID),
    FOREIGN KEY (pizza_PizzaID) REFERENCES pizza(pizza_PizzaID),
    FOREIGN KEY (discount_DiscountID) REFERENCES discount(discount_DiscountID)
);

CREATE TABLE order_discount (
    ordertable_OrderID INT NOT NULL,
    discount_DiscountID INT NOT NULL,
    PRIMARY KEY (ordertable_OrderID, discount_DiscountID),
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID),
    FOREIGN KEY (discount_DiscountID) REFERENCES discount(discount_DiscountID)
);

CREATE TABLE pickup (
    ordertable_OrderID INT PRIMARY KEY,
    pickup_IsPickedUp TINYINT NOT NULL DEFAULT 0,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID)
);

CREATE TABLE delivery (
    ordertable_OrderID INT PRIMARY KEY,
    delivery_HouseNum INT NOT NULL,
    delivery_Street VARCHAR(30) NOT NULL,
    delivery_City VARCHAR(30) NOT NULL,
    delivery_State VARCHAR(2) NOT NULL,
    delivery_Zip INT NOT NULL,
    delivery_IsDelivered TINYINT NOT NULL DEFAULT 0,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID)
);

CREATE TABLE dinein (
    ordertable_OrderID INT PRIMARY KEY,
    dinein_TableNum INT NOT NULL,
    FOREIGN KEY (ordertable_OrderID) REFERENCES ordertable(ordertable_OrderID)
);