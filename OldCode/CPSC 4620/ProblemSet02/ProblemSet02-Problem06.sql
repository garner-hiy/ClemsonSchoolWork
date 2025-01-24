-- ## Problem 6
-- 
-- Modify the query used in Problem 5 to include the number of individual product purchases made 
-- by each customer. (In other words, if the customer’s invoice is based on three products, 
-- one per LINE_NUMBER, you count three product purchases. Note that in the original invoice data,
-- customer 10011 generated three invoices, which contained a total of six lines, each representing
-- a product purchase.) 
-- 
-- Your results must match those shown below and be sorted by customer code.
-- 
-- +----------+-------------+-----------------+---------------------+
-- | CUS_CODE | CUS_BALANCE | Total Purchases | Number of Purchases |
-- +----------+-------------+-----------------+---------------------+
-- |  10011   |    0.00     |     444.00      |          6          |
-- |  10012   |   345.86    |     153.85      |          3          |
-- |  10014   |    0.00     |     422.77      |          6          |
-- |  10015   |    0.00     |      34.97      |          2          |
-- |  10018   |   216.55    |      70.44      |          1          |
-- +----------+-------------+-----------------+---------------------+
-- 
SELECT 
    C.CUS_CODE, 
    C.CUS_BALANCE, 
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE), 2) AS `Total Purchases`,
    COUNT(L.LINE_NUMBER) AS `Number of Purchases`
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