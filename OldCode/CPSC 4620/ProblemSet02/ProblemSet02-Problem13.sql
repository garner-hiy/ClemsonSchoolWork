-- ## Problem 13
-- 
-- Provide a summary of customer balance characteristics for customers who made purchases. 
-- Include the minimum balance, maximum balance, and average balance, as shown below.
-- 
-- +-----------------+-----------------+-----------------+
-- | Minimum Balance | Maximum Balance | Average Balance |
-- +-----------------+-----------------+-----------------+
-- |      0.00       |     345.86      |      112.48     |
-- +-----------------+-----------------+-----------------+
-- 
SELECT 
    ROUND(MIN(C.CUS_BALANCE), 2) AS `Minimum Balance`,
    ROUND(MAX(C.CUS_BALANCE), 2) AS `Maximum Balance`,
    ROUND(AVG(C.CUS_BALANCE), 2) AS `Average Balance`
FROM 
    CUSTOMER C
WHERE 
    C.CUS_CODE IN (SELECT DISTINCT CUS_CODE FROM INVOICE);