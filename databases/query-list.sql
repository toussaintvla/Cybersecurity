SELECT product_code, product_name, list_price, discount_percent
FROM my_guitar_shop.products; -- 3.1

SELECT first_name, last_name,
CONCAT(last_name, ', ' , first_name) AS full_name
FROM my_guitar_shop.customers
WHERE last_name > 'M'
ORDER BY last_name ASC; -- 3.2

SELECT product_name, list_price, date_added
FROM my_guitar_shop.products
WHERE list_price > 550 and list_price < 2000
ORDER BY date_added DESC; -- 3.3

SELECT product_name, list_price, discount_percent,
ROUND((list_price * (discount_percent / 100)), 2) AS discount_amount,
ROUND((list_price - (list_price * (discount_percent / 100))), 2) AS discount_price
FROM my_guitar_shop.products
ORDER BY discount_price DESC
LIMIT 5; -- 3.4

SELECT item_id, item_price, discount_amount, quantity,
(item_price * quantity) AS price_total,
(discount_amount * quantity) AS discount_total,
((item_price * quantity) - (discount_amount * quantity)) AS item_total
FROM my_guitar_shop.order_items
WHERE ((item_price * quantity) - (discount_amount * quantity)) > 500
ORDER BY item_total DESC; -- 3.5

SELECT order_id, order_date, ship_date
FROM my_guitar_shop.orders
WHERE ship_date IS NULL
ORDER BY order_id DESC; -- 3.6

Select 100 AS price,
0.07 AS tax_rate,
(100 * 0.07) AS tax_amount,
(100) + (100 * 0.07) AS total; -- 3.7

SELECT categories.category_name, products.product_name, products.list_price
FROM my_guitar_shop.categories
INNER JOIN my_guitar_shop.products
ON categories.category_id=products.category_id
ORDER BY categories.category_name, products.product_name ASC; -- 4.1

SELECT customers.first_name, customers.last_name, addresses.line1, addresses.city, addresses.state, addresses.zip_code
FROM my_guitar_shop.customers
INNER JOIN my_guitar_shop.addresses
ON customers.customer_id=addresses.customer_id
WHERE customers.email_address = 'allan.sherwood@yahoo.com'
ORDER BY addresses.zip_code ASC; -- 4.2

SELECT DISTINCT customers.first_name, customers.last_name, addresses.line1, addresses.city, addresses.state, addresses.zip_code
FROM my_guitar_shop.customers
INNER JOIN my_guitar_shop.addresses
ON customers.shipping_address_id=addresses.address_id
ORDER BY addresses.zip_code ASC; -- 4.3

SELECT last_name, first_name, order_date, product_name, item_price, discount_amount, quantity
FROM customers c
INNER JOIN orders o
ON c.customer_id=o.customer_id
INNER JOIN order_items oi
ON oi.order_id=o.order_id
INNER JOIN products prd
ON prd.product_id=oi.product_id
ORDER BY last_name, order_date, product_name; -- 4.4

SELECT 'SHIPPED' AS ship_status, order_id, order_date FROM orders
WHERE ship_date IS NOT NULL
UNION
SELECT 'NOT SHIPPED' ship_status, order_id, order_date FROM orders
WHERE ship_date IS NULL
ORDER BY order_date; -- 4.5

INSERT INTO categories (category_name) VALUES
('Brass'); -- 5.1

UPDATE categories
SET category_name = "Woodwinds"
WHERE category_name = "Drums"; -- 5.2

DELETE FROM categories
WHERE category_id = '4'; -- 5.3

INSERT INTO products (
    product_id,
    category_id,
    product_code,
    product_name,
    description,
    list_price,
    discount_percent,
    date_added
)
VALUES (
    default,
    '4',
    'dgx_640',
    'Yamaha DGX 640 88-Key Digital Piano',
    'Long description to come.',
    '799.99',
    '0',
    NOW()
); -- 5.4

UPDATE products
SET discount_percent = "35"
WHERE product_name = "Fender Stratocaster"; -- 5.5

INSERT INTO customers (
    email_address,
    password,
    first_name,
    last_name
)
VALUES (
    "rick@raven.com",
    "",
    "Rick",
    "Raven"
); -- 5.6


UPDATE customers
SET first_name = "Al"
WHERE email_address = "allan.sherwood@yahoo.com"; -- 5.7

