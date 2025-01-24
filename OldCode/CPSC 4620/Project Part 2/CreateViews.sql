
CREATE VIEW ToppingPopularity AS
SELECT 
    t.topping_TopName AS Topping,
    IFNULL(SUM(pt.pizza_topping_IsDouble + 1), 0) AS ToppingCount 
FROM 
    topping t
LEFT JOIN 
    pizza_topping pt ON t.topping_TopID = pt.topping_TopID
GROUP BY 
    t.topping_TopName
ORDER BY 
    ToppingCount DESC;


CREATE VIEW ProfitByPizza AS
SELECT 
    p.pizza_Size AS Size,
    p.pizza_CrustType AS Crust,
    SUM(p.pizza_CustPrice - p.pizza_BusPrice) AS Profit,
    DATE_FORMAT(p.pizza_PizzaDate, '%c/%Y') AS OrderMonth
FROM 
    pizza p
GROUP BY 
    p.pizza_Size, p.pizza_CrustType, OrderMonth
ORDER BY 
    Profit;


CREATE VIEW ProfitByOrderType AS 
SELECT 
    customerType,
    OrderMonth,
    SUM(TotalOrderPrice) AS TotalOrderPrice,
    SUM(TotalOrderCost) AS TotalOrderCost,
    SUM(Profit) AS Profit
FROM (
    SELECT 
        CASE 
            WHEN o.ordertable_OrderID IN (SELECT ordertable_OrderID FROM dinein) THEN 'dinein'
            WHEN o.ordertable_OrderID IN (SELECT ordertable_OrderID FROM pickup) THEN 'pickup'
            WHEN o.ordertable_OrderID IN (SELECT ordertable_OrderID FROM delivery) THEN 'delivery'
            ELSE 'unknown'
        END AS customerType,
        DATE_FORMAT(o.ordertable_OrderDateTime, '%c/%Y') AS OrderMonth,
        SUM(o.ordertable_CustPrice) AS TotalOrderPrice,
        SUM(o.ordertable_BusPrice) AS TotalOrderCost,
        SUM(o.ordertable_CustPrice - o.ordertable_BusPrice) AS Profit
    FROM 
        ordertable o
    GROUP BY 
        customerType, OrderMonth
    UNION ALL
    SELECT 
        'Grand Total' AS customerType,
        'Grand Total' AS OrderMonth,
        SUM(o.ordertable_CustPrice) AS TotalOrderPrice,
        SUM(o.ordertable_BusPrice) AS TotalOrderCost,
        SUM(o.ordertable_CustPrice - o.ordertable_BusPrice) AS Profit
    FROM 
        ordertable o
) AS combined
GROUP BY 
    customerType, OrderMonth
ORDER BY 
    CASE WHEN OrderMonth = 'Grand Total' THEN 1 ELSE 0 END, OrderMonth;