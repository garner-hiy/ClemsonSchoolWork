-- ## Problem 10
-- 
-- Modify customer 1001 to have a date of birth on December 22, 1988.
-- 
-- NOTE: Use YYYY-MM-DD format for date values.
--

UPDATE CUSTOMER
SET CUST_DOB = '1988-12-22'
WHERE CUST_NUM = 1001;