-- ## Problem 11
-- 
-- Write a query to generate the total number of invoices, the invoice total for all of the 
-- invoices, the smallest of the customer purchase amounts, the largest of the customer purchase
-- amounts, and the average of all the customer purchase amounts. 
-- 
-- Your output must match the results show below.
-- 
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- | Total Invoices | Total Sales | Minimum Customer Purchases | Largest Customer Purchases | Average Customer Purchases |
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- |       8        |   1126.03   |           34.97            |           444.00           |           225.21           |
-- +----------------+-------------+----------------------------+----------------------------+----------------------------+
-- 
-- 
SELECT
    (SELECT COUNT(DISTINCT INV_NUMBER) FROM INVOICE) AS `Total Invoices`,
    ROUND(SUM(L.LINE_UNITS * L.LINE_PRICE), 2) AS `Total Sales`,
    ROUND(MIN(TotalPurchases.CUST_TOTAL), 2) AS `Minimum Customer Purchases`,
    ROUND(MAX(TotalPurchases.CUST_TOTAL), 2) AS `Largest Customer Purchases`,
    ROUND(AVG(TotalPurchases.CUST_TOTAL), 2) AS `Average Customer Purchases`
FROM
    (
        SELECT
            I.CUS_CODE,
            SUM(L.LINE_UNITS * L.LINE_PRICE) AS CUST_TOTAL
        FROM
            INVOICE I
        JOIN
            LINE L ON I.INV_NUMBER = L.INV_NUMBER
        GROUP BY
            I.CUS_CODE
    ) AS TotalPurchases;