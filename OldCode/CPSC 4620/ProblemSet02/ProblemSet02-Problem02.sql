-- ## Problem 2
-- 
-- Write a query to count the number of customers with a balance of more than $500.
-- 
-- +----------+
-- | COUNT(*) |
-- +----------+
-- |    2     |
-- +----------+
-- 
SELECT COUNT(*) AS `COUNT(*)`
FROM CUSTOMER
WHERE CUS_BALANCE > 500;