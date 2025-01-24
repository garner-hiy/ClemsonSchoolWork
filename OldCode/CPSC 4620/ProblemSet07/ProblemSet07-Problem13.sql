-- ## Problem 13
-- 
-- One of the purchasing managers is interested in the impact of product prices on the sale of
-- products of each brand. Write a query to display the brand name, brand type, average price of
-- products of each brand, and total units sold of products of each brand. Even if a product has 
-- been sold more than once, its price should only be included once in the calculation of the average
-- price. 
-- 
-- However, you must be careful because multiple products of the same brand can have the same price,
-- and each of those products must be included in the calculation of the brand’s average price. 
-- Sort the result by brand name.
-- 
-- Your results should look like this:
-- +-------------------+--------------+-----------------+--------------+
-- | BRAND_NAME        | BRAND_TYPE   |   Average Price |   Units Sold |
-- |-------------------+--------------+-----------------+--------------|
-- | BINDER PRIME      | PREMIUM      |           16.12 |         3753 |
-- | BUSTERS           | VALUE        |           22.59 |         3727 |
-- | FORESTERS BEST    | VALUE        |           20.94 |         2086 |
-- | HOME COMFORT      | CONTRACTOR   |           21.8  |         4842 |
-- | LE MODE           | PREMIUM      |           19.22 |         5284 |
-- | LONG HAUL         | CONTRACTOR   |           20.12 |         5728 |
-- | OLDE TYME QUALITY | CONTRACTOR   |           18.33 |         3614 |
-- | STUTTENFURST      | CONTRACTOR   |           16.47 |         3671 |
-- | VALU-MATTE        | VALUE        |           16.84 |         2485 |
-- +-------------------+--------------+-----------------+--------------+
-- 

SELECT B.BRAND_NAME, B.BRAND_TYPE, ROUND(AVG(DISTINCT P.PROD_PRICE), 2) AS "Average Price", SUM(L.LINE_QTY) AS "Units Sold"
FROM LGBRAND AS B
JOIN LGPRODUCT AS P ON B.BRAND_ID = P.BRAND_ID
LEFT JOIN LGLINE AS L ON P.PROD_SKU = L.PROD_SKU
GROUP BY B.BRAND_NAME, B.BRAND_TYPE
ORDER BY B.BRAND_NAME;