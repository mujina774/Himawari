# [ひまわり8/9号 フルディスク (FD) gridded data (緯度経度直交座標系精密幾何補正済データ) Version 02 (V20190123)公開について](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/index_jp.html)

## [Version 01 (20151105) リリースノートはこちら](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/index_jp_V20151105.html)

樋口篤志・竹中栄晶・豊嶋紘一：千葉大学環境リモートセンシング研究センター

本リリースノートの pdf 版はこちら([H08\_09\_gridded\_FD\_V02\_V20190123\_readme\_jp.pdf](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/H08_09_gridded_FD_V02_V20190123_readme_jp.pdf))

## 0\. ひまわり8号，9号観測期間

ひまわり8号，9号の観測期間は以下のとおりです．  
\- ひまわり8号：2015年7月7日 – 2022年12月13日0450 UTC, 左観測期間中一部ひまわり9号への切り替え有  
\- ひまわり9号：2018年2月13日 0250UTC – 2018年2月14日 0710UTC, 2022年12月13日 0450 UTC -.  
\# 観測期間については気象庁からの情報を再度確認してください．

## 1\. はじめに

「ひまわり8/9号」全球スキャンモード (FD) のgridded data を Version 02 (V20190123) にアップデートしました．概要は以下の通りです．

## 2\. Version up の概要

Version 02 (V20190123)では日射推定プロダクトAMATERASSの開発技術をフィードバックさせています．具体的には以下の通りです．

### 2.1. 精密幾何補正精度の向上

Version 01 (V20151105) と比較して，Version 02 では可視画像を利用した精密幾何補正の精度が高まっています． EXT等の高空間分解能データで恩恵を得ることができます． 一方，夜間の幾何補正精度は Version 01 と同じであり，SIR, TIR ではVersion 01 と Version 02 はほぼ同じ補正精度ですので，これらの波長域のユーザは本アップデートに伴う過去データの再取得は原則不要です．

### 2.2. 4 km データの公開

一部ユーザからのa) 物理量変換済みのデータが欲しい，b) センサー方位角・天頂角，太陽方位角・天頂角等のジオメトリ情報が欲しい，の要望に対応し， 4 km データ（詳細は3.3.5.を参照）を公開しました．

## 3\. データ格納仕様

### 3.1. 公開サーバおよびディレクトリー構成

Version 01 同様，[ftp://hmwr829gr.cr.chiba-u.ac.jp/](ftp://hmwr829gr.cr.chiba-u.ac.jp/) によるanonymous ftp で公開しています． anonymous \[ゲストユーザ\] でログイン後， _gridded/FD/V20190123/_ に移動すればデータ取得が可能です． [ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20190123/](ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20190123/) に直接アクセスすることも可能です． 以下の仕様でディレクトリが構成され，データが格納されています．  
_YYYYMM_ _YYYY_: 年 (4桁)，_MM_: 月（２桁）．2015年8月の場合，_201508_ となります． 各_YYYYMM_ ディレクトリには以下のサブディレクトリが作成されています．  
_EXT VIS SIR TIR 4KM_  
各ディレクトリに収められたデータの仕様は3.3 以降で説明します．

### 3.2. データ種類の仕様，およびひまわり8/9号バンドとの対応関係

公開する gridded data はこれまでの静止気象衛星データとの関連性から，気象庁のバンド名とは異なるルールで作製・公開しています．ご注意下さい． CEReS gridded data とひまわり8/9号バンドとの関係を表1に，EXT, VIS, SIR, TIR 共通のgridded data に関する仕様を表２にそれぞれ示します．  

| CEReS gridded | ひまわり8/9号バンド | Pixel x Line | 空間解像度 |
| --- | --- | --- | --- |
| EXT 01 | Band03 (0.64 μｍ) | 24000 x 24000 | 0.005 degree (500 m 相当) |
| VIS 01 | Band01 (0.47 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |
| VIS 02 | Band02 (0.51 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |
| VIS 03 | Band04 (0.86 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |
| SIR 01 | Band05 (1.6 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| SIR 02 | Band06 (2.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 01 | Band13 (10.4 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 02 | Band14 (11.2 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 03 | Band15 (12.4 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 04 | Band16 (13.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 05 | Band07 (3.9 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 06 | Band08 (6.2 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 07 | Band09 (6.9 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 08 | Band10 (7.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 09 | Band11 (8.8 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 10 | Band12 (9.6 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |

  

<table border="1"><tbody><tr><td>緯度経度範囲</td><td>東経 85度 – 西経155度 (85E – 155W (205E)), 北緯60度 – 南緯60度 (60N – 60S)</td></tr><tr><td>格納データ仕様</td><td>ヘッダー無し2 byte 符号無し整数 (unsigned short), big endian data order のバイナリデータ</td></tr><tr><td>データ書き出し順</td><td>西 -&gt; 東 (左 -&gt; 右)，北 -&gt; 南（上 -&gt; 下）に書き出し</td></tr><tr><td>格納データ</td><td>気象庁より配信されたひまわりスタンダード(HS) データ内のカウント値そのもの． <strong>幾何補正で値が入っていないところには例外値として65535 が入る点に注意が必要．</strong></td></tr></tbody></table>

### 3.3. ファイル名ルール

各データのファイル名ルールは以下の通りです．ファイル名がメタデータとなっています． **ファイル名で示される時刻は観測開始（スキャン開始）時刻となります．解析で用いる際には注意してください．** 基本ルールは以下の通りです．  
_YYYYMMDDHHMN.XXX.ZZ.fld.geoss.bz2_  
_YYYY_: 年 (4桁)，_MM_: 月 (2桁)，_DD_: 日 (2桁)， _HH_: 時 (2桁，**UTC**) ，_MN_: 分 (2桁, **UTC**)， _XXX_: 表１の CEReS gridded data 区分 (ext, vis, sir, tir が入る; 常に3文字．ディレクトリ名は大文字だが，ファイル表記では小文字となる点に注意が必要)， _ZZ_: 表１の CEReS gridded data バンド番号 (01, 02, 03, ...; 10 以下でも常に2文字．例 1 -> 01)， _fld_: ひまわり HS フルディスク (FD) データより作成， _geoss_: 特に意味はありません．CEReS静止気象衛星 gridded data 命名仕様上付けています． _bz2_: bzip2 仕様で圧縮されていることを示します． データを利用する際には bzip2 コマンドなど，bz2 ファイルを解凍する機能を持つコマンド，ソフトウェアで解凍する必要があります．

#### 3.3.1. EXT (0.005 degree; 500 m 相当)

EXT (0.005 degree, 500 m 相当，1バンド，Band 03) の仕様，ファイル名ルールは表3の通りです．

| CEReS gridded | ひまわり8/9号バンド | Pixel x Line | 空間解像度 |
| --- | --- | --- | --- |
| EXT 01 | Band03 (0.64 μｍ) | 24000 x 24000 | 0.005 degree (500 m 相当) |

<table border="1"><tbody><tr><td>ファイル名：<em>YYYYMMDDHHMN.ext.01.fld.geoss.bz2</em> で以下の情報を意味します．<br><em>YYYY</em>: 年(4桁), <em>MM</em>: 月(2桁), <em>DD</em>: 日(2桁), <em>HH</em>: 時（2桁，<strong>UTC</strong>）, <em>MN</em>: 分（2桁，<strong>UTC</strong>）， <em>ext</em>: CEReS grided data のバンド区分 (EXT)，<em>01</em>: CEReS gridded data のバンド番号(EXT は1バンドのみなので，01のみ)， <em>geoss</em>: CEReS gridded data 命名仕様上付記，<em>bz2</em>: bzip2 で圧縮されていることを示す．</td></tr><tr><td>注：EXT のみ精密幾何補正による位置修正結果に関する log ファイルである <em>YYYYMMDDHHMN.ext.(coff または loff).fld.txt.bz2</em> が存在します． 通常は参照する必要はありません．</td></tr></tbody></table>

#### 3.3.2. VIS (0.01 degree; 1 km 相当)

VIS (0.01 degree 1 km 相当，3バンド) の仕様，ファイル名ルールは表4の通りです．

| CEReS gridded | ひまわり8/9号バンド | Pixel x Line | 空間解像度 |
| --- | --- | --- | --- |
| VIS 01 | Band01 (0.47 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |
| VIS 02 | Band02 (0.51 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |
| VIS 03 | Band04 (0.86 μｍ) | 12000 x 12000 | 0.01 degree (1 km 相当) |

<table border="1"><tbody><tr><td>ファイル名：<em>YYYYMMDDHHMN.vis.ZZ.fld.geoss.bz2</em> で以下の情報を意味します．<br><em>YYYY</em>: 年(4桁), <em>MM</em>: 月(2桁), <em>DD</em>: 日(2桁), <em>HH</em>: 時（2桁，<strong>UTC</strong>）, <em>MN</em>: 分（2桁，<strong>UTC</strong>）， <em>vis</em>: CEReS grided data のバンド区分 (VIS)，<em>ZZ</em>: CEReS gridded data のバンド番号(VIS は3バンドなので， 01, 02, 03 が入る)， <em>geoss</em>: CEReS gridded data 命名仕様上付記，<em>bz2</em>: bzip2 で圧縮されていることを示す．</td></tr></tbody></table>

#### 3.3.3. SIR (0.02 degree; 2 km 相当)

SIR (0.02 degree 2 km 相当，2バンド)の仕様，ファイル名ルールは表5の通りです．

| CEReS gridded | ひまわり8/9号バンド | Pixel x Line | 空間解像度 |
| --- | --- | --- | --- |
| SIR 01 | Band05 (1.6 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| SIR 02 | Band06 (2.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |

<table border="1"><tbody><tr><td>ファイル名：<em>YYYYMMDDHHMN.sir.ZZ.fld.geoss.bz2</em> で以下の情報を意味します．<br><em>YYYY</em>: 年(4桁), <em>MM</em>: 月(2桁), <em>DD</em>: 日(2桁), <em>HH</em>: 時（2桁，<strong>UTC</strong>）, <em>MN</em>: 分（2桁，<strong>UTC</strong>）， <em>sir</em>: CEReS grided data のバンド区分 (SIR)，<em>ZZ</em>: CEReS gridded data のバンド番号 (SIR は2バンドなので，01, 02 が入る)， <em>geoss</em>: CEReS gridded data 命名仕様上付記，<em>bz2</em>: bzip2 で圧縮されていることを示す．</td></tr></tbody></table>

#### 3.3.4. TIR (0.02 degree; 2 km 相当)

TIR (0.02 degree 2 km 相当，10バンド)の仕様，ファイル名ルールは表6の通りです．

| CEReS gridded | ひまわり8/9号バンド | Pixel x Line | 空間解像度 |
| --- | --- | --- | --- |
| TIR 01 | Band13 (10.4 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 02 | Band14 (11.2 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 03 | Band15 (12.4 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 04 | Band16 (13.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 05 | Band07 (3.9 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 06 | Band08 (6.2 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 07 | Band09 (6.9 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 08 | Band10 (7.3 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 09 | Band11 (8.8 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |
| TIR 10 | Band12 (9.6 μｍ) | 6000 x 6000 | 0.02 degree (2 km 相当) |

<table border="1"><tbody><tr><td>ファイル名：<em>YYYYMMDDHHMN.tir.ZZ.fld.geoss.bz2</em> で以下の情報を意味します．<br><em>YYYY</em>: 年(4桁), <em>MM</em>: 月(2桁), <em>DD</em>: 日(2桁), <em>HH</em>: 時（2桁，<strong>UTC</strong>）, <em>MN</em>: 分（2桁，<strong>UTC</strong>）， <em>tir</em>: CEReS grided data のバンド区分 (TIR)，<em>ZZ</em>: CEReS gridded data のバンド番号 (TIR は10バンドなので，01, 02, ... 10 が入る)， <em>geoss</em>: CEReS gridded data 命名仕様上付記，<em>bz2</em>: bzip2 で圧縮されていることを示す．</td></tr></tbody></table>

#### 3.3.5. 4KM (0.04 degree; 4 km 相当) \[New!\]

Version 02 から提供される 4KM プロダクトは，ファイル数が多いことから日毎のサブディレクトリへ分かれます (_ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/V20190123/ YYYYMM/4KM/YYYYMMDD/_)． 提供されるデータセットおよびファイル名ルールは表7の通りです．

<table border="1"><tbody><tr><td>Pixel x Line, 解像度</td><td>3000 x 3000, 0.04 degree (4 km 相当)</td></tr><tr><td>緯度経度範囲</td><td>東経 85度 – 西経155度 (85E – 205E (155W)), 北緯60度 – 南緯60度 (60N – 60S) (他のデータセットと同じ)</td></tr><tr><td>格納データ仕様</td><td><strong>4 byte 浮動小数点(float), big endian data order バイナリデータ</strong></td></tr><tr><td>データ書き出し順</td><td>西 -&gt; 東 (左 -&gt; 右)，北 -&gt; 南（上 -&gt; 下）に書き出し</td></tr><tr><td>格納データ</td><td>物理量に換算済み</td></tr></tbody></table>

  

| ファイル名例 | 説明 |
| --- | --- |
| _YYYYMMDDHHMN.xxx.ZZ.rad.fld.4km.bin.bz2_ (xxx: ext, vis, sir, tir; ZZ: CEReS gridded data バンド番号) | ext, vis, sir, tir 放射輝度 (単位 W m<sup>-2</sup> sr<sup>-1</sup> μm<sup>-1</sup>) |
| _YYYYMMDDHHMN.xxx.ZZ.rfc.fld.4km.bin.bz2_ (xxx: ext, vis, sir; ZZ: CEReS gridded data バンド番号) | ext, vis, sir 分光反射率 (無次元) |
| _YYYYMMDDHHMN.xxx.ZZ.rfy.fld.4km.bin.bz2_ (xxx: ext, vis, sir; ZZ: CEReS gridded data バンド番号) | ext, vis, sir 分光反射率 (%) |
| _YYYYMMDDHHMN.tir.ZZ.tbb.fld.4km.bin.bz2_ (ZZ: CEReS gridded data バンド番号) | tir (のみ)輝度温度 (K) |

  

| ファイル名例 | 説明 |
| --- | --- |
| _YYYYMMDDHHMN.sun.azm.fld.4km.bin.bz2_ | 太陽方位角 (単位：度．真南が0，時計回り) |
| _YYYYMMDDHHMN.sun.zth.fld.4km.bin.bz2_ | 太陽天頂角 (単位：度) |
| _YYYYMMDDHHMN.sat.azm.fld.4km.bin.bz2_ | センサー方位角(単位：度．真南が0，時計回り) |
| _YYYYMMDDHHMN.sat.zth.fld.4km.bin.bz2_ | センサー天頂角（単位：度） |
| _YYYYMMDDHHMN.grd.time.mjd.hms.fld.4km.bin.bz2_ | 観測時刻情報<sup>*1</sup>（0〜1 で正規化．12:00 UTC で0.5） |
| _YYYYMMDDHHMN.lat.fld.4km.bin.bz2_ | 緯度情報（度．度以下の単位は小数点 \[分，秒ではない\]） |
| _YYYYMMDDHHMN.lng.fld.4km.bin.bz2_ | 経度情報（度．度以下の単位は小数点 \[分，秒ではない\]） |
| _YYYYMMDDHHMN.cap.flg.fld.bin.bz2_<sup>*2</sup> | 雲フラグ（昼間，海洋のみで，1以上が雲域と判別） |

\*1: スキャン時間の計算は厳格には行っていません． 各観測地点での厳格なスキャン時間を得たい場合はHS データからの取得が望ましいです．  
\*2: このファイルのみ2 byte 符号無し整数 (unsigned short), big endian byte order のバイナリデータ  

### 3.4. カウント値から物理量への変換

Version 02 より新規に提供された 4KM プロダクトを除くデータセットは，カウント値から物理量への変換処理（参照テーブルを基に輝度温度，または分光反射率への換算）が必要となります．

#### 3.4.1. カウント値から物理量（輝度温度，分光反射率）への変換 \[New!\]

サンプルプログラム群（Fortran90, C言語，python コードおよび変換テーブル群）として， [count2tbb\_v103.tgz](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/count2tbb_v103.tgz)をご参照ください． 同じファイルは [ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/support/](ftp://hmwr829gr.cr.chiba-u.ac.jp/gridded/FD/support/) にも置いてあります．  
[count2tbb\_v103.tgz](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/count2tbb_v103.tgz) ではひまわり9号の変換係数を追加しました． v103以前のバージョンを利用されている方は，ひまわり9号データを扱う際には v103をご利用ください．  
\[注意\] EXT (24000 x 24000) データは 4byte 浮動小数点 (float) への直接の変換ができません． 1ファイル 2GB の壁に当たるため， 64bit OS (Linux x86\_64, MacOS, Windows 64 bit 版)でもファイルを擬似的に2分割 （北半球，南半球）した後で変換処理を行い，分割された物理量データを結合しています（サンプルプログラム中のシェルスクリプトを参照下さい）． 加えて，32-bit OS では2 GBを超えるファイルは作製できません． 32-bit OS で EXTデータを扱う際には，北半球・南半球にデータを分けそれぞれで解析を行う，等の工夫が必要です．  
  
データの読み方について，以下の記載も参考になるかと思います（英語）．Version の違いは適宜読み替えてください． [http://quicklooks.cr.chiba-u.ac.jp/~himawari\_movie/rd\_gridded.html](http://quicklooks.cr.chiba-u.ac.jp/~himawari_movie/rd_gridded.html)  
海外のユーザによるPythonによるサンプルプログラムも存在します．公式にはサポートしませんが，参考までにお知らせします． [https://github.com/zxdawn/Himawari-8-gridded](https://github.com/zxdawn/Himawari-8-gridded)  

#### 3.4.2. カウント値から反射率等への変換（EXT, VIS, SIR）経年劣化について

光学センサは長期観測に伴い感度劣化（経年劣化）が起こります． そのため，年々変動，長期トレンド解析を行う際には感度補正（校正情報補正）が必要となります． ひまわり8号AHIに関し，ハワイ大学マノア校三浦知昭教授よりBand 01 - 06 (CEReS gridded dataset における EXT01, VIS01, 02, 03, SIR01, 02) に対する， 2015年（打ち上げ年）から2019年までの経年劣化補正済みの変換テーブルが提供されました． 解析の目的に応じ，ご利用ください． [Updated\_LUTs\_20200308\_zip.zip](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/Updated_LUTs_20200308_zip.zip) (zipでの圧縮．展開すると，説明文と校正テーブルのエクセルファイル，および各年のLUTが得られます)．  
  
参考情報：ひまわり8号AHI の感度補正のための構成情報更新について （ [https://www.data.jma.go.jp/mscweb/ja/oper/pdf/Update\_of\_Calibration\_Information\_2020(jp).pdf](https://www.data.jma.go.jp/mscweb/ja/oper/pdf/Update_of_Calibration_Information_2020(jp).pdf)， 2020年7月6日参照）

#### 3.4.3. センサ校正 (GSICS)活動

気象庁はひまわり8/9号 AHI に対し，可視・近赤外，中間赤外波長バンドに限らず， GSICS (Global Space-based Inter-Calibration System) の一環で校正作業をしています． より精確な物理量換算を行いたい場合には GSICS校正情報が有効です． 詳しくは気象庁気象衛星センターが提供する “Himawari Calibration Portal（英文）” をご参照ください．  
  
Himawari Calibration Portal: [https://www.data.jma.go.jp/mscweb/en/oper/calibration/calibration\_portal.html](https://www.data.jma.go.jp/mscweb/en/oper/calibration/calibration_portal.html) (2020年9月1日参照)

## 4\. 本データの利用 (citation)について

論文中では以下の２編の論文の引用をお願いします．  
  
幾何補正アルゴリズム：Takenaka, H., T. Sakashita, A. Higuchi, T. Nakajima (2020): Development of geolocation correction for geostationary satellite observation by phase only correlation method using visible channel, _Remote Sensing_, **12** (15), 2472, [doi:10.3390/rs12152472](https://doi.org/10.3390/rs12152472).  
  
幾何補正精度検証：Yamamoto, Y., K. Ichii, A. Higuchi, H. Takenaka (2020): Geolocation accuracy assessment of Himawari-8/AHI imagery for application to terrestrial monitoring, _Remote Sensing_, **12** (9), 1372, [doi:10.3390/rs12091372](https://doi.org/10.3390/rs12091372).  
  
また，謝辞には以下の文言を加えていいただければ幸いです．  
_“ひまわり8/9号 グリッドデータは千葉大学環境リモートセンシング研究センターで提供されたものを利用した (Himawari 8/9 gridded data are distributed by the Center for Environmental Remote Sensing (CEReS), Chiba University, Japan.)”_  
  
本 gridded data の利用に関しては，オリジナルであるひまわり標準データ提供元の気象庁\*に準拠します． すなわち営利目的の利用は原則として禁じます． ただし，民間企業による利用であっても，営利目的の前段階の研究開発の場合はこれを許容します．  
  
\*研究者向けデータ公開： [http://www.data.jma.go.jp/mscweb/ja/info/resercher.html](http://www.data.jma.go.jp/mscweb/ja/info/resercher.html) (2020年9月1日参照)

### 4.1. リアルタイムデータの取り扱いについて

オリジナルデータ提供元の気象庁より，リアルタイムデータ (気象庁の定義ではリアルタイムデータは観測後24時間以内) を制限無しで公開することが禁じられています．リアルタイムデータへのアクセスは IP アドレスで制御しています． リアルタイムデータへのアクセスを希望される際には，request4himawaridata \_AT\_ ceres.cr.chiba-u.ac.jp にアクセスする IP アドレス（global IP）と利用目的（数行で結構です）を記載し送って下さい． なお，大学機関・研究所等の大口利用に関してはどなたかアクセスしうるIPアドレスの範囲を教えて頂けると大変助かります （非商用利用が分かれば良く，多数のIPアドレス列挙は効率が良くないため）． ユーザ登録によるアクセス制御に対応する予定は今後もありません．あらかじめご容赦下さい．

#### 謝辞

本処理プログラムのアップデート，リアルタイム・過去分処理計算機群資源，公開サーバストレージ資源，人件費のサポートについては， 4大学連携バーチャルラボラトリー，JST/CREST TEEDDA，千葉大学学長裁量の支援を受けました． また，富山大学濱田篤准教授には変換プログラムのバグの指摘，F90での回避プログラム例の提示，pyhtonコードの提供を， ハワイ大学マノア校三浦知昭教授にはひまわり8号バンド1-6の校正係数アップデートを適応したルックアップテーブルファイルの作成，および提供を， 千葉大 CEReS 市井研 Liu Zhiyan氏には，python コードの高速化をして頂きました．ここに記し，感謝の意を示します．

This html was written by: HIGUCHI, Atsushi, CEReS, Chiba University, Japan. Last update: 14 Dec 2022