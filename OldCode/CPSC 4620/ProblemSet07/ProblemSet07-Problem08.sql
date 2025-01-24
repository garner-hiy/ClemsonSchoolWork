-- ## Problem 8
-- 
-- Write a query to display the starting salary for each employee. The starting salary would be 
-- the entry in the salary history with the oldest salary start date for each employee. 
-- Sort the output by employee number.
-- 
-- Your results should look like this:
-- +-----------+---------------+-------------+--------------+
-- |   EMP_NUM | EMP_LNAME     | EMP_FNAME   |   SAL_AMOUNT |
-- |-----------+---------------+-------------+--------------|
-- |     83304 | MCDONALD      | TAMARA      |        19770 |
-- |     83308 | LOVE          | CONNIE      |        11230 |
-- |     83312 | BAKER         | ROSALBA     |        39260 |
-- |     83314 | DAVID         | CHAROLETTE  |        15150 |
-- |     83318 | PECK          | DARCIE      |        22330 |
-- |     83321 | FARMER        | ANGELINA    |        18250 |
-- |     83332 | LONG          | WILLARD     |        23380 |
-- |     83341 | CORTEZ        | CHRISTINE   |        14510 |
-- |     83347 | WINN          | QUINTIN     |        17010 |
-- |     83349 | SINGH         | JENNIFFER   |        21220 |
-- |     83359 | WATTS         | MERLE       |        25370 |
-- |     83366 | BLEDSOE       | PHOEBE      |        23200 |
-- ...
-- |     84598 | SARGENT       | EDNA        |       126000 |
-- |     84599 | FENTON        | ELEANORE    |        33190 |
-- +-----------+---------------+-------------+--------------+
-- 

SELECT LGEMPLOYEE.EMP_NUM, EMP_LNAME, EMP_FNAME, ROUND(SAL_AMOUNT) AS SAL_AMOUNT
FROM LGEMPLOYEE
JOIN LGSALARY_HISTORY ON LGEMPLOYEE.EMP_NUM = LGSALARY_HISTORY.EMP_NUM
WHERE SAL_FROM = (
    SELECT MIN(SAL_FROM)
    FROM LGSALARY_HISTORY
    WHERE LGSALARY_HISTORY.EMP_NUM = LGEMPLOYEE.EMP_NUM
)
ORDER BY LGEMPLOYEE.EMP_NUM;