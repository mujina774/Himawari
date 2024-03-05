import bz2
import os
import ftplib
import tarfile
import urllib.request

import cartopy.crs as ccrs
import cartopy.feature as cfeature
import matplotlib.pyplot as plt
import numpy as np

date = "20200707" 
time = "0300" 
band = "tir"  
ch = "01" 

lon_min = 85
lon_max = 205
lat_min = -60
lat_max = 60
n = 6000

extent_hmwr = (lon_min, lon_max, lat_min, lat_max)

server = "hmwr829gr.cr.chiba-u.ac.jp"
tail = "fld.geoss.bz2"
fname_hmwr = f"{date}{time}.{band}.{ch}.{tail}"
# url = f"{server}/{date[0:6]}/{band.upper()}/{fname_hmwr}"

if not os.path.isfile(fname_hmwr):
    ftp = ftplib.FTP(server)
    ftp.login('', '')           # anonymous login
    ftp.cwd(f'gridded/FD/V20190123/{date[0:6]}/{band.upper()}')

    with open(fname_hmwr ,'wb') as fhandle:
        ftp.retrbinary(f'RETR {fname_hmwr}', fhandle.write)
    print('Download finished: ', fname_hmwr,)

    ftp.quit()