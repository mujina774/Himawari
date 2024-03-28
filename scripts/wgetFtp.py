import wget

sv = 'ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20190123/'
yr = 2024
mn = 3
ym = str(yr) + str(mn).zfill(2)
ch = '/TIR/'
dy = 7
tm = 300
tl = '.tir.01.fld.geoss.bz2'

url = sv + ym + ch + ym + str(dy).zfill(2) + str(tm).zfill(4) + tl

fn = wget.download(url)
