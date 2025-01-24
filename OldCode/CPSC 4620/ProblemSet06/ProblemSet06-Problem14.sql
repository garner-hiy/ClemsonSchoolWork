-- ## Problem 14
-- 
-- Write a query to display the employee number, first name, last name, and largest salary amount
-- for each employee in department 200. Sort the output by largest salary in descending order, 
-- and then by employee number.
-- 
-- Your results should look like this:
-- +-----------+-------------+-------------+-----------------+
-- |   EMP_NUM | EMP_FNAME   | EMP_LNAME   |   LARGESTSALARY |
-- |-----------+-------------+-------------+-----------------|
-- |     83509 | FRANKLYN    | STOVER      |          210000 |
-- |     83705 | JOSE        | BARR        |          147000 |
-- |     83537 | CLEO        | ENGLISH     |          136000 |
-- |     83565 | LOURDES     | ABERNATHY   |          133000 |
-- |     83593 | ROSANNE     | NASH        |          129000 |
-- ...
-- |     84392 | ALEJANDRA   | WHALEY      |           61000 |
-- |     84420 | DOUG        | CAUDILL     |           61000 |
-- +-----------+-------------+-------------+-----------------+
-- 
-- 
SELECT LGEMPLOYEE.EMP_NUM, EMP_FNAME, EMP_LNAME, MAX(SAL_AMOUNT) AS LARGESTSALARY
FROM LGEMPLOYEE
JOIN LGSALARY_HISTORY ON LGEMPLOYEE.EMP_NUM = LGSALARY_HISTORY.EMP_NUM
WHERE LGEMPLOYEE.DEPT_NUM = 200
GROUP BY LGEMPLOYEE.EMP_NUM, EMP_FNAME, EMP_LNAME
ORDER BY LARGESTSALARY DESC, LGEMPLOYEE.EMP_NUM;