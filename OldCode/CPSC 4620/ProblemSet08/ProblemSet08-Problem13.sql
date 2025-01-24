-- ## Problem 13
-- 
-- Using the EMP_2 table, write a single SQL statement that will change the
-- project number (PROJ_NUM) to 18 for all employees whose job classification (JOB_CODE) is 500.
--

UPDATE EMP_2
SET PROJ_NUM = '18'
WHERE JOB_CODE = '500';