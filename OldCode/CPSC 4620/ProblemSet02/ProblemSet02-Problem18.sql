-- ## Problem 18
-- 
-- Find the total value of the product inventory. The results are shown below.
-- 
-- +--------------------------+
-- | Total Value of Inventory |
-- +--------------------------+
-- |         15084.52         |
-- +--------------------------+
-- 
SELECT 
    ROUND(SUM(P_QOH * P_PRICE), 2) AS `Total Value of Inventory`
FROM 
    PRODUCT;