DROP PROCEDURE IF EXISTS GetCustomerOrders;
DELIMITER $$

CREATE PROCEDURE GetCustomerOrders(IN  customerNo INT)
BEGIN
    SELECT order_no
    FROM orders
    WHERE order_no = customerNo;
END $$

DELIMITER ;

CALL GetCustomerOrders(100);


CREATE OR REPLACE VIEW wine_view AS
    SELECT
        v.variety_name, w.wine_name, w.year
    FROM
        variety v, wine w
    WHERE
        v.variety_name = w.type;

