import sys
import json
import os
import boto3
import logging
import rds_config
import pymysql

#rds settings
rds_host = rds_config.db_host
name     = rds_config.db_username
password = rds_config.db_password
db_name  = rds_config.db_name

logger = logging.getLogger()
logger.setLevel(logging.INFO)

try:
    conn = pymysql.connect(host=rds_host, user=name, passwd=password, db=db_name, connect_timeout=5)
except pymysql.MySQLError as e:
    logger.error("ERROR: Unexpected error: Could not connect to MySQL instance.")
    logger.error(e)
    sys.exit()

logger.info("SUCCESS: Connection to RDS MySQL instance succeeded")
def lambda_handler(event, context):
    """
    This function fetches content from MySQL RDS instance
    """
    #name       = event['firstName'] +' '+ event['lastName']
    order_no    = event["order_no"]
    customer_id = event["customer_id"]
    date        = event["date"]
    address     = event["address"]
    discount    = event["discount"]
    note        = event["note"]

    create = "INSERT INTO orders(order_no,customer_id,date,address,discount,note) VALUES(%s, %s, %s, %s, %s, %s);"
    values = (order_no, customer_id, date, address, discount, note)
    read   = "SELECT * FROM orders;"
    update = 'UPDATE orders SET address = "{}" WHERE customer_id = {} AND order_no = {};'.format(address, customer_id, order_no)
    delete = "DELETE FROM orders WHERE order_no = {};".format(order_no)

    item_count = 0
    response   = []

    if event["condition"] == "create":
        with conn.cursor() as cur:
            cur.execute(create, values)
            conn.commit()
            cur.execute("SELECT * FROM orders WHERE order_no = {}".format(order_no))
            for row in cur:
                item_count += 1
                logger.info(row)
                #print(row)
                response.append(row)
            conn.commit()

    if event["condition"] == "read":
        with conn.cursor() as cur:
            cur.execute(read)
            for row in cur:
                item_count += 1
                logger.info(row)
                # print(row)
                response.append(row)
            conn.commit()

    if event["condition"] == "update":
        with conn.cursor() as cur:
            cur.execute(update)
            conn.commit()

    if event["condition"] == "delete":
        with conn.cursor() as cur:
            cur.execute(delete)
            conn.commit()
            cur.execute(read)
            for row in cur:
                item_count += 1
                logger.info(row)
                #print(row)
                response.append(row)
            conn.commit()

    return {
        'body': "Number of Rows: {}".format(item_count),
        'response':"Response: {}".format(response),
        'headers': {
        'Content-Type': 'text/plain'
        },
        'statusCode': 200
    }