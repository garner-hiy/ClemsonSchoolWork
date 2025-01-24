-- ## Problem 10
-- 
-- The Binder Prime Company wants to recognize the employee who sold the most of its products during
--  a specified period. Write a query to display the employee number, employee first name, employee
-- last name, email address, and total units sold for the employee who sold the most Binder Prime
-- brand products between November 1, 2021, and December 5, 2021. 
-- 
-- If there is a tie for most units sold, sort the output by employee last name.
-- 
-- Your results should look like this:
-- +-----------+-------------+-------------+--------------------------+---------+
-- |   EMP_NUM | EMP_FNAME   | EMP_LNAME   | EMP_EMAIL                |   TOTAL |
-- |-----------+-------------+-------------+--------------------------+---------|
-- |     84134 | ROSALIE     | GARLAND     | G.ROSALI98@LGCOMPANY.COM |      23 |
-- |     83850 | RUSTY       | MILES       | M.RUSTY95@LGCOMPANY.COM  |      23 |
-- +-----------+-------------+-------------+--------------------------+---------+
-- 

WITH SalesSummary AS (
    SELECT E.EMP_NUM, E.EMP_FNAME, E.EMP_LNAME, E.EMP_EMAIL, SUM(L.LINE_QTY) AS TOTAL
    FROM LGINVOICE AS I
    JOIN LGLINE AS L ON I.INV_NUM = L.INV_NUM
    JOIN LGPRODUCT AS P ON L.PROD_SKU = P.PROD_SKU
    JOIN LGBRAND AS B ON P.BRAND_ID = B.BRAND_ID
    JOIN LGEMPLOYEE AS E ON I.EMPLOYEE_ID = E.EMP_NUM
    WHERE B.BRAND_NAME = 'Binder Prime'
      AND I.INV_DATE BETWEEN '2021-11-01' AND '2021-12-05'
    GROUP BY E.EMP_NUM, E.EMP_FNAME, E.EMP_LNAME, E.EMP_EMAIL
)
SELECT EMP_NUM, EMP_FNAME, EMP_LNAME, EMP_EMAIL, TOTAL
FROM SalesSummary
WHERE TOTAL = (SELECT MAX(TOTAL) FROM SalesSummary)
ORDER BY EMP_LNAME;