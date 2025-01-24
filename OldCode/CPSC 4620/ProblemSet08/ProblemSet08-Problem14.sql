-- ## Problem 14
-- 
-- Using the EMP_2 table, write a single SQL statement that will change the project
-- number (PROJ_NUM) to 25 for all employees whose job classification (JOB_CODE) is 502 or higher.
-- 

UPDATE EMP_2
SET PROJ_NUM = '25'
WHERE JOB_CODE >= '502';
