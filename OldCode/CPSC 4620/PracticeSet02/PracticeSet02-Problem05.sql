-- ## Problem 5
-- 
-- During the guest user analysis, developers realized there could be duplicate users in the 
-- system. Check for the guests with the same name but different GuestIDs to check whether 
-- they are duplicate or not.
-- 
-- +---------+----------------+---------------+-------------------+--------------+
-- | GuestID | GuestFirstName | GuestLastName |    GuestEmail     | DUP Guest ID |
-- +---------+----------------+---------------+-------------------+--------------+
-- |   12    |     Ronald     |     Oneil     | r.oneil@tmail.com |      7       |
-- |   11    |      Jada      |     Swan      | j.swan@tmail.com  |      9       |
-- |    9    |      Jada      |     Swan      | j.swan@xmail.com  |      11      |
-- |    7    |     Ronald     |     Oneil     | r.oneil@xmail.com |      12      |
-- +---------+----------------+---------------+-------------------+--------------+

SELECT 
    G.GuestID, G.GuestFirstName, G.GuestLastName, G.GuestEmail, GG.GuestID AS `DUP Guest ID`
FROM 
    GUEST G
JOIN 
    GUEST GG ON G.GuestFirstName = GG.GuestFirstName AND G.GuestLastName = GG.GuestLastName
	AND G.GuestID != GG.GuestID
ORDER BY 
    G.GuestID DESC;
