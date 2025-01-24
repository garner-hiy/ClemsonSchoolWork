-- ## Problem 2
-- 
-- Create the INVOICE table structure shown in the ProblemSet09 ERD:
-- - INV_NUM should store integer values. 
-- - INV_DATE should store date values. 
-- - INV_AMOUNT should support up to eight digits to the left of the decimal place and 
--   two digits to the right of the decimal place. 
-- - Use INV_NUM as the primary key.  
-- - Note that the CUST_NUM is the foreign key to CUSTOMER, so be certain to enforce 
--   referential integrity.
-- 

CREATE TABLE INVOICE (
    INV_NUM INT NOT NULL,
    INV_DATE DATE,
    INV_AMOUNT DECIMAL(10, 2) DEFAULT 0.00,
    CUST_NUM INT,
    PRIMARY KEY (INV_NUM),
    FOREIGN KEY (CUST_NUM) REFERENCES CUSTOMER (CUST_NUM)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);