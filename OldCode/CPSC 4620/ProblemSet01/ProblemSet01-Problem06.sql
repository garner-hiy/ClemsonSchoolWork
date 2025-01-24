-- ## Problem 6
--
-- Using the data in the ASSIGNMENT table, write the SQL that will yield the 
-- total number of hours worked for each employee and the total charges stemming 
-- from those hours worked, sorted by employee number. 
-- 
-- The results of running that query are shown below:
-- 
--    +---------+------------+-------------------+--------------------+
--    | EMP_NUM | EMP_LNAME  | SumOfASSIGN_HOURS | SumOfASSIGN_CHARGE |
--    +---------+------------+-------------------+--------------------+
--    |   101   |    News    |        3.1        |       387.50       |
--    |   103   |  Arbough   |       19.7        |      1664.65       |
--    |   104   |  Ramoras   |       11.9        |      1218.70       |
--    |   105   |  Johnson   |       12.5        |      1382.50       |
--    |   108   | Washington |        8.3        |       840.15       |
--    |   113   | Joenbrood  |        3.8        |       192.85       |
--    |   115   |  Bawangi   |       12.5        |      1276.75       |
--    |   117   | Williamson |       18.8        |       649.54       |
--    +---------+------------+-------------------+--------------------+

SELECT
    A.EMP_NUM,
    E.EMP_LNAME,
    ROUND(SUM(A.ASSIGN_HOURS), 1) AS SumOfASSIGN_HOURS,
    ROUND(SUM(A.ASSIGN_CHARGE), 2) AS SumOfASSIGN_CHARGE
FROM
    ASSIGNMENT A
JOIN
    EMPLOYEE E ON A.EMP_NUM = E.EMP_NUM
GROUP BY
    A.EMP_NUM, E.EMP_LNAME
ORDER BY
    A.EMP_NUM;
