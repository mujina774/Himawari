import wget

date = "20160510" 
time = "0400"    
band = "vis"
ch = "01"
      
svr = 'ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20151105/'
tail = 'fld.geoss.bz2'
fname = f"{date}{time}.{band}.{ch}.{tail}"

url = f"{svr}{date[0:6]}/{band.upper()}/{fname}"

print(url)
wget.download(url)
