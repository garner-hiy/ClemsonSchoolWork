-- ## Problem 12
-- 
-- List the balances of customers who have made purchases during the current invoice cycle,
-- that is, for the customers who appear in the INVOICE table. 
-- 
-- Sort the results by customer code.  Your output must match the results show below.
-- 
-- +----------+-------------+
-- | CUS_CODE | CUS_BALANCE |
-- +----------+-------------+
-- |  10011   |    0.00     |
-- |  10012   |   345.86    |
-- |  10014   |    0.00     |
-- |  10015   |    0.00     |
-- |  10018   |   216.55    |
-- +----------+-------------+
-- 
SELECT 
    DISTINCT C.CUS_CODE, 
    C.CUS_BALANCE
FROM 
    CUSTOMER C
JOIN 
    INVOICE I ON C.CUS_CODE = I.CUS_CODE
ORDER BY 
    C.CUS_CODE;