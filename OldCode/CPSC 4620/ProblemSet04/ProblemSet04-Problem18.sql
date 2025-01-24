-- ## Problem 18
-- 
-- Write a query to display the patron ID, book number, patron first name and last name, and 
-- book title for all currently checked out books. (Remember to use the redundant relationship
-- described in the assignment instructions for current checkouts.) 
-- 
-- Sort the output by patron last name and book title.
-- 
-- +----------+------------+-------------+-------------+-----------------------------+
-- |   PAT_ID |   BOOK_NUM | PAT_FNAME   | PAT_LNAME   | BOOK_TITLE                  |
-- |----------+------------+-------------+-------------+-----------------------------|
-- |     1229 |       5252 | Gerald      | Burke       | Beyond the Database Veil    |
-- |     1229 |       5238 | Gerald      | Burke       | Conceptual Programming      |
-- |     1228 |       5242 | Homer       | Goodman     | C# in Middleware Deployment |
-- |     1212 |       5240 | Iva         | McClain     | iOS Programming             |
-- |     1172 |       5246 | Tony        | Miles       | Capture the Cloud           |
-- |     1207 |       5249 | Iva         | Ramos       | Starlight Applications      |
-- +----------+------------+-------------+-------------+-----------------------------+

SELECT C.PAT_ID, C.BOOK_NUM, P.PAT_FNAME, P.PAT_LNAME, B.BOOK_TITLE
FROM CHECKOUT C
JOIN PATRON P ON C.PAT_ID = P.PAT_ID
JOIN BOOK B ON C.BOOK_NUM = B.BOOK_NUM
WHERE C.CHECK_IN_DATE IS NULL
ORDER BY P.PAT_LNAME, B.BOOK_TITLE;