SELECT
COUNT(order_id) AS order_count,
SUM(tax_amount) AS tax_total,
AVG(tax_amount) AS tax_average
FROM orders; -- 6.1

SELECT c.category_name,
    COUNT(p.product_id) product_count,
    MAX(p.list_price) AS most_expensive_product
FROM categories AS c
INNER JOIN products p
ON c.category_id = p.category_id
GROUP BY c.category_name
ORDER BY product_count DESC;-- 6.2

SELECT
    c.email_address,
    SUM(o.item_price * o.quantity) AS item_price_total,
    SUM(o.discount_amount * o.quantity) AS discount_amount_total
FROM customers AS c
INNER JOIN orders AS ord ON ord.customer_id = c.customer_id
INNER JOIN order_items AS o ON o.order_id = ord.order_id
GROUP BY c.customer_id
ORDER BY item_price_total DESC; -- 6.3


SELECT c.email_address,
    COUNT(o.customer_id) AS order_count,
    SUM((oi.item_price – oi.discount_amount) * oi.quantity) AS order_total
FROM customers AS c
INNER JOIN orders AS o
ON (c.customer_id = o.customer_id)
INNER JOIN order_items AS oi
ON (o.order_id = oi.order_id)
GROUP BY c.email_address
HAVING COUNT(o.customer_id) > 1
ORDER BY item_price_total DESC;
SELECT SUM((item_price - discount_amount) * quantity)
FROM order_items
ORDER BY order_id; -- 6.4 - fix


SELECT
    c.email_address,
    COUNT(o.order_id) AS order_count,
    SUM(o.item_price - o.discount_amount) * COUNT(o.order_id) AS order_total
FROM customers AS c
INNER JOIN orders AS ord ON c.customer_id = ord.customer_id
INNER JOIN order_items AS o ON o.order_id = ord.order_id
where o.item_price>400
GROUP BY c.customer_id
HAVING order_count > 1
ORDER BY order_total DESC; -- 6.5 - fix



SELECT product_id, product_name, list_price
FROM products
WHERE list_price > (
    SELECT AVG(list_price)
    FROM products
    )
ORDER BY list_price DESC; -- 7.1

SELECT email_address, max(order_total) max_order_total,
        min(order_id) min_order_id
FROM (
    SELECT email_address, o.order_id,
    sum(quantity * (item_price - discount_amount)) order_total
    FROM customers c
    INNER JOIN orders o
    ON o.customer_id = c.customer_id
    INNER JOIN order_items oi on oi.order_id = o.order_id
    GROUP BY email_address, o.order_id
    ) DATA
GROUP BY email_address
ORDER BY 2 DESC; --7.2

SELECT prd.Product_name, prd.List_price, prd.Discount_percent
FROM products AS prd
WHERE prd.Discount_percent NOT IN (
        SELECT prd2.Discount_percent
        FROM products AS prd2
        WHERE prd.Product_name <> prd2.Product_name
        )
ORDER BY Product_name; -- 7.3

SELECT
    c.email_address, o.order_id AS oldest_order_id,
    o.order_date AS oldest_order_date
FROM customers c
INNER JOIN orders o
ON o.customer_id=c.customer_id
WHERE o.order_date IN (
    SELECT MIN(o.order_date)
    FROM orders o
    GROUP BY o.customer_id); -- 7.4

SELECT list_price,
FORMAT(list_price,1) AS price_format,
CONVERT(list_price, UNSIGNED) AS price_convert,
CAST(list_price AS UNSIGNED) AS price_cast
FROM  products
ORDER BY list_price ASC; -- 8.1

SELECT Date_added, CAST(Date_added AS DATE) AS added_date,
    DATE_FORMAT(CAST(Date_added AS DATE), '%Y-%m') AS added_char7,
    CAST(Date_added AS TIME) AS added_time
FROM products
ORDER BY Date_added; -- 8.2

SELECT list_price, discount_percent,
    ROUND(list_price * discount_percent / 100,2) AS discount_amount
FROM products
ORDER BY discount_amount ASC; -- 9.1

SELECT order_date,
    DATE_FORMAT(order_date, '%Y') AS order_year,
    DATE_FORMAT(order_date, '%b-%d-%Y') AS order_date_formatted,
    DATE_FORMAT(order_date, '%l:%i %p') AS order_time,
    DATE_FORMAT(order_date, '%m/%d/%y %H:%i') AS order_datetime
FROM orders; -- 9.2

SELECT Card_number,LENGTH(Card_number) AS Card_number_length,
RIGHT(Card_number,4) AS Last_four_digits,
IF(LENGTH(Card_number) < 16,
    CONCAT('XXXX-XXXXXX-X', (SUBSTRING(card_number,-4))),
    CONCAT('XXXX-XXXX-XXXX-', (SUBSTRING(card_number,-4)))) AS Formatted_number
FROM orders
ORDER BY Card_number; -- 9.3

SELECT order_id, order_date, DATE_ADD(order_date, INTERVAL 2 DAY) AS 'approx_ship_date',
ship_date, DATEDIFF(ship_date , order_date) AS 'days_to_ship'
FROM orders
WHERE ship_date IS NOT NULL
AND MONTH(order_date) = '3'
AND YEAR(order_date) = '2018'
ORDER BY order_id ASC; -- 9.4

CREATE INDEX zip_index
ON addresses (zip_code); -- 11.1

CREATE INDEX name_index
ON customers (last_name, first_name); -- 11.2

ALTER TABLE products
ADD COLUMN
(
    product_price DECIMAL(5,2) DEFAULT 9.99
); -- 11.3

ALTER TABLE customers
ADD COLUMN
(
    sms_number VARCHAR(20) NOT NULL
); -- 11.4

CREATE OR REPLACE VIEW customer_addresses AS
    SELECT
        c.customer_id,
        c.email_address,
        c.first_name,
        c.last_name,
        a1.line1 AS bill_line1,
        a1.line2 AS bill_line2,
        a1.city AS bill_city,
        a1.state AS bill_state,
        a1.zip_code AS bill_zip,
        a2.line1 AS ship_line1,
        a2.line2 AS ship_line2,
        a2.city AS ship_city,
        a2.state AS ship_state,
        a2.zip_code AS ship_zip
    FROM
        customers AS c
            INNER JOIN addresses AS a1
            ON c.customer_id=a1.customer_id
            AND c.billing_address_id=a1.address_id
            INNER JOIN addresses AS a2
            ON c.customer_id=a2.customer_id
            AND c.shipping_address_id=a2.address_id; -- 12.1

CREATE OR REPLACE VIEW order_item_products AS
    SELECT
        o.order_id,
        o.order_date,
        o.tax_amount,
        o.ship_date,
        oi.item_price,
        oi.discount_amount,
        (oi.item_price - oi.discount_amount) AS final_price,
        oi.quantity,
        (oi.item_price - oi.discount_amount) * oi.quantity as item_total,
        prd.product_name
    FROM orders o
    INNER JOIN order_items oi
    ON o.order_id=oi.order_id
    INNER JOIN products prd
    ON oi.product_id=prd.product_id; -- 12.2

CREATE OR REPLACE VIEW product_summary AS
    SELECT
        product_name,
        COUNT(order_id) AS order_count,
        SUM(item_total) AS order_total
    FROM order_item_products
    GROUP BY product_name; -- 12.3

CREATE OR REPLACE VIEW best_products AS
    SELECT order_total
    FROM product_summary
    ORDER BY order_total DESC LIMIT 5;-- 12.4

DROP PROCEDURE IF EXISTS test;
CREATE PROCEDURE test()
BEGIN
    DECLARE count_of_7 DECIMAL(10,2);

    SELECT COUNT(*) INTO count_of_7 FROM products;
    IF count_of_7 >= 7 THEN
        SELECT 'The number of products is greater than or equal to 7' AS message;
    ELSE
        SELECT 'The number of products is less than 7' AS message;
    END IF;
END -- 13.1


CREATE PROCEDURE test()
BEGIN
    DECLARE fact_var1 INT;
    DECLARE fact_var2 INT;
    DECLARE i INT;
    DECLARE common_var VARCHAR(400) DEFAULT 'Common factors of 10 and 20: ';

    DECLARE fact_var3 VARCHAR(40);

    SET fact_var1 = 10;
    SET fact_var2 = 20;
    SET i = 1;

    WHILE (i <= fact_var1) DO
        IF (i = 10) THEN
            SET common_var = CONCAT(common_var, i, '');
        ELSEIF (fact_var1 % i = 0 AND fact_var2 % i = 0) THEN
            SET common_var = CONCAT(common_var, i, ' ');
        ELSE
            SET fact_var3 = 'Do Nothing';
        END IF;
            SET i = i + 1;
    END WHILE;
    SELECT common_var AS message;
END -- 13.2


CREATE PROCEDURE test()
BEGIN
DECLARE product_name_var VARCHAR(50);
DECLARE list_price_var DECIMAL(9,2);
DECLARE row_not_found TINYINT DEFAULT FALSE;
DECLARE s_var VARCHAR(400) DEFAULT '';

DECLARE invoice_cursor CURSOR for
	SELECT
		product_name,
		list_price
	FROM
		products
	WHERE
		list_price > 700
	ORDER BY list_price DESC;

DECLARE CONTINUE HANDLER FOR NOT FOUND
	SET row_not_found = TRUE;

OPEN invoice_cursor;

FETCH invoice_cursor INTO product_name_var, list_price_var;
WHILE row_not_found = FALSE DO
    SET s_var = CONCAT(s_var,' " ', product_name_var,' " , " ',list_price_var,'" |');
	FETCH invoice_cursor INTO product_name_var, list_price_var;
END WHILE;

SELECT s_var AS message;
END -- 13.3 - fix


CREATE PROCEDURE test()
BEGIN
DECLARE duplicate_entry_for_key TINYINT DEFAULT FALSE;
    BEGIN
    DECLARE EXIT HANDLER FOR 1062
    SET duplicate_entry_for_key = TRUE;
    INSERT INTO categories VALUES (default, 'Guitars');
    SELECT '1 row was inserted.' AS message;
    END;
    IF duplicate_entry_for_key = TRUE THEN
    SELECT 'Row was not inserted - duplicate entry.' AS message;
    END IF;
END -- 13.4


DROP PROCEDURE IF EXISTS test;
DELIMITER //

CREATE PROCEDURE test (OUT message VARCHAR(55))
BEGIN
    DECLARE count_of_7 DECIMAL(10,2);

    SELECT COUNT(*) INTO count_of_7 FROM products;
    IF count_of_7 >= 7 THEN
        SELECT 'The number of products is greater than or equal to 7' INTO message;
    ELSE
        SELECT 'The number of products is less than 7' INTO message;
    END IF;
END //
DELIMITER ; -- 15.1


CREATE PROCEDURE test()
BEGIN
    DECLARE product_name_var VARCHAR(50);
    DECLARE list_price_var DECIMAL(9,2);
    DECLARE row_not_found TINYINT DEFAULT FALSE;
    DECLARE s_var VARCHAR(400) DEFAULT '';

    DECLARE invoice_cursor CURSOR for
        SELECT
            product_name,
            list_price
        FROM
            products
        WHERE
            list_price > 700
        ORDER BY list_price DESC;

    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET row_not_found = TRUE;

    OPEN invoice_cursor;

    FETCH invoice_cursor INTO product_name_var, list_price_var;
    WHILE row_not_found = FALSE DO
        SET s_var = CONCAT(s_var,' " ', product_name_var,' " , " ',list_price_var,'" |');
        FETCH invoice_cursor INTO product_name_var, list_price_var;
    END WHILE;

    SELECT s_var AS message;
END -- 15.2 -- fix



CREATE PROCEDURE insert_category(var_category_id INT, var_category_name varchar(50))
BEGIN
    DECLARE sql_error TINYINT DEFAULT FALSE;
    DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
    SET sql_error = TRUE;
    START TRANSACTION;
    UPDATE categories
    SET
        category_id = var_category_id
    WHERE
        category_name = var_category_name;
    IF sql_error = FALSE THEN
    COMMIT;
    ELSE
    ROLLBACK;
    END IF;
END -- 15.3 -- fix


CREATE FUNCTION discount_price(item_id_par INT)
RETURNS DECIMAL(9,2)
BEGIN
    DECLARE item_total_var DECIMAL(9,2);
    SELECT discount_price(item_id)*quantity
    INTO item_total_var
    FROM order_items
    WHERE  item_id= item_id_par;
RETURN item_total_var;
END -- 15.4 -- fix