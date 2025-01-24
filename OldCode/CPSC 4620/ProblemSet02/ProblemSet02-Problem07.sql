-- ## Problem 7
-- 
-- Write a query to compute the total of all purchases, the number of purchases, and the average
-- purchase amount made by each customer. 
-- 
-- Your results must match those shown below. Sort the results by customer code.
-- 
-- +----------+-------------+-----------------+---------------------+-------------------------+
-- | CUS_CODE | CUS_BALANCE | Total Purchases | Number of Purchases | Average Purchase Amount |
-- +----------+-------------+-----------------+---------------------+-------------------------+
-- |  10011   |    0.00     |     444.00      |          6          |          74.00          |
-- |  10012   |   345.86    |     153.85      |          3          |          51.28          |
-- |  10014   |    0.00     |     422.77      |          6          |          70.46          |
-- |  10015   |    0.00     |      34.97      |          2          |          17.49          |
-- |  10018   |   216.55    |      70.44      |          1          |          70.44          |
-- +----------+-------------+-----------------+---------------------+-------------------------+
-- 
-- 
SELECT 
    C.CUS_CODE, 
    C.CUS_BALANCE, 
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE), 2) AS `Total Purchases`,
    COUNT(L.LINE_NUMBER) AS `Number of Purchases`,
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE) / COUNT(L.LINE_NUMBER), 2) AS `Average Purchase Amount`
FROM 
    CUSTOMER C
JOIN 
    INVOICE I ON C.CUS_CODE = I.CUS_CODE
JOIN 
    LINE L ON I.INV_NUMBER = L.INV_NUMBER
GROUP BY 
    C.CUS_CODE, C.CUS_BALANCE
ORDER BY 
    C.CUS_CODE;