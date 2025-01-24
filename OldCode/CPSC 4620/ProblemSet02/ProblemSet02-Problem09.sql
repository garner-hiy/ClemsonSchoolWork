-- ## Problem 9
-- 
-- Write a query to show the invoices and invoice totals show below.
-- Sort the results by customer code and then by invoice number.
-- 
-- +----------+------------+---------------+
-- | CUS_CODE | INV_NUMBER | Invoice Total |
-- +----------+------------+---------------+
-- |  10011   |    1002    |     9.98      |
-- |  10011   |    1004    |     34.87     |
-- |  10011   |    1008    |    399.15     |
-- |  10012   |    1003    |    153.85     |
-- |  10014   |    1001    |     24.94     |
-- |  10014   |    1006    |    397.83     |
-- |  10015   |    1007    |     34.97     |
-- |  10018   |    1005    |     70.44     |
-- +----------+------------+---------------+
-- 
SELECT 
    I.CUS_CODE, 
    I.INV_NUMBER, 
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE), 2) AS `Invoice Total`
FROM 
    INVOICE I
JOIN 
    LINE L ON I.INV_NUMBER = L.INV_NUMBER
GROUP BY 
    I.CUS_CODE, I.INV_NUMBER
ORDER BY 
    I.CUS_CODE, I.INV_NUMBER;