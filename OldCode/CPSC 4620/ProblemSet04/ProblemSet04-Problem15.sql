-- ## Problem 15
-- 
-- Write a query to display the author last name, author first name, and book number for each 
-- book written by that author. Sort the results by author last name, first name, and then book 
-- number. (25 rows)
-- 
-- +------------+------------+------------+
-- | AU_LNAME   | AU_FNAME   |   BOOK_NUM |
-- |------------+------------+------------|
-- | Aggerwal   | Manish     |       5242 |
-- | Beatney    | Rachel     |       5240 |
-- | Bruer      | Hugo       |       5243 |
-- | Bruer      | Hugo       |       5246 |
-- | Chiang     | Xia        |       5244 |
-- | Chiang     | Xia        |       5249 |
-- | Chiang     | Xia        |       5252 |
-- | Durante    | Reba       |       5235 |
-- | Lake       | Robert     |       5245 |
-- | Lake       | Robert     |       5247 |
-- | McGill     | Rachel     |       5241 |
-- | McGill     | Rachel     |       5254 |
-- | Palca      | Julia      |       5238 |
-- | Paulsen    | Connie     |       5239 |
-- | Paulsen    | Connie     |       5241 |
-- | Paulsen    | Connie     |       5251 |
-- | Pearson    | Perry      |       5250 |
-- | Reeves     | Benson     |       5237 |
-- | Reeves     | Benson     |       5253 |
-- | Salvadore  | Carmine    |       5239 |
-- | Salvadore  | Carmine    |       5248 |
-- | Sheel      | Lawrence   |       5239 |
-- | Tankersly  | Trina      |       5244 |
-- | Walsh      | Neal       |       5236 |
-- | Walsh      | Neal       |       5250 |
-- +------------+------------+------------+

SELECT A.AU_LNAME, A.AU_FNAME, W.BOOK_NUM
FROM AUTHOR A
JOIN WRITES W ON A.AU_ID = W.AU_ID
ORDER BY A.AU_LNAME, A.AU_FNAME, W.BOOK_NUM;

