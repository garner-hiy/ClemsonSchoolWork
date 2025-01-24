-- ## Problem 7
-- 
-- Write a query to display the lowest book cost in the system.
-- 
-- +-----------------+
-- | Least Expensive |
-- +-----------------+
-- |      49.95      |
-- +-----------------+

SELECT MIN(BOOK_COST) AS `Least Expensive`
FROM BOOK;
