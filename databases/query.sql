SELECT customers.first_name, customers.last_name, addresses.line1, addresses.city, addresses.state, addresses.zip_code
FROM my_guitar_shop.customers
INNER JOIN my_guitar_shop.addresses
ON customers.customer_id=addresses.customer_id
WHERE customers.email_address = 'allan.sherwood@yahoo.com'
ORDER BY addresses.zip_code ASC;