-- ## Problem 2:
-- 
-- The InstantStay Finance team requires average price per stay rounded to two decimal places for 
-- all the houses in the system. However, ensure that you do not include the cancelled stays with 
-- negative payment information.
-- 
-- +---------+---------+
-- | HouseID | Payment |
-- +---------+---------+
-- |    1    |  110.0  |
-- |    2    |  118.0  |
-- |    4    | 129.17  |
-- |    5    | 127.75  |
-- +---------+---------+

SELECT 
    HouseID, ROUND(AVG(FinalPrice), 2) AS Payment
FROM (
    SELECT 
        S.HouseID, S.StayPrice * (1 - S.StayDiscount) AS FinalPrice
    FROM 
        STAY S
    WHERE 
        S.StayPrice > 0
) AS StayWithFinalPrice
GROUP BY 
    HouseID
ORDER BY 
    HouseID ASC;
