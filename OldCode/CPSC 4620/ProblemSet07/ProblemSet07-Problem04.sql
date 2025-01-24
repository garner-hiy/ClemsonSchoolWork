-- ## Problem 4
-- 
-- Write a query to display the largest average product price of any brand.
-- 
-- Your results should look like this:
-- +-------------------+
-- |   LARGEST AVERAGE |
-- |-------------------|
-- |             22.59 |
-- +-------------------+
-- 

SELECT ROUND(MAX(avg_price), 2) AS "LARGEST AVERAGE"
FROM (
    SELECT AVG(PROD_PRICE) AS avg_price
    FROM LGPRODUCT
    GROUP BY BRAND_ID
) AS subquery;