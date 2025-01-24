-- ## Problem 3:
-- 
-- The InstantStay Marketing team wants to learn the apartment that have more than average number 
-- of stays.
-- 
-- +---------+-------+
-- | HouseID | Stays |
-- +---------+-------+
-- |    1    |   4   |
-- |    4    |   4   |
-- +---------+-------+

SELECT 
    HouseID, COUNT(*) AS Stays
FROM 
    STAY
GROUP BY 
    HouseID
HAVING 
    COUNT(*) > (
        SELECT AVG(Stays) 
        FROM (
            SELECT 
                HouseID, COUNT(*) AS Stays
            FROM 
                STAY
            GROUP BY 
                HouseID) AS AvgStays);
