-- ## Problem 06
-- 
-- Write a query to display the first name, last name, street, city, state, and zip code of any
-- customer who purchased a Foresters Best brand top coat between July 15, 2021, and July 31, 2021. 
-- If a customer purchased more than one such product, display the customer’s information only once 
-- in the output. Sort the output by state, last name, and then first name.
-- 
-- Your results should look like this:
-- +--------------+--------------+---------------------------+---------------+--------------+------------+
-- | CUST_FNAME   | CUST_LNAME   | CUST_STREET               | CUST_CITY     | CUST_STATE   |   CUST_ZIP |
-- |--------------+--------------+---------------------------+---------------+--------------+------------|
-- | LUPE         | SANTANA      | 1292 WEST 70TH PLACE      | Phenix City   | AL           |      36867 |
-- | HOLLIS       | STILES       | 1493 DOLLY MADISON CIRCLE | Snow Hill     | AL           |      36778 |
-- | LISETTE      | WHITTAKER    | 339 NORTHPARK DRIVE       | Montgomery    | AL           |      36197 |
-- | DEANDRE      | JAMISON      | 1571 HANES STREET         | Miami         | FL           |      33169 |
-- | CATHLEEN     | WHITMAN      | 1712 NORTHFIELD DRIVE     | Marshallville | GA           |      31057 |
-- ...
-- | RENATE       | LADD         | 652 LEWIS STREET          | Crystal City  | VA           |      22202 |
-- | MELONIE      | JIMENEZ      | 848 DOWNEY FINCH LANE     | East Monkton  | VT           |      05443 |
-- +--------------+--------------+---------------------------+---------------+--------------+------------+
-- 

SELECT DISTINCT CUST_FNAME, CUST_LNAME, CUST_STREET, CUST_CITY, CUST_STATE, CUST_ZIP
FROM LGCUSTOMER
JOIN LGINVOICE ON LGCUSTOMER.CUST_CODE = LGINVOICE.CUST_CODE
JOIN LGLINE ON LGINVOICE.INV_NUM = LGLINE.INV_NUM
JOIN LGPRODUCT ON LGLINE.PROD_SKU = LGPRODUCT.PROD_SKU
JOIN LGBRAND ON LGPRODUCT.BRAND_ID = LGBRAND.BRAND_ID
WHERE LGBRAND.BRAND_NAME = 'FORESTERS BEST'
  AND LGPRODUCT.PROD_CATEGORY = 'Top Coat'
  AND LGINVOICE.INV_DATE BETWEEN '2021-07-15' AND '2021-07-31'
ORDER BY CUST_STATE, CUST_LNAME, CUST_FNAME;
