-- ## Problem 1:
-- 
-- The InstantStay Finance team require all the available information about the reservations 
-- where the commission rate of the channel is higher than 10%
-- 
-- +--------+---------+---------+-----------+---------------+-------------+-----------+--------------+
-- | StayID | HouseID | GuestID | ChannelID | StayStartDate | StayEndDate | StayPrice | StayDiscount |
-- +--------+---------+---------+-----------+---------------+-------------+-----------+--------------+
-- |   8    |    5    |    4    |     4     |  2024-08-01   | 2024-09-01  |   150.0   |     0.15     |
-- |   9    |    5    |   10    |     4     |  2024-08-01   | 2024-09-01  |   160.0   |     0.2      |
-- |   10   |    4    |    1    |     3     |  2024-09-10   | 2024-09-15  |   125.0   |     0.2      |
-- |   11   |    4    |    2    |     3     |  2024-09-10   | 2024-09-15  |   125.0   |     0.3      |
-- |   12   |    4    |    3    |     3     |  2024-09-10   | 2024-09-15  |  -130.25  |     0.3      |
-- |   13   |    4    |    7    |     3     |  2024-09-10   | 2024-09-15  |   200.0   |     0.0      |
-- +--------+---------+---------+-----------+---------------+-------------+-----------+--------------+

SELECT 
    S.StayID, S.HouseID, S.GuestID, S.ChannelID, S.StayStartDate, S.StayEndDate, S.StayPrice, S.StayDiscount
FROM 
    STAY S
JOIN 
    CHANNEL C ON S.ChannelID = C.ChannelID
WHERE 
    C.ChannelCommission > 0.10
ORDER BY
	S.StayID;