# [Himawari-8/9 data processing](http://quicklooks.cr.chiba-u.ac.jp/~himawari_movie/rd_gridded.html)

CEReS, Chiba university, Japan
October, 20 2017
November, 28 2018 modified

## About Himawari-8/9

The Himawari-8/9 is a geostationary satellite launched on October 4, 2014 which has a new payload called the Advanced Himawari Imager (AHI). The specifications are improved from that of the imagers on board MTSAT's. In each 10-minute period, the AHI will scan the Full Disk once, the Japan Area and Target Area (ie. Tropical cyclone ) four times. Here we demonstrate the visualization of Himawari-8/9 grided data provided by CEReS/Chiba university.

## The bands and sampling gradations

| CEReS gridded data
Bands and Numbers | JMA's Himawari8/9 Bands | sampling gradation | Pixel x Line | gridded resolution |
| --- | --- | --- | --- | --- |
| EXT | 01 | Band 03 (0.64 μm) | 2048/11bit | 24000 x 24000 | 0.005 degree (approx. 500 m) |
| VIS | 01 | Band 01 (0.47 μm) | 12000 x 12000 | 0.01 degree (approx. 1km) |
| 02 | Band 02 (0.51 μm) |
| 03 | Band 04 (0.86 μm) |
| SIR | 01 | Band 05 (1.6 μm) | 6000 x 6000 | 0.02 degree (approx. 2km) |
| 02 | Band 06 (2.3 μm) |
| TIR | 01 | Band 13 (10.4 μm) | 4096/12bit | 6000 x 6000 | 0.02 degree (approx. 2km) |
| 02 | Band 14 (11.2 μm) |
| 03 | Band 15 (12.4 μm) |
| 04 | Band 16 (13.3 μm) | 2048/11bit |
| 05 | Band 07 (3.9 μm) | 16384/14bit |
| 06 | Band 08 (6.2 μm) | 2048/11bit |
| 07 | Band 09 (6.9 μm) |
| 08 | Band 10 (7.3 μm) | 4096/12bit |
| 09 | Band 11 (8.6 μm) |
| 10 | Band 12 (9.6 μm) |

**Common Specifications: Covered area: 85 E -- 205 E (155 W), 60 N -- 60 S** (same as our gridded data for MTSAT2)
**2byte "unsigned short" binary data without any header and footer, and "big endian" data order
Data reading orders: West to East (left to right) and North to South (up to down).
Stored binary data is: HS data thenselves (CCT count like).**

All bands data separately compressed by bzip2 (\*.bz2).

## Preparation

Please prepare grads or GMT to visualize the data.

## Processing the Hiamwari-8/9 Gridded data

The Hiamwari-8/9 gridded data is open to web at FTP server (ftp://hmwr829gr.cr.chiba-u.ac.jp) that directry is stratified by the year and month combined number directories (i.e. /201507/). The bands as ext (extension), vis (visible), tir (thermal infrared), sir (short wave infrared) are under the year month numberd directory.
  
For example, the data of July 7th, 2015 00:00(UTC) Band13 (10.4 micro meter) is as below.

ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20151105/201507/TIR/201507070000.tir.01.fld.geoss.bz2

To download the data, confirm the full path includes file name that composed of date and band, use "wget" command. This instruction will continue with thermal IR band (band13, 10.4 micro meter).

 wget ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20151105/201507/TIR/201507070000.tir.01.fld.geoss.bz2

The grided data that distributed from CEReS via FTP is compressed file by bz2 archive format. Extract it by "bunzip2" command.

 bunzip2 201507070000.tir.01.fld.geoss.bz2

The data file type is unsigned short integer, big endian binary. Most of personal computer CPUs such as x86\_64 are supported a liitle endian while workstations such as Sun WS, PowerPC supported big endian. To byte swap the data order, use "dd" command with a byte swap option. If you use the -w option in xyz2grd command, you can skip this step.

 dd if=201507070000.tir.01.fld.geoss of=little-count.geoss conv=swab

Confirm the data value using "od" command with the option "-d" that means unsigned short. The output file "little-count.geoss" is a converted little endian data. Check the data value as follow.

 od -d -An -w2 little-count.geoss |sort

The value will be shown with the range in 1 to 4096 (Band 13). To make an image of Himawari-8 data (count value), follow these bellow ways (GMT, GrADS).

## Conversion count value into tbb

To convert from count value to tbb, execute sample program using lookup table. The convert program is available from [count2tbb\_v101.tgz](ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/support/count2tbb_v101.tgz).

 wget ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/support/count2tbb\_v101.tgz
 tar zxvf count2tbb\_v101.tgz
 cd count2tbb

The main source code count2tbb05.c, count2tbb10.c, and count2tbb20.c correspond to 500m resolution data (ext01), 1km resolution data (vis01-03), and 2km resolution data (sir01,02, tir01-10), respectively. The conversion look-up tables from count vale to tbb are ext.01, sir\[01-02\], and tir.\[01-10\], respectively. This time we demonstrate tir01 data of 2 km resolution, so we use count2tbb20.c program and lookup table tir.01.

 gcc count2tbb20.c -o c2t20.x

"c2t20.x" is an executable file to convert from count value to tbb. Move the little endian data (little-count.geoss) that you just prepared in the same directory, do the conversion as follows.

  ./c2t20.x little-count.geoss tir.01

Then a converted file "grid20.dat" appears, which is 4 bytes real tbb. Check the data value as follow.

 od -tf4 -An -w4 grid20.dat |sort

"count2tbb.sh" is a shell code that collectively performs a series of conversion from data download to tbb conversion. Please take advantage to properly specify the time parameters and band.

## Visualization with GMT ver.4 plot tool

Here, describes the procedure for displaying the count data (little-count.geoss). GMT setting: Set a bordar line as solid line.

 gmtset BASEMAP\_TYPE PLAIN
 gmtset PAPER\_MEDIA=a4+
 gmtset COLOR\_BACKGROUND black
 gmtset COLOR\_FOREGROUND white
 gmtset COLOR\_NAN black

 gmtset FRAME\_PEN=1.25p,0/0/0 #Frame color
 gmtset GRID\_PEN\_PRIMARY=0.10p,90/90/90 #Grid color
 gmtset TICK\_PEN=0.5p,0/0/0 # tick font color

First, make a color pallet file. The "makecpt" is a utility that will help you make color palette tables. The color style is set to gray scale (-Cgray), the vale range is set to 0 to 4096, 410 steps. -Z option creates a continuous cpt file while default is discontinuous.

 makecpt -Cgray -T0/4096/410 -Z > count.cpt

Convert binary data to GMT type format.
The xyz2grd reads a z or xyz table and creates a binary grid file. -R (regional range) must be same as that of original dataset dimensions. -Z option sets exact specification of incoming 1-column z-table. If data is in row format, state if first row is at T(op) or B(ottom). Then, append L or R to indicate starting point in row. Then specify one of the following data types,

        c  signed 1-byte character.
        u  unsigned 1-byte character.
        h  signed short 2-byte integer.
        H  unsigned short 2-byte integer.
        i  signed 4-byte integer.
        I  unsigned 4-byte integer.
        l  signed long (4- or 8-byte) integer.
        f  4-byte floating point single precision.
        d  8-byte floating point double precision.

To swap byte-order in 2-byte words, append w in -Z option.

 xyz2grd little-count.geoss -Glittle-count.gmt -I0.02/0.02 -R85/205/-60/60 -F -N4096 -ZTLH

Here little\_endian.gmt file is created. Once converted to GMT (netCDF) format, you do not need to do this again. Now draw the image.
The range (-R) is set to area you defined.

 grdimage little-count.gmt -JQ140/15 -Ccount.cpt -K -P -R85/205/-60/60 > ir1-count.eps

 pscoast -Ba20g20/a15g15eWSn -J -R -Di -K -N1/2t7.5\_7.5:0/0/255/0 -W1/0/255/0 -O >> ir1-count.eps

 echo "140 62 18 0 0 CB Himawari-8 Band13 20150707 00:00UTC" |pstext -R -J -G0/0/0 -O -K -N >> ir1-count.eps

 psscale -D7.5/-1/12/0.5h -Ccount.cpt -B512/:"\[count\]": -O >> ir1-count.eps

Convert eps into png. -E option set to the density 300 dpi.

 ps2raster ir1-count.eps  -P -A -E300 -Qt -Qg -Tg && eog ir1-count.png

ir1-count.png will be created.

## For GMT ver.5 users

GMT setting: Set a bordar line as solid line and define font size and title position.

 gmt set MAP\_FRAME\_TYPE plain
 gmt set COLOR\_BACKGROUND black
 gmt set COLOR\_FOREGROUND white
 gmt set COLOR\_NAN gray
 gmt set PS\_MEDIA a4
 gmt set FONT\_TITLE 13p
 gmt set MAP\_TITLE\_OFFSET -0.2c

 gmt makecpt -Cgray -T0/4096/410 -Z > count.cpt

Convert binary data to GMT type format.
The xyz2grd reads a z or xyz table and creates a binary grid file. -R (regional range) must be same as that of original dataset dimensions. -Z option sets exact specification of incoming 1-column z-table. If data is in row format, state if first row is at T(op) or B(ottom). Then, append L or R to indicate starting point in row. Then specify one of the following data types,

        c  signed 1-byte character.
        u  unsigned 1-byte character.
        h  signed short 2-byte integer.
        H  unsigned short 2-byte integer.
        i  signed 4-byte integer.
        I  unsigned 4-byte integer.
        l  signed long (4- or 8-byte) integer.
        f  4-byte floating point single precision.
        d  8-byte floating point double precision.

 gmt xyz2grd little-count.geoss -Glittle-count.gmt -I0.02/0.02 -R85/205/-60/60 -r -di4096 -ZTLH

Here little\_endian.gmt file is created. Now draw the image.
Draw the data. The range (-R) is set to area you defined.

 gmt grdimage little-count.gmt -JQ140/15 -Ccount.cpt -K -P -R85/205/-60/60 > ir1-count.eps

 gmt pscoast -BWSne+t"Himawari-8 Band13 20150707 00:00UTC" -Bxa20g20 -Bya20g20 -J -R -Di -K -N1/0.25p,0/255/0,solid -W0.25p,0/255/0,solid -O >> ir1-count.eps

 gmt psscale -D7.5/-1/12/0.5h -Ccount.cpt -B512/:"\[count\]": -O >> ir1-count.eps

 gmt psconvert ir1-count.eps  -P -A -E300 -Qt -Qg -Tg && eog ir1-count.png

## For GrADS users

Save bellow script as grads.ctl.

 DSET little-count.geoss
 UNDEF  4098
 options YREV LITTLE\_ENDIAN
 TITLE  Himawari8 count vale
 XDEF 6000 LINEAR 84.99 0.02
 YDEF 6000 LINEAR -60.01 0.02
 ZDEF  1 linear    1 1
 TDEF 1  LINEAR   00z7Jul2015 10mn
 VARS 1
 count 0 -1,40,2 Himawari8 count value
 endvars

For 4 bytes data, modify as the variable "count 0 99 Himawari8". open GrADS.

 grads -l

Type follow commands.

 open grads.ctl
 set grads off
 set gxout shaded
 set grid on 1 15
 set xlint 20
 set ylint 20

 set rgb 30 25 25 25
 set rgb 31 51 51 51
 set rgb 32 76 76 76
 set rgb 33 102 102 102
 set rgb 34 127 127 127
 set rgb 35 153 153 153
 set rgb 36 178 178 178
 set rgb 37 204 204 204
 set rgb 38 230 230 230
 set rgb 39 255 255 255

 set clevs  410 820 1230 1640 2048 2460 2870 3280 3690
 set ccols 30 31  32   33   34   35   36   37   38   39

 set mpdset hires
 set map 3 1
 d count
 set strsiz 0.8 1
 draw title Himawari8 Band13 20150707 00:00UTC
 cbarn
 printim ir1-count-grads.png  white  x1600 y1200
 !eog ir1-count-grads.png

---

Install GMT5.x.x on Centos7

yum install netcdf\* GMT\* gshhg-gmt-\* -y

---

Install GMT4.x.x

Download the GMT4 source file from somewhere.
wget ftp://ftp.soest.hawaii.edu/gmt/gmt-4.5.18-src.tar.bz2
tar jxvf gmt-4.5.18-src.tar.bz2

cd gmt-4.5.18
./configure --prefix=/usr/local/GMT4; make ; make install install-data install-man install-doc
ln -s /usr/share/gshhg-gmt-nc4 /usr/local/GMT4/share/coast
ln -s /usr/local/GMT4 /usr/local/gmt
export PATH=$PATH:/usr/local/gmt/bin

---

Install GMT6 on Ubuntu 20.04

 sudo apt install gmt gmt-gshhg gmt-dcw

---

Install GMT4.x.x

Download the GMT4 source file from somewhere.
wget ftp://ftp.soest.hawaii.edu/gmt/gmt-4.5.18-src.tar.bz2
tar jxvf gmt-4.5.18-src.tar.bz2

cd gmt-4.5.18
sudo apt install gcc make libnetcdf-dev -y
./configure --prefix=/usr/local/GMT4; make ; make install install-data install-man install-doc
ln -s /usr/share/gmt-gshhg /usr/local/GMT4/share/coast
ln -s /usr/local/GMT4 /usr/local/gmt
export PATH=$PATH:/usr/local/gmt/bin

---

Install PyGMT on anaconda3 (Ubuntu 20.04)

!pip install pygmt

---

GMT6 source installation

\# load libraries and coastlines

!sudo apt install -y gmt-gshhg gmt-dcw build-essential cmake libcurl4-gnutls-dev libnetcdf-dev gdal-bin libgdal-dev libfftw3-dev libpcre3-dev liblapack-dev libblas-dev libglib2.0-dev ghostscript  graphicsmagick ffmpeg xdg-utils

GMT\_VERSION = "6.1.1"

# download the code

!wget "https://github.com/GenericMappingTools/gmt/releases/download/{GMT\_VERSION}/gmt-{GMT\_VERSION}-src.tar.gz"

!tar xzvf gmt-{GMT\_VERSION}-src.tar.gz

 
# build and install

%cd gmt-{GMT\_VERSION}

!cat ./cmake/ConfigUserTemplate.cmake > ./cmake/ConfigUser.cmake

!mkdir build

%cd build

!sudo cmake -DCMAKE\_INSTALL\_PREFIX=/usr/local -DCMAKE\_BUILD\_TYPE=RelWithDebInfo ..

# jオプションで同時に実行できるジョブの数（並行処理の数）を指定

!sudo make -j2

!sudo make -j2 install

 

# load the PyGMT

!pip install pygmt
