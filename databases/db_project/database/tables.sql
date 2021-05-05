DROP TABLE IF EXISTS wine;
DROP TABLE IF EXISTS winery;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS orders;
DROP TABLE IF EXISTS items;
DROP TABLE IF EXISTS variety;

CREATE TABLE wine (
    wine_id int(5) NOT NULL auto_increment,
    wine_name varchar(50) DEFAULT '' NOT NULL,
    type varchar(10) DEFAULT '' NOT NULL,
    year int(4) DEFAULT '0' NOT NULL,
    description blob,
    PRIMARY KEY (wine_id)
);

CREATE TABLE winery (
    winery_id int(4) NOT NULL auto_increment,
    winery_name varchar(100) DEFAULT '' NOT NULL,
    description blob,
    phone varchar(15),
    PRIMARY KEY (winery_id)
);

CREATE TABLE customer (
    customer_id int(5) NOT NULL auto_increment,
    lastname varchar(50) NOT NULL,
    firstname varchar(50) NOT NULL,
    address varchar(50) NOT NULL,
    city varchar(20) NOT NULL,
    state varchar(20),
    zip varchar(5),
    country varchar(20),
    email varchar(30) NOT NULL,
    PRIMARY KEY (customer_id),
    KEY names (lastname, firstname)
);

CREATE TABLE users (
    customer_id int(4) DEFAULT '1' NOT NULL,
    user_name varchar(50) DEFAULT '' NOT NULL,
    lastname varchar(50) NOT NULL,
    firstname varchar(50) NOT NULL,
    password varchar(15) DEFAULT '' NOT NULL,
    PRIMARY KEY (user_name)
);

CREATE TABLE orders (
    order_no int(5) NOT NULL,
    customer_id int(5) DEFAULT '1' NOT NULL,
    date timestamp(6),
    address varchar(50) NOT NULL,
    discount float(3,1) DEFAULT '0.0',
    note varchar(120),
    PRIMARY KEY (order_no, customer_id)
);

CREATE TABLE items (
    item_id int(3) DEFAULT '1' NOT NULL,
    customer_id int(5) DEFAULT '1' NOT NULL,
    wine_id int(4) DEFAULT '1' NOT NULL,
    order_no int(5) NOT NULL,
    quantity int(3),
    date timestamp(6),
    price float(5, 2),
    PRIMARY KEY (item_id, customer_id, order_no, wine_id)
);

CREATE TABLE variety (
    variety_id int(3) DEFAULT '1' NOT NULL,
    variety_name varchar(20),
    PRIMARY KEY (variety_id)
);