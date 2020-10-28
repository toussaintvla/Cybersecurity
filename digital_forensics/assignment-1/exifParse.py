import sys
import os
import imghdr
from pathlib import Path
from exifread import process_file

file = image = ""

try:
    if len(sys.argv) == 1:
        raise IOError
    else:
        file = sys.argv[1]
except IOError:
    print("Error! - No Image File Specified!")
    
try:
    if not Path(file).exists():
        raise FileNotFoundError
    else:
        image_file = open(file, 'rb')
        ext = imghdr.what(file)
        if ext == 'jpg' or ext == 'jpeg':         
            print("Source File: {0}".format(file))
            tags = process_file(image_file)
            for key, val in tags.items():
                if key in ('Image Make', 'Image Model'):
                    i = key.split(" ")
                    print("{0}: {1}".format(i[1], val))
                if key in ('EXIF DateTimeOriginal'):
                    print("{0}: {1}".format("Original Date/Time", val))
            for key, val in tags.items():
                if key in ('GPS GPSLatitude', 'GPS GPSLongitude'):                    
                    coordinates = str(val)
                    coor = coordinates.split(",")
                    seconds = str(coor[2]).split("/")
                    print("{0}: {1} degrees, {2} minutes, {3} seconds".format( key[7:], coor[0][1:], float(coor[1][1:]), int(seconds[0][1:])/int(seconds[1][:-1]) ))
        else:
            raise Exception("Not expected file type! (JPG, JPEG)")
except FileNotFoundError:
    print("Error! - File Not Found!")
except Exception as e:
    print("Unexpected Error! - {}".format(e))