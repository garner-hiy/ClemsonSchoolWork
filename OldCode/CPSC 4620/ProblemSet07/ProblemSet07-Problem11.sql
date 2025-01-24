-- ## Problem 11
-- 
-- Write a query to display the customer code, first name, and last name of all customers who have 
-- had at least one invoice completed by employee 83649 and at least one invoice completed by 
-- employee 83677. Sort the output by customer last name and then first name.
-- 
-- Your results should look like this:
-- +-------------+--------------+--------------+
-- |   CUST_CODE | CUST_FNAME   | CUST_LNAME   |
-- |-------------+--------------+--------------|
-- |         684 | WENDI        | BEAN         |
-- |         684 | WENDI        | BEAN         |
-- |         340 | MARCIA       | BURRIS       |
-- |         211 | GERALD       | CAUDILL      |
-- |         211 | GERALD       | CAUDILL      |
-- |         292 | VALARIE      | DILLARD      |
-- |         293 | CLAIR        | ERICKSON     |
-- |         416 | TATIANA      | HOWE         |
-- |         996 | EZRA         | LYON         |
-- |          98 | VALENTIN     | MARINO       |
-- |          98 | VALENTIN     | MARINO       |
-- |         121 | PETER        | SMALL        |
-- |        1157 | LUCIO        | STALEY       |
-- |         617 | CESAR        | TALLEY       |
-- |         457 | SHAUNA       | WERNER       |
-- |         131 | SAL          | WHALEY       |
-- +-------------+--------------+--------------+
-- 
SELECT C.CUST_CODE, C.CUST_FNAME, C.CUST_LNAME
FROM LGCUSTOMER AS C
JOIN LGINVOICE AS I1 ON C.CUST_CODE = I1.CUST_CODE
JOIN LGINVOICE AS I2 ON C.CUST_CODE = I2.CUST_CODE
WHERE I1.EMPLOYEE_ID = 83649 AND I2.EMPLOYEE_ID = 83677
ORDER BY C.CUST_LNAME, C.CUST_FNAME;
