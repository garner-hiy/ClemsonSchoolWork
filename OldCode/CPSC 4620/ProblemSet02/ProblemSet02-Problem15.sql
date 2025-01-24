-- ## Problem 15
-- 
-- Write a query to create a listing of customers who did not make purchases during the 
-- invoicing period. Sort the results by customer code. 
-- 
-- Your output must match the output shown here.
-- 
-- +----------+-------------+
-- | CUS_CODE | CUS_BALANCE |
-- +----------+-------------+
-- |  10010   |    0.00     |
-- |  10013   |   536.75    |
-- |  10016   |   221.19    |
-- |  10017   |   768.93    |
-- |  10019   |    0.00     |
-- +----------+-------------+
-- 
SELECT 
    C.CUS_CODE, 
    ROUND(C.CUS_BALANCE, 2) AS CUS_BALANCE
FROM 
    CUSTOMER C
WHERE 
    C.CUS_CODE NOT IN (SELECT DISTINCT CUS_CODE FROM INVOICE)
ORDER BY 
    C.CUS_CODE;