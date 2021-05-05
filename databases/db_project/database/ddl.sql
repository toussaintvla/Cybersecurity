DROP PROCEDURE IF EXISTS GetCustomerOrders;
DELIMITER $$

CREATE PROCEDURE GetCustomerOrders(IN  customerNo INT, OUT customerLevel VARCHAR(20))
BEGIN

	DECLARE credit DEC(10,2) DEFAULT 0;

    -- get credit limit of a customer
    SELECT order_no
    INTO credit
    FROM orders
    WHERE customerNumber = customerNo;

    -- call the function
    SET customerLevel = CustomerLevel(credit);
END $$

DELIMITER ;



CALL GetCustomerOrders(-131,@customerLevel);
SELECT @customerLevel;




DELIMITER $$
CREATE FUNCTION CustomerCredit(credit DECIMAL(10,2))
RETURNS VARCHAR(20)
DETERMINISTIC
BEGIN
    DECLARE customerLevel VARCHAR(20);

    SELECT discount
    FROM orders
    WHERE  order_no = order_no_val;
    RETURN item_total_var;

    IF credit > 50000 THEN
		SET customerLevel = 'PLATINUM';
    ELSEIF (credit >= 50000 AND credit <= 10000) THEN
        SET customerLevel = 'GOLD';
    ELSEIF credit < 10000 THEN
        SET customerLevel = 'SILVER';
    END IF;
	RETURN (customerLevel);
END $$
DELIMITER ;


