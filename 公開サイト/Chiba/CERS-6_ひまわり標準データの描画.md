## 6 ひまわり標準データの描画
フルディスクのひまわり標準データはグリッドデータに比べて取り扱いが難しいが、グリッドデータにはないヘッダー情報やディスク周辺部の観測データを含む。

### 6.1 ひまわり標準データについて
ひまわり標準データはひまわり独自のバイナリデータ形式になっており、可視赤外放射計（AHI）の観測で得られたDN値と様々なヘッダー情報が含まれている。フルディスクのひまわり標準データに収められているAHI観測データの列数および有効ビット数を表6.1にまとめる。ここで使うひまわり標準データは図6.1のように10個のセグメントに分割されており、 1セグメント（1ファイル）当たりの行数は列数の1/10である。
 - ひまわり標準データにはAHIの各画素で得られたDN値が有効ビット数に関わらず2バイトの符号なし整数として記録されている。

#### 表6.1. フルディスクひまわり標準データ
|ひまわり8号バンド名 |中心波長（μm） |空間分解能（km） |列数（fulldisk） |有効ビット数|
| --- | --- | --- | --- | --- |
|01 |0.47 |1 |11000| 11|
|02 |0.51 |1 |11000 |11|
|03 |0.64 |0.5 |22000 |11|
|04 |0.86 |1 |11000 |11|
|05 |1.6 |2 |5500 |11|
|06 |2.3 |2 |5500 |11|
|07 |3.9 |2 |5500 |14|
|08 |6.2 |2 |5500 |11|
|09 |6.9 |2 |5500 |11|
|10 |7.3 |2 |5500 |12|
|11 |8.6 |2 |5500 |12|
|12 |9.6 |2 |5500 |12|
|13 |10.4 |2 |5500 |12|
|14 |11.2 |2 |5500 |12|
|15 |12.4 |2 |5500 |12|
|16 |13.3 |2 |5500 |12|

図6.1 フルディスクひまわり標準データの観測領域

### 6.2 準備
☞ まず、いつもの準備を行う。
入力コード：
```
%matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
```
In [1]:
☞ 次に、ヘッダー情報のサイズを計算するため（ファイルサイズを取得するため）にosモジュールを使う準備をする。 また、今回は幾何補正で2次元補間関数を使うため、その準備をする。
入力コード：
```
import os
from scipy.interpolate import RectBivariateSpline
```
In [2]:
### 6.3 ひまわり標準データの読み込み
ここでは例として近赤外バンド（バンド4）のひまわり標準データ（"HS_H08_20160512_0400_B04_FLDSK_R01_SD210.DAT"）を使う。このデータは以下のようなコードで読み込むことができる。
 - ここではAHI観測データの列数、行数とファイルサイズからヘッダーサイズを計算しているが、これらの値はヘッダー情報を解析して得ることもできる。
 - 3行目では整数の商を得るために切り捨て除算演算子//を用いている。（Python3では整数同士に除算演算子/を使うと浮動小数点数の商が得られる。）
 - 7行目ではfromstringの引数にdtypeを与えて変数の型を指定している。'u'は符号なし整数を意味し、後ろの2はバイト数を意味している。 'u'以外にも'i'、'f'等のフォーマット文字があり、それぞれ符号付き整数，浮動小数点数を意味する。デフォルトのバイトオーダーは計算機に依存するが、フォーマット文字の前に'<'、'>'を置くとそれぞれリトルエンディアン、ビッグエンディアンを指定できる。型の指定方法はいくつかあるが、ここではコードが一番短いものを使用している。（例えば'u2'の代わりにnp.dtype('u2')やnp.uint16が使える。）fromstringのデフォルトは'f8'である。

In [3]:
入力コード：
```
fnam = 'HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT'
NCOL = 11000
NLIN = NCOL//10
hsiz = os.path.getsize(fnam)- NCOL*NLIN*2
with open(fnam,'rb') as fp:
   head = fp.read(hsiz)
   data = np.fromstring(fp.read(),dtype='u2').reshape(NLIN,NCOL)
```

☞ これでデータが読み込まれたので、例えば以下のようなコードで描画できる。
入力コード：
```
plt.imshow(data,vmax=2**11);
```
```
%matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
import os
from scipy.interpolate import RectBivariateSpline
fnam = 'HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT'
NCOL = 11000
NLIN = NCOL//10
hsiz = os.path.getsize(fnam)- NCOL*NLIN*2
with open(fnam,'rb') as fp:
head = fp.read(hsiz)
data = np.fromstring(fp.read(),dtype='u2').reshape(NLIN,NCOL)
```

### 6.4 ひまわり標準データのヘッダー情報の解析
前節で読み込んだデータはDN値であり、物理量を得るには校正が必要である。 また、AHI独自の空間座標系になっているために幾何補正も必要となる。そのためにヘッダー情報の解析を行う。ここではひまわり標準データのユーザーガイド (http://www.data.jma.go.jp/mscweb/en/himawari89/space_segment/hsd_sample/HS_D_users_guide_en_v12.pdf)に従って必要最低限の情報のみ取り出すことにする。
入力コード：
```
imax, = np.fromstring(head[3:5],dtype='u2')
j,h = 0,[]
for i in range(imax):
   n, = np.fromstring(head[j+1:j+3],dtype='u2')
   h.append(head[j:j+n])
   j += n
sub_lon, = np.fromstring(h[2][3:11])
cfac,lfac = np.fromstring(h[2][11:19],dtype='u4')
coff,loff = np.fromstring(h[2][19:27],dtype='f4')
p1,p2,p3,p4,p5,p6,p7 = np.fromstring(h[2][27:83])
band, = np.fromstring(h[4][3:5],dtype='u2')
wlen, = np.fromstring(h[4][5:13])
verr,vout = np.fromstring(h[4][15:19],dtype='u2')
gain,cnst = np.fromstring(h[4][19:35])
lnum, = np.fromstring(h[6][5:7],dtype='u2')
```
 - ひまわり標準データのヘッダーは11（= imax）個のブロックに分かれており、各ブロックの先頭にブロック番号とブロックサイズが格納されている。
 - 2～6行目でヘッダーをブロック毎に分け、それ以後はブロック毎に必要なパラメータを取り出している。ここではシーケンスのアンパックという手法が使われている。シーケンスとはリストやタプル、ndarrayといったPythonの配列型のことである。例えば8行目の左辺は要素数2のタプル、右辺は要素数2のndarrayであり、右辺のndarrayがアンパック（開梱）されて左辺のそれぞれの要素に代入されている。（Pythonのタプルは丸括弧で囲んで表すが、ここでは丸括弧が省略されている。）要素数1のタプルは値の後ろにコンマを付けるという規則があり、1行目の左辺にはコンマが付いている。（コンマを付けるとimaxは整数値になるが、そうしないとndarrayになる。）
In [5]:
```
plt.imshow(data,vmax=2**11);
imax, = np.fromstring(head[3:5],dtype='u2')
j,h = 0,[]
for i in range(imax):
n, = np.fromstring(head[j+1:j+3],dtype='u2')
h.append(head[j:j+n])
j += n
sub_lon, = np.fromstring(h[2][3:11])
cfac,lfac = np.fromstring(h[2][11:19],dtype='u4')
coff,loff = np.fromstring(h[2][19:27],dtype='f4')
p1,p2,p3,p4,p5,p6,p7 = np.fromstring(h[2][27:83])
band, = np.fromstring(h[4][3:5],dtype='u2')
wlen, = np.fromstring(h[4][5:13])
verr,vout = np.fromstring(h[4][15:19],dtype='u2')
gain,cnst = np.fromstring(h[4][19:35])
lnum, = np.fromstring(h[6][5:7],dtype='u2')
```
## 6.5 ひまわり標準データの校正
前節で得られたヘッダー情報を使って校正を行う。まず、DN値（data）を放射輝度（lrad）に変換する。 次に放射輝度を反射率（バンド1～6）または輝度温度（バンド7～16）に変換する。変換に用いる数式はひまわり標準データのユーザーガイド (http://www.data.jma.go.jp/mscweb/en/himawari89/space_segment/hsd_sample/HS_D_users_guide_en_v12.pdf)で説明されている。
入力コード：
```
LMIN = 1.0e-60
lrad = gain*data+cnst
lrad[lrad < LMIN] = LMIN
if band > 6:
   wlen *= 1.0e-6
   lrad *= 1.0e6
   c0,c1,c2,c_0,c_1,c_2,c_c,c_h,c_k = np.fromstring(h[4][35:107])
   t_e = c_h*c_c/(c_k*wlen*np.log(2*c_h*c_c**2/(wlen**5*lrad)+1))
   val = c0+c1*t_e+c2*t_e**2
else:
   coef, = np.fromstring(h[4][35:43])
   val = coef*lrad
```
◎ 3行目ではlrad < LMINが成立するlradの要素の値をLMINに変更している。cnd = (lrad < LMIN)とするとcndはlradがLMINより小さい要素はTrue、そうでない要素はFalseのndarrayになる。（複数条件のandやorを取る場合は各条件を括弧で囲んでおくとよい。）このようにndarrayの要素を選択するためにはTrueまたはFalseのフラグが入った配列が使えるほか、欲しい要素のインデックスを入れた配列を使うこともできる。（例えば、indy,indx = np.where(lrad <LMIN)とするとlrad < LMINが成立するインデックスを取得でき、lrad[indy,indx]で要素を選択することができる。）
 - 4～12行目では追加のヘッダー情報を取得して校正された放射輝度（lrad）を反射率（バンド1～6）または輝度温度（バンド7～16）に変換している。
In [6]:
```
LMIN = 1.0e-60
lrad = gain*data+cnst
lrad[lrad < LMIN] = LMIN
if band > 6:
wlen *= 1.0e-6
lrad *= 1.0e6
c0,c1,c2,c_0,c_1,c_2,c_c,c_h,c_k = np.fromstring(h[4][35:107])
t_e = c_h*c_c/(c_k*wlen*np.log(2*c_h*c_c**2/(wlen**5*lrad)+1))
val = c0+c1*t_e+c2*t_e**2
else:
coef, = np.fromstring(h[4][35:43])
val = coef*lrad
```

### 6.6 ひまわり標準データの幾何補正
標準データの幾何補正方法としては、AHI画像座標（列番号,行番号）を緯度経度に変換する方法と、適当な等緯度経度座標をAHI画像座標に変換し、その格子点におけるAHI観測値を2次元補間によって求める方法が考えられる。ここでは結果が等緯度経度座標系になる後者の方法を採用する。変換に用いる数式はLRIT/HRIT Global Specification5) (http://www.cgms-info.org/documents/cgms-lrithrit-global-specification-(v2-8-of-30-oct-2013).pdf)で説明されている。
入力コード：
```
lon = np.arange(138.0,141.001,0.01)
lat = np.arange(37.5,34.499,-0.01)
col = np.arange(NCOL)+1
lin = np.arange(NLIN)+lnum
rad_lat = np.radians(lat)
c_lat = np.arctan(p5*np.tan(rad_lat))
c_lon = np.radians(lon-sub_lon)
cos_lat = np.cos(c_lat).reshape(-1,1)
sin_lat = np.sin(c_lat).reshape(-1,1)
cos_lon = np.cos(c_lon).reshape(1,-1)
sin_lon = np.sin(c_lon).reshape(1,-1)
rl = p3/np.sqrt(1.0-p4*cos_lat**2)
r1 = p1-rl*cos_lat*cos_lon
r2 = -rl*cos_lat*sin_lon
r3 = rl*sin_lat
rn = np.sqrt(r1*r1+r2*r2+r3*r3)
x = np.degrees(np.arctan(-r2/r1))
y = np.degrees(np.arcsin(-r3/rn))
col_out = coff+x/65536*cfac
lin_out = loff+y/65536*lfac
val_out = RectBivariateSpline(lin,col,val).ev(lin_out,col_out)
```
 - ここではndarrayのブロードキャスティングという手法が使われている。これを使うと、例えば要素数が(1,nx)と(ny,1)のndarrayの2項演算をするとあたかもそれぞれが要素数(ny,nx)のndarrayであるかのように扱われる（足りない行または列には同じ値が使われる）。9～12行目ではブロードキャスティングが行われるようにreshape（全要素数を保ったままndarrayの次元数や各次元の要素数を変更すること）を行っている。ここで、1つの次元の要素数に−1を指定すると、その次元の要素数は全要素数が保たれるように自動計算される。
 - この例ではバンド4観測データの空間分解能が1 kmであることから東経138°～141°、北緯34.5°～37.5°の範囲を0.01度間隔で区切り、緯度経度座標をAHI画像座標に変換して格子点上のAHI観測値をRectBivariateSplineという2次元補間メソッドを用いて求めている。
In [7]:
```
lon = np.arange(138.0, 141.001, 0.01)
lat = np.arange(37.5, 34.499, -0.01)
col = np.arange(NCOL) + 1
lin = np.arange(NLIN) + lnum
rad_lat = np.radians(lat)
c_lat = np.arctan(p5*np.tan(rad_lat))
c_lon = np.radians(lon-sub_lon)
cos_lat = np.cos(c_lat).reshape(-1,1)
sin_lat = np.sin(c_lat).reshape(-1,1)
cos_lon = np.cos(c_lon).reshape(1,-1)
sin_lon = np.sin(c_lon).reshape(1,-1)
rl = p3/np.sqrt(1.0-p4*cos_lat**2)
r1 = p1-rl*cos_lat*cos_lon
r2 = -rl*cos_lat*sin_lon
r3 = rl*sin_lat
rn = np.sqrt(r1*r1+r2*r2+r3*r3)
x = np.degrees(np.arctan(-r2/r1))
y = np.degrees(np.arcsin(-r3/rn))
col_out = coff+x/65536*cfac
lin_out = loff+y/65536*lfac
val_out = RectBivariateSpline(lin,col,val).ev(lin_out,col_out)
```

### 6.7 描画
☞ Matplotlibのimshowを使って2次元データを描画する。

入力コード：

```
plt.imshow(val_out,extent=(lon[0],lon[-1],lat[-1],lat[0]),interpolation='none')
plt.colorbar();
```

In [8]: 
```
plt.imshow(val_out,extent=(lon[0],lon[-1],lat[-1],lat[0]),interpolation='none')
plt.colorbar();
```