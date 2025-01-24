-- ## Problem 12
-- 
-- Write a query to display the patron ID, book number, and days kept for each checkout. 
-- "Days Kept" is the difference from the date on which the book is returned to the date it was
-- checked out. Sort the results by days kept in descending order, then by patron ID, 
-- and then by book number. (68 rows)
-- 
-- [NOTE: Rows omitted from the target results for clarity.  
--  The autograder will check for  ALL required output.]
-- 
-- 
-- +--------+------+-----------+
-- | PATRON | BOOK | Days Kept |
-- +--------+------+-----------+
-- |  1160  | 5240 |    78     |
-- |  1165  | 5235 |    78     |
-- |  1185  | 5240 |    78     |
-- |  1219  | 5248 |    78     |
-- |  1222  | 5240 |    78     |
-- |  1226  | 5244 |    78     |
-- |  1202  | 5236 |    77     |
-- |  1218  | 5236 |    77     |
-- |  1228  | 5237 |    77     |
-- |  1220  | 5235 |    76     |
-- |  1209  | 5238 |    74     |
-- |  1210  | 5242 |    74     |
-- |  1210  | 5235 |    73     |
-- |  1225  | 5235 |    73     |
-- |  1160  | 5237 |    72     |
-- |  1160  | 5240 |     9     |
-- |  1183  | 5236 |     8     |
-- |  1184  | 5240 |     8     |
-- ... rows ommitted...
-- |  1210  | 5244 |     0     |
-- |  1213  | 5236 |     0     |
-- |  1214  | 5240 |     0     |
-- |  1172  | 5246 |           |
-- |  1207  | 5249 |           |
-- |  1212  | 5240 |           |
-- |  1228  | 5242 |           |
-- |  1229  | 5238 |           |
-- |  1229  | 5252 |           |
-- +--------+------+-----------+

SELECT PAT_ID AS `PATRON`, BOOK_NUM AS `BOOK`, 
       DATEDIFF(COALESCE(CHECK_IN_DATE, CURRENT_DATE), CHECK_OUT_DATE) AS `Days Kept`
FROM CHECKOUT
ORDER BY `Days Kept` DESC, PAT_ID ASC, BOOK_NUM ASC;
