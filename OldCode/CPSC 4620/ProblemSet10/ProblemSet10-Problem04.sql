-- ## Problem 4
-- 
-- Create a procedure named prc_cus_balance_update that will take the invoice number 
-- as a parameter and update the customer balance.
-- 
-- Hint: You can use DECLARE to define a TOTINV numeric variable that holds the computed 
-- invoice total.
-- 
-- Check your prodecure code by calling it with an invoice number and then verifying that 
-- the data in the CUSTOMER table are updated apprporiately.  You will need to use your
-- prc_inv_amounts procedure to make sure things work correctly!
-- 
-- Make sure you include the appropriate DELIMITER statements in your solution!
-- 
DELIMITER $$

CREATE PROCEDURE prc_cus_balance_update (
    IN p_inv_number INT
)
BEGIN
    DECLARE totinv DECIMAL(10, 2);
    DECLARE cus_code INT;

    CALL prc_inv_amounts(p_inv_number);

    SELECT INV_TOTAL, CUS_CODE
    INTO totinv, cus_code
    FROM INVOICE
    WHERE INV_NUMBER = p_inv_number;

    UPDATE CUSTOMER
    SET CUS_BALANCE = CUS_BALANCE + totinv
    WHERE CUS_CODE = cus_code;
END;
$$

DELIMITER ;