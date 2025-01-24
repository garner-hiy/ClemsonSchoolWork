-- ## Problem 6:
-- 
-- The InstantStay Owner Relationships team wants to send reminders to the owners who left the 
-- system. 
-- 
-- Collect the email address of the owners, notification date as one week later of their leave and last day of the month for financial closure.
-- 
-- +---------------------+------------------+------------------+
-- |     OwnerEmail      | NotificationDate | FinancialClosure |
-- +---------------------+------------------+------------------+
-- |  r.snow@xmail.com   |    2024-05-22    |    2024-05-31    |
-- | d.schmidt@xmail.com |    2024-06-19    |    2024-06-30    |
-- +---------------------+------------------+------------------+

SELECT
	OwnerEmail, 
    DATE_ADD(OwnerEndDate, INTERVAL 7 DAY) AS NotificationDate, 
    LAST_DAY(OwnerEndDate) AS FinancialClosure
FROM 
	OWNER
WHERE
	OwnerEndDate IS NOT NULL;
