-- ## Problem 03
-- 
-- Write a query to display the first name, last name, and email address of employees hired from 
-- May 1, 2011, to December 31, 2012. Sort the output by last name and then by first name.
-- 
-- Your results should look like this:
-- +-------------+---------------+--------------------------+
-- | EMP_FNAME   | EMP_LNAME     | EMP_EMAIL                |
-- |-------------+---------------+--------------------------|
-- | SONDRA      | ALBRIGHT      | SO.ALBRI96@LGCOMPANY.COM |
-- | WALLY       | ANDERSEN      | A.WALLY94@LGCOMPANY.COM  |
-- | SUE         | ASH           | S.ASH98@LGCOMPANY.COM    |
-- | ALIDA       | BLACKWELL     | A.BLACKW99@LGCOMPANY.COM |
-- | PHOEBE      | BLEDSOE       | P.BLEDSO99@LGCOMPANY.COM |
-- | VALARIE     | BLEDSOE       | V.BLEDSO99@LGCOMPANY.COM |
-- | PHYLISS     | BOUCHARD      | P.BOUCHA95@LGCOMPANY.COM |
-- | LANE        | BRANDON       | B.LANE97@LGCOMPANY.COM   |
-- | BRADFORD    | BRAY          | B.BRADFO96@LGCOMPANY.COM |
-- | VILMA       | BUNCH         | V.BUNCH96@LGCOMPANY.COM  |
-- ...
-- | THURMAN     | WILKINSON     | W.THURMA99@LGCOMPANY.COM |
-- | ALYSON      | WILLARD       | A.WILLAR1@LGCOMPANY.COM  |
-- +-------------+---------------+--------------------------+
-- 
SELECT EMP_FNAME, EMP_LNAME, EMP_EMAIL
FROM LGEMPLOYEE
WHERE EMP_HIREDATE BETWEEN '2011-05-01' AND '2012-12-31'
ORDER BY EMP_LNAME, EMP_FNAME;
