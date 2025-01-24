-- ## Problem 3
-- 
-- Create a stored procedure named prc_inv_amounts to update the INV_SUBTOTAL, INV_TAX, 
-- and INV_TOTAL. The procedure takes the invoice number as a parameter.
-- - INV_SUBTOTAL is the sum of the LINE_TOTAL amounts for the invoicein the LINE table
-- - INV_TAX is the product of the INV_SUBTOTAL and the tax rate (8%)
-- - INV_TOTAL is the sum of the INV_SUBTOTAL and the INV_TAX
-- 
-- Check your prodecure code by calling it with an invoice number and then verifying that 
-- the data in the INVOICE table are updated apprporiately.
-- 
-- Make sure you include the appropriate DELIMITER statements in your solution!
-- 
DELIMITER $$

CREATE PROCEDURE prc_inv_amounts (
    IN p_inv_number INT
)
BEGIN
    DECLARE subtotal DECIMAL(10, 2);
    DECLARE tax DECIMAL(10, 2);
    DECLARE total DECIMAL(10, 2);

    SELECT SUM(LINE_TOTAL)
    INTO subtotal
    FROM LINE
    WHERE INV_NUMBER = p_inv_number;

    SET tax = subtotal * 0.08;
    SET total = subtotal + tax;

    UPDATE INVOICE
    SET INV_SUBTOTAL = subtotal,
        INV_TAX = tax,
        INV_TOTAL = total
    WHERE INV_NUMBER = p_inv_number;
END;
$$

DELIMITER ;
