import bz2
import os
import ftplib
import tarfile
import urllib.request

import cartopy.crs as ccrs
import cartopy.feature as cfeature
import matplotlib.pyplot as plt
import numpy as np

date = "20220901"
time = "1700"
band = "tir"
ch = "01"

lon_min = 85
lon_max = 205
lat_min = -60
lat_max = 60
n = 6000

extent_hmwr = (lon_min, lon_max, lat_min, lat_max)

tail = "fld.geoss.bz2"
fname_hmwr = f"{date}{time}.{band}.{ch}.{tail}"

_, cnt2tbb = np.loadtxt(f'count2tbb_v103/{band}.{ch}', unpack=True)

with bz2.open(fname_hmwr) as bz2fin:
    buf_cnt = bz2fin.read()
    data_cnt = np.frombuffer(buf_cnt, dtype = '>u2').reshape(n, n)
    
    data_tbb = cnt2tbb[data_cnt]


fig = plt.figure(figsize = (294/25.4, 210/25.4))
out_fig_path = f'{date}{time}-himawari_{band}{ch}.png'

fig.text(0.10, 0.97, f"{date} {time}UTC", fontsize=14)
fig.text(0.10, 0.94, f"BAND:{band}, CH:{ch}", fontsize=14)

# mapcrs = ccrs.PlateCarree()
# mapcrs = ccrs.NorthPolarStereo(central_longitude=140.0, true_scale_latitude=60.0) # 気象庁「日々の天気図」
# mapcrs = ccrs.Robinson(central_longitude=180.0) # ロビンソン図法
# mapcrs = ccrs.Mercator() # メルカトル図法
mapcrs = ccrs.Mollweide() # モルワイデ図法

ax = fig.add_axes([0.10, 0.10, 0.75, 0.75], projection=mapcrs)

ax.add_feature(cfeature.COASTLINE, linewidth=0.5, color="green")
ax.add_feature(cfeature.BORDERS, linewidth=0.5, linestyle=':', color="green")

ax.set_extent([117.0, 156.0, 18.0, 61.0], ccrs.PlateCarree())

ax.imshow(data_tbb, origin = 'upper', extent = extent_hmwr, interpolation = 'none',cmap = "gray_r", transform=ccrs.PlateCarree())
ax.gridlines(xlocs=np.arange(100, 180, 10),
             ylocs=np.arange(10, 90, 10),
             linestyle = 'dashed', color = 'green', linewidth=0.5)

# plt.show()
plt.savefig(out_fig_path, transparent = False)