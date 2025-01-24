-- ## Problem 5
-- 
-- Write a query to display the brand ID, brand name, brand type, and average price of products 
-- for the brand that has the largest average product price.
-- 
-- Your results should look like this:
-- +------------+--------------+--------------+------------+
-- |   BRAND_ID | BRAND_NAME   | BRAND_TYPE   |   AVGPRICE |
-- |------------+--------------+--------------+------------|
-- |         29 | BUSTERS      | VALUE        |      22.59 |
-- +------------+--------------+--------------+------------+
-- 
SELECT LGBRAND.BRAND_ID, BRAND_NAME, BRAND_TYPE, ROUND(AVG(PROD_PRICE), 2) AS AVGPRICE
FROM LGBRAND
JOIN LGPRODUCT ON LGBRAND.BRAND_ID = LGPRODUCT.BRAND_ID
GROUP BY LGBRAND.BRAND_ID, BRAND_NAME, BRAND_TYPE
HAVING AVG(PROD_PRICE) = (
    SELECT MAX(avg_price)
    FROM (
        SELECT AVG(PROD_PRICE) AS avg_price
        FROM LGPRODUCT
        GROUP BY BRAND_ID
    ) AS subquery
);