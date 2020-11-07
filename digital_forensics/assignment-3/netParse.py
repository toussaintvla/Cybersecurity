import sys
import sqlite3
import pathlib
from datetime import datetime

file = ""
sum = 0

try:
    if len(sys.argv) == 1:
        raise IOError
    else:
        file = sys.argv[1]
except IOError:
    print("Error! - No History File Specified!")

try:
    if not pathlib.Path(file).exists():
        raise FileNotFoundError
    else:
        print("Source File: {0}".format(file))
        conn = sqlite3.connect(file)
        c = conn.cursor()
        # Total # of Downloads
        c.execute("SELECT COUNT(*) FROM 'downloads';")
        totalDownloads = c.fetchone()
        print("Total Downloads: {0}".format(totalDownloads[0]))
        # Name of Longest Downloaded File
        c.execute("SELECT target_path, total_bytes, (end_time - start_time) AS elapsed_time FROM `downloads` ORDER BY elapsed_time DESC LIMIT 0,1;")
        file_name, total_bytes, elapsed_time = c.fetchone()
        file_name = file_name.split('\\')
        print("File Name: {0} {1}".format(file_name[-1], elapsed_time))
        # Bytes of Longest Downloaded File
        print("File Size: {0}".format(total_bytes))
        # # Unique Searched Items
        c.execute("SELECT DISTINCT * FROM `keyword_search_terms` GROUP BY term;")
        unique_searches = c.fetchall()
        for i in unique_searches:
            sum = sum + 1
        print("Unique Search Terms: {0}".format(sum))
        # # Most Recent Searched Item
        c.execute("SELECT DISTINCT datetime(urls.last_visit_time / 1000000 - 11644473600, 'unixepoch') AS date_time, keyword_search_terms.term FROM `keyword_search_terms` INNER JOIN `urls` ON keyword_search_terms.url_id = urls.id INNER JOIN `visits` ON urls.id = visits.url ORDER BY date_time DESC LIMIT 0,1;")
        recent_searched_date, recent_searched_item = c.fetchone()
        print("Most Recent Search: {0}".format(recent_searched_item))
        # # Date of Recent Searched Item
        print("Most Recent Search Date/Time: {0}".format(datetime.strptime(recent_searched_date, '%Y-%m-%d %H:%M:%S').strftime('%Y-%b-%d %H:%M:%S')))
        
        conn.close()
except FileNotFoundError:
    print("Error! - File Not Found!")    
except Exception as e:
    print("Unexpected Error! - {}".format(e))

