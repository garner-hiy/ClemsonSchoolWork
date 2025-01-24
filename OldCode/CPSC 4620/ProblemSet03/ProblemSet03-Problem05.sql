-- ## Problem 5
-- 
-- Write a query to display the different years in which books have been published. 
-- Include each year only once and sort the results by year.
-- 
-- +-----------+
-- | BOOK_YEAR |
-- +-----------+
-- |   2018    |
-- |   2019    |
-- |   2020    |
-- |   2021    |
-- +-----------+

SELECT 
    DISTINCT BOOK_YEAR
FROM 
    BOOK
WHERE 
    BOOK_YEAR IS NOT NULL
ORDER BY 
    BOOK_YEAR;