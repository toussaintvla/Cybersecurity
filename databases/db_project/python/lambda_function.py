import sys
import json
import os
import boto3
import logging
import rds_config
import pymysql

#rds settings
rds_host  = rds_config.db_host
name = rds_config.db_username
password = rds_config.db_password
db_name = rds_config.db_name

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
    name = event['firstName'] +' '+ event['lastName']

    item_count = 0

    with conn.cursor() as cur:
        cur.execute("select * from information_schema.tables LIMIT 1;")
        for row in cur:
            item_count += 1
            logger.info(row)
            # print(row)
    conn.commit()

    return {
        'body': json.dumps("%s and the Added items from RDS MySQL table %s" % (name, item_count)),
        'headers': {
        'Content-Type': 'text/plain'
        },
        'statusCode': 200
    }