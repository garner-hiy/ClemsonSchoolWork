-- ## Problem 07
-- 
-- Write a query to display the employee number, last name, email address, title, and department name
-- of each employee whose job title ends in the word “ASSOCIATE.” Sort the output by department name,
-- employee title, and employee number.
-- 
-- Your results should look like this:
-- +-----------+---------------+--------------------------+------------------+------------------+
-- |   EMP_NUM | EMP_LNAME     | EMP_EMAIL                | EMP_TITLE        | DEPT_NAME        |
-- |-----------+---------------+--------------------------+------------------+------------------|
-- |     83378 | DUNHAM        | F.DUNHAM5@LGCOMPANY.COM  | ASSOCIATE        | ACCOUNTING       |
-- |     83517 | ALBRIGHT      | SO.ALBRI96@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     83583 | ROLLINS       | M.ROLLIN99@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     83661 | FINN          | D.FINN87@LGCOMPANY.COM   | ASSOCIATE        | ACCOUNTING       |
-- |     84386 | RIVERA        | D.RIVERA76@LGCOMPANY.COM | ASSOCIATE        | ACCOUNTING       |
-- |     84526 | LASSITER      | F.LASSIT8@LGCOMPANY.COM  | ASSOCIATE        | ACCOUNTING       |
-- |     83341 | CORTEZ        | C.CORTEZ85@LGCOMPANY.COM | ASSOCIATE        | CUSTOMER SERVICE |
-- ...
-- |     84543 | GOODMAN       | K.GOODMA96@LGCOMPANY.COM | ASSOCIATE        | WAREHOUSE        |
-- |     84545 | BURKETT       | I.BURKET9@LGCOMPANY.COM  | ASSOCIATE        | WAREHOUSE        |
-- +-----------+---------------+--------------------------+------------------+------------------+
-- 

SELECT LGEMPLOYEE.EMP_NUM, EMP_LNAME, EMP_EMAIL, EMP_TITLE, DEPT_NAME
FROM LGEMPLOYEE
JOIN LGDEPARTMENT ON LGEMPLOYEE.DEPT_NUM = LGDEPARTMENT.DEPT_NUM
WHERE EMP_TITLE LIKE '%ASSOCIATE'
ORDER BY DEPT_NAME, EMP_TITLE, LGEMPLOYEE.EMP_NUM;