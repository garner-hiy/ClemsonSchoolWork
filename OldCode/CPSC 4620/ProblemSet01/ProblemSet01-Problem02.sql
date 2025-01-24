-- ## Problem 2
--
-- Using the EMPLOYEE, JOB, and PROJECT tables, write the SQL that will join the tables using 
-- common attributes. 
-- 
-- Display the results as shown below:
-- 
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+
--    |  PROJ_NAME   | PROJ_VALUE | PROJ_BALANCE | EMP_LNAME  | EMP_FNAME | EMP_INITIAL | JOB_CODE |   JOB_DESCRIPTION   | JOB_CHG_HOUR |
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+
--    | Rolling Tide | 805000.00  |  500345.20   |   Senior   |   David   |      H      |   501    |   Systems Analyst   |    96.75     |
--    |  Evergreen   | 1453500.00 |  1002350.00  |  Arbough   |   June    |      E      |   503    | Electrical Engineer |    84.50     |
--    |  Starflight  | 2650500.00 |  2309880.00  |   Alonzo   |   Maria   |      D      |   500    |     Programmer      |    35.75     |
--    |  Amber Wave  | 3500500.00 |  2110346.00  | Washington |   Ralph   |      B      |   501    |   Systems Analyst   |    96.75     |
--    +--------------+------------+--------------+------------+-----------+-------------+----------+---------------------+--------------+

SELECT 
    P.PROJ_NAME, 
    P.PROJ_VALUE, 
    P.PROJ_BALANCE, 
    E.EMP_LNAME, 
    E.EMP_FNAME, 
    COALESCE(E.EMP_INITIAL, '') AS EMP_INITIAL, 
    E.JOB_CODE, 
    J.JOB_DESCRIPTION, 
    J.JOB_CHG_HOUR
FROM 
    PROJECT P
JOIN 
    EMPLOYEE E ON P.EMP_NUM = E.EMP_NUM
JOIN 
    JOB J ON E.JOB_CODE = J.JOB_CODE
ORDER BY 
    P.PROJ_VALUE;