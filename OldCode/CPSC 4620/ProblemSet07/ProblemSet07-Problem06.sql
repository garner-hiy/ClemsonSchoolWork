-- ## Problem 6
-- 
-- Write a query to display the manager name, department name, department phone number, employee name,
-- customer name, invoice date, and invoice total for the department manager of the employee who made
-- a sale to a customer whose last name is Hagan on May 18, 2021.
-- 
-- Your results should look like this:
-- +-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------+
-- | EMP_FNAME   | EMP_LNAME   | DEPT_NAME   | DEPT_PHONE   | EMP_FNAME   | EMP_LNAME   | CUST_FNAME   | CUST_LNAME   | INV_DATE   |   INV_TOTAL |
-- |-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------|
-- | FRANKLYN    | STOVER      | SALES       | 555-2824     | THURMAN     | WILKINSON   | DARELL       | HAGAN        | 2021-05-18 |      315.04 |
-- +-------------+-------------+-------------+--------------+-------------+-------------+--------------+--------------+------------+-------------+
-- 

SELECT MGR.EMP_FNAME AS EMP_FNAME, MGR.EMP_LNAME AS EMP_LNAME, DEPT_NAME, DEPT_PHONE,
       EMP.EMP_FNAME, EMP.EMP_LNAME, CUST_FNAME, CUST_LNAME, INV_DATE, INV_TOTAL
FROM LGINVOICE
JOIN LGCUSTOMER ON LGINVOICE.CUST_CODE = LGCUSTOMER.CUST_CODE
JOIN LGEMPLOYEE AS EMP ON LGINVOICE.EMPLOYEE_ID = EMP.EMP_NUM
JOIN LGDEPARTMENT ON EMP.DEPT_NUM = LGDEPARTMENT.DEPT_NUM
JOIN LGEMPLOYEE AS MGR ON LGDEPARTMENT.EMP_NUM = MGR.EMP_NUM
WHERE CUST_LNAME = 'Hagan' AND INV_DATE = '2021-05-18';