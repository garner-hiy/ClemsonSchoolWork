-- ## Problem 5
-- 
-- Using the EMP_1 table, write the SQL code to change the job code to 501 for the person whose 
-- employee number (EMP_NUM) is 107 in table EMP_1.
--
UPDATE EMP_1
SET JOB_CODE = '501'
WHERE EMP_NUM = '107';