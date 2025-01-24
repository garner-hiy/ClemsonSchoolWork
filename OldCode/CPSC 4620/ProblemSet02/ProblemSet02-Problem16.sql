-- ## Problem 16
-- 
-- Write a query to find the customer balance summary for all customers who have not made 
-- purchases during the current invoicing period. 
-- 
-- The results are shown here.
-- 
-- +---------------+-----------------+-----------------+-----------------+
-- | Total Balance | Minimum Balance | Maximum Balance | Average Balance |
-- +---------------+-----------------+-----------------+-----------------+
-- |    1526.87    |      0.00       |     768.93      |     305.37      |
-- +---------------+-----------------+-----------------+-----------------+
-- 
-- 
SELECT 
    ROUND(SUM(C.CUS_BALANCE), 2) AS `Total Balance`,
    ROUND(MIN(C.CUS_BALANCE), 2) AS `Minimum Balance`,
    ROUND(MAX(C.CUS_BALANCE), 2) AS `Maximum Balance`,
    ROUND(AVG(C.CUS_BALANCE), 2) AS `Average Balance`
FROM 
    CUSTOMER C
WHERE 
    C.CUS_CODE NOT IN (SELECT DISTINCT CUS_CODE FROM INVOICE);
