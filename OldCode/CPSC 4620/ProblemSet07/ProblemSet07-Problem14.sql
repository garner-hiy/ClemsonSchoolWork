-- ## Problem 14
-- 
-- The purchasing manager is still concerned about the impact of price on sales. Write a query to
-- display the brand name, brand type, product SKU, product description, and price of any products
-- that are not a premium brand, but that cost more than the most expensive premium brand products.
-- 
-- Your results should look like this:
-- +--------------+--------------+------------+--------------------------------------------+--------------+
-- | BRAND_NAME   | BRAND_TYPE   | PROD_SKU   | PROD_DESCRIPT                              |   PROD_PRICE |
-- |--------------+--------------+------------+--------------------------------------------+--------------|
-- | LONG HAUL    | CONTRACTOR   | 1964-OUT   | Fire Resistant Top Coat, for Interior Wood |        78.49 |
-- +--------------+--------------+------------+--------------------------------------------+--------------+
-- 

SELECT B.BRAND_NAME, B.BRAND_TYPE, P.PROD_SKU, P.PROD_DESCRIPT, P.PROD_PRICE
FROM LGBRAND AS B
JOIN LGPRODUCT AS P ON B.BRAND_ID = P.BRAND_ID
WHERE B.BRAND_TYPE != 'PREMIUM'
  AND P.PROD_PRICE > (
      SELECT MAX(P2.PROD_PRICE)
      FROM LGBRAND AS B2
      JOIN LGPRODUCT AS P2 ON B2.BRAND_ID = P2.BRAND_ID
      WHERE B2.BRAND_TYPE = 'PREMIUM'
  )
ORDER BY P.PROD_PRICE DESC;