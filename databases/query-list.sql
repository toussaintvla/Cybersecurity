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
(100) + (100 * 0.07) AS total -- 3.7

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

