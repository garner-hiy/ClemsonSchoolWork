-- ## Problem 5
-- 
-- Write a query to display the customer code, balance, and total purchases for each customer. 
-- Total purchase is calculated by summing the line subtotals 
-- for each customer. Sort the results by customer code, and use aliases as shown below.
-- 
-- +----------+-------------+-----------------+
-- | CUS_CODE | CUS_BALANCE | Total Purchases |
-- +----------+-------------+-----------------+
-- |  10011   |    0.00     |     444.00      |
-- |  10012   |   345.86    |     153.85      |
-- |  10014   |    0.00     |     422.77      |
-- |  10015   |    0.00     |      34.97      |
-- |  10018   |   216.55    |      70.44      |
-- +----------+-------------+-----------------+
-- 
SELECT 
    C.CUS_CODE, 
    C.CUS_BALANCE, 
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE), 2) AS `Total Purchases`
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