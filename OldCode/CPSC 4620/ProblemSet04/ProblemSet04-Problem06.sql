-- ## Problem 6
-- 
-- Write a query to display the highest book cost in the system.
-- 
-- +----------------+
-- | Most Expensive |
-- +----------------+
-- |     129.95     |
-- +----------------+

SELECT MAX(BOOK_COST) AS `Most Expensive`
FROM BOOK;