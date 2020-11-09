import sys
import pathlib
import csv
import logging
import ipaddress
from datetime import datetime

file = ""
time_date_conn = []
source_ips = []
dest_ips = []
total_bytes_sum = []
source_ips_sum = dest_ips_sum = 0

try:
    if len(sys.argv) == 1:
        raise IOError
    else:
        file = sys.argv[1]
except IOError:
    print("Error! - No Log File Specified!")

try:
    if not pathlib.Path(file).exists():
        raise FileNotFoundError
    else:
        print("Source File: {0}".format(file))
        with open(file, newline='') as csvfile:
            reader = csv.reader(csvfile, delimiter=' ', quotechar='|')
            for row_list in reader:
                for row in row_list:
                    network_connections = row.split(",")
                    source_ip, dest_ip, port, total_bytes = network_connections[1], network_connections[2], network_connections[4], network_connections[7]
                    if port in ('1337', '1338', '1339', '1340') and source_ip not in source_ips:
                        source_ips.append(source_ip)
                        source_ips_sum += 1
                    if port in ('1337', '1338', '1339', '1340') and dest_ip not in dest_ips:
                        dest_ips.append(dest_ip)
                        dest_ips_sum += 1
                    if dest_ip in dest_ips:
                        time_date_established = network_connections[0]
                        time_date_conn.append(float(time_date_established))

            time_date_conn.sort()
            source_ips.sort(key = ipaddress.IPv4Address)
            dest_ips.sort(key = lambda ips: int(ips.rsplit('.', 1)[1]), reverse=True)
            dest_ips.sort()
            # data_totals = list(zip(dest_ips, total_bytes_sum))

            print("Systems Infected: {0} \nInfected System IPs: \n{1}".format(source_ips_sum, source_ips))
            print("C2 Servers: {0} \nC2 Server IPs: \n{1}".format(dest_ips_sum, dest_ips))
            print("First C2 Connections: {0} UTC".format(datetime.fromtimestamp(time_date_conn[0]).strftime('%Y-%b-%d %H:%M:%S')))
            # print("C2 Data Totals: {0}".format(sorted(data_totals)))

except FileNotFoundError:
    print("Error! - File Not Found!")
except Exception as e:
    print("Unexpected Error! - {}".format(e))