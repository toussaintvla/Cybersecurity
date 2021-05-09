insert into winery(winery_id,winery_name,description,phone) values('1','New Rochelle Wines','New Rochelle Wines','914-637-6252');
insert into winery(winery_id,winery_name,description,phone) values('2','Wine Bazaar','Wine Bazaar','914-712-0260');
insert into winery(winery_id,winery_name,description,phone) values('3','Wine Gems','Wine Gems','914-840-4223');
insert into winery(winery_id,winery_name,description,phone) values('4','Carhart Wines & Liquors','Carhart Wines & Liquors','914-949-0940');
insert into winery(winery_id,winery_name,description,phone) values('5','Bottle Grove Wine and Spirits','Bottle Grove Wine and Spirits','914-468-6777');


insert into wine(wine_id,wine_name,type,year,description) values('1','Cabernet Sauvignon','red','1967','1967 Robert Mondavi Winery Cabernet Sauvignon');
insert into wine(wine_id,wine_name,type,year,description) values('2','Pinot Noir','red','1971','1971 Hanzell Vineyards Pinot Noir');
insert into wine(wine_id,wine_name,type,year,description) values('3','Malbec','red','1990','1990 Malbec Mendoza Argentina');
insert into wine(wine_id,wine_name,type,year,description) values('4','Chardonnay','white','1883','1883 Chardonnay by Wente Vineyards');
insert into wine(wine_id,wine_name,type,year,description) values('5','Merlot','red','1948','1948 Goudini Merlot');


insert into variety(variety_id,variety_name) values('1','red');
insert into variety(variety_id,variety_name) values('2','rose');
insert into variety(variety_id,variety_name) values('3','white');
insert into variety(variety_id,variety_name) values('4','sparkling');


insert into users(customer_id,user_name,lastname,firstname,password) values('1','vt905','Toussaint','Vladimir','vt9051234');


insert into orders(order_no,customer_id,date,address,discount,note) values('100','1','2020-02-13 00:00:00.000000','171 Titshall Ccl','1.4','white');
insert into orders(order_no,customer_id,date,address,discount,note) values('200','2','2020-01-19 00:00:00.000000','125 Barneshaw St','1.2','rose');
insert into orders(order_no,customer_id,date,address,discount,note) values('300','3','2021-10-15 00:00:00.000000','99 Kinsala Pl','1.1','sparkling');
insert into orders(order_no,customer_id,date,address,discount,note) values('400','4','2020-11-20 00:00:00.000000','6 Woodburne Pl','1.9','red');
insert into orders(order_no,customer_id,date,address,discount,note) values('500','5','2021-03-20 00:00:00.000000','50 Lefferts','1.7','red');


insert into items(item_id,customer_id,wine_id,order_no,quantity,date,price) values('1','1','1','400','2','2020-11-20 00:00:00.000000','79.99');


INSERT INTO customer VALUES ('1','Toussaint','Vladimir','50 Lefferts','Brooklyn','NY', '11225','USA','vladtous@gmail.com');
INSERT INTO customer VALUES ('2','Marzalla','Dimitria','171 Titshall Ccl','St Albans','WA', '7608','Australia','vt101@nyu.edu');
INSERT INTO customer VALUES ('3','LaTrobe','Anthony','125 Barneshaw St','Westleigh','WA','865 5','Australia', 'vt102@nyu.edu');
INSERT INTO customer VALUES ('4','Fong','Nicholas','99 Kinsala Pl','Stormlea','NSW','6400','Australia','vt103@nyu.edu');
INSERT INTO customer VALUES ('5','Stribling','James','6 Woodburne Pl','Legana','QLD','6377','Australia','vt104@nyu.edu');

insert into items(item_id,customer_id,wine_id,order_no,quantity,date,price) values('1','1','1','200','5','2021-04-10 00:00:00.000000','49.99');
insert into items(item_id,customer_id,wine_id,order_no,quantity,date,price) values('2','2','1','400','2','2020-11-20 00:00:00.000000','79.99');
insert into items(item_id,customer_id,wine_id,order_no,quantity,date,price) values('3','3','4','300','4','2021-04-10 00:00:00.000000','39.99');


SELECT *
FROM wine w, winery wi
WHERE w.wine_id = wi.winery_id
AND w.description IS NOT NULL;

SELECT * FROM orders;

UPDATE orders
SET date = '2020-02-13',
    address = '171 Titshall Ccl',
    discount = '1.40'
WHERE customer_id = 1 AND order_no = 100;

UPDATE orders
SET address = '171 Titshall CL'
WHERE customer_id = '1' AND order_no = '100';

DELETE FROM orders
WHERE order_no = '500';
