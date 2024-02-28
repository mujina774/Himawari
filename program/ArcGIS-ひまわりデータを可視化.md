# [ArcGIS Pro で気象衛星ひまわりデータを可視化する](https://blog.esrij.com/2022/12/09/post-46880/)

2022/12/9 2023/12/11  
[イメージ](https://blog.esrij.com/category/%e3%82%a4%e3%83%a1%e3%83%bc%e3%82%b8/) [ArcGIS Pro](https://blog.esrij.com/products/arcgis-pro/)

先日、[気象庁が気象衛星の観測を「ひまわり8号」から「ひまわり9号」に切り替えることを発表](https://www.jma.go.jp/jma/press/2211/11a/20221111_sat_kirikae.html#:~:text=%E6%A6%82%E8%A6%81,%E8%A1%9B%E6%98%9F%E8%A6%B3%E6%B8%AC%E3%82%92%E5%88%87%E3%82%8A%E6%9B%BF%E3%81%88%E3%81%BE%E3%81%99%E3%80%82)しました。ひまわりのデータは報道等で目にする機会は多いものの、GIS で扱うことは稀ではないかと思います。今回、ひまわりの[**フルディスク観測**](https://www.data.jma.go.jp/mscweb/ja/info/observation.html) (衛星から見える地球全体) の画像データを ArcGIS Pro で可視化してみました。本記事ではその概要をご紹介します。


### 目次

- [1 前提](https://blog.esrij.com/2022/12/09/post-46880/#i)
- [2 ひまわり標準データ](https://blog.esrij.com/2022/12/09/post-46880/#i-2)
- [3 座標系の設定](https://blog.esrij.com/2022/12/09/post-46880/#i-3)
- [4 ラスター データとして取扱うために必要な情報](https://blog.esrij.com/2022/12/09/post-46880/#i-4)
    - [4.1 ヘッダー ファイル](https://blog.esrij.com/2022/12/09/post-46880/#i-5)
    - [4.2 データの構成](https://blog.esrij.com/2022/12/09/post-46880/#i-6)
- [5 ヘッダー ファイルの作成](https://blog.esrij.com/2022/12/09/post-46880/#i-7)
    - [5.1 セグメント単位のヘッダー ファイルの作成](https://blog.esrij.com/2022/12/09/post-46880/#i-8)
    - [5.2 全セグメントのヘッダー ファイル](https://blog.esrij.com/2022/12/09/post-46880/#i-9)

## 前提

使用したデータ

気象衛星センターが公開している[サンプルデータ](https://www.data.jma.go.jp/mscweb/ja/info/sample_data_hsd_h09_v13.html)を使用しました。

- ひまわり標準データ (Ver.13)  (ひまわり９号)  – バンド１
- ファイル名: 　HS\_H09\_20180205\_0250\_B01\_FLDK.zip

記事中で引用している手引書

本記事では、気象衛星センターが公開している[手引書](https://www.data.jma.go.jp/mscweb/ja/info/sample_data_hsd.html) (ひまわり標準データ 利用の手引き (第1.3版、2017年7月3日公開) 、2022年12月1日アクセス) を引用しています。記事中では、特に断りが無い限り「手引書」と記載し、必要に応じて引用箇所を併記します。

試行した環境

ArcGIS Pro 3.0

## ひまわり標準データ

ひまわり標準データは気象庁が作成し提供する衛星観測データの最も源泉に近いデータです。ラスター データとして扱うために最低限必要な情報を次に示します。

<table style="width: 810px;"><tbody><tr><td style="width: 197.094px;">データの種類</td><td style="width: 585.906px;">フルディスク、日本域、機動観測域、ランドマーク域に分類されます。 （手引書p.3）</td></tr><tr><td style="width: 197.094px;">データの構成</td><td style="width: 585.906px;">手引書によると、ひまわり標準データは”必要に応じてセグメント分割して提供されることがある”とされています。セグメントの分割数はファイル名またはヘッダーから判断できます。 (手引書p.6 – 4. ファイル命名規則)</td></tr><tr><td style="width: 197.094px;">画素数</td><td style="width: 585.906px;">各データのバンドごとに空間分解能が異なることから、画像データの画素数も異なります。 (手引書p.4 表3)</td></tr><tr><td style="width: 197.094px;">地図投影法と測地系</td><td style="width: 585.906px;">静止衛星から見える地球上に画像を投影する Normalized Geostationary Projection に準拠します。測地系は WGS84 に準拠します。</td></tr></tbody></table>

## 座標系の設定

ArcGIS に搭載されている [Geostationary Satellite](https://pro.arcgis.com/ja/pro-app/latest/help/mapping/properties/geostationary-satellite.htm) 図法を使用します。ArcGIS Pro のマップ プロパティの座標系メニューにて「新しい投影座標系」を選択し、必要なパラメーターを指定します。最低限必要なパラメーターは、①中心経度、②高さ、の 2 つです。気象庁の公開資料等を参考にして、図のように設定し、任意の名前で保存します。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection-300x152.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection-300x152.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection.png)

定義した座標系をマップに適用すると、下図のように緯度経度が 0, 140.7 の位置を原点 (マップ中央の赤い点) とする静止気象衛星座標系でマップが表示されます。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection_map-300x176.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection_map-300x176.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_projection_map.png)

※設定した座標系は、再利用できるよう、[お気に入りへの登録](https://pro.arcgis.com/ja/pro-app/latest/help/mapping/properties/specify-a-coordinate-system.htm#ESRI_SECTION1_094B3E77F00C468298C03E7319A55A74)もしくは[投影情報ファイル (prj) に保存](https://pro.arcgis.com/ja/pro-app/latest/help/mapping/properties/specify-a-coordinate-system.htm#ESRI_SECTION1_208CE566B39340DB97BE9361F316ADD4)しておくと便利です。

## ラスター データとして取扱うために必要な情報

ひまわり標準データは気象庁の独自形式のバイナリ データとして提供されるため、そのままでは ArcGIS がラスターとして認識できません。今回の試行では、[ヘッダー ファイル](https://desktop.arcgis.com/ja/arcmap/10.6/manage-data/raster-and-images/bil-bip-and-bsq-raster-files.htm#GUID-241FFE13-A74A-4B82-B0B0-8C22E367FCE0) (\*.hdr) という仕組みを利用します。

### ヘッダー ファイル

ヘッダー ファイルは画像データのパラメーター (縦横のピクセル数、バイト オーダー、マップ座標等) を記述したものです。規定のルールに沿って記述したヘッダーは、画像データと同じ名前 (.hdr) で同じ場所に保存することで、ArcGIS がラスターとして認識します。今回、ひまわり標準データの可視化にあたり、使用したヘッダーのキーワードは次のとおりです。

<table style="width: 680px;"><tbody><tr><td style="background-color: #c4caff; width: 104.891px;">キーワード</td><td style="background-color: #c4caff; width: 551.109px;">内容</td></tr><tr><td style="width: 104.891px;">ncols</td><td style="width: 551.109px;">画像の列数</td></tr><tr><td style="width: 104.891px;">nrows</td><td style="width: 551.109px;">画像の行数</td></tr><tr><td style="width: 104.891px;">nbands</td><td style="width: 551.109px;">バンド数</td></tr><tr><td style="width: 104.891px;">nbits</td><td style="width: 551.109px;">バンド当たりのピクセルのビット数</td></tr><tr><td style="width: 104.891px;">byteorder</td><td style="width: 551.109px;">バイト オーダー（I または M）</td></tr><tr><td style="width: 104.891px;">skipbytes</td><td style="width: 551.109px;">イメージ データの先頭に達するまでにスキップするイメージ ファイル内のデータのバイト数</td></tr><tr><td style="width: 104.891px;">ulxmap</td><td style="width: 551.109px;">画像データの左上隅ピクセルの中央の X 軸座標</td></tr><tr><td style="width: 104.891px;">ulymap</td><td style="width: 551.109px;">画像データの左上隅ピクセルの中央の Y 軸座標</td></tr><tr><td style="width: 104.891px;">xdim</td><td style="width: 551.109px;">X 軸方向のピクセルあたりの距離</td></tr><tr><td style="width: 104.891px;">ydim</td><td style="width: 551.109px;">Y 軸方向のピクセルあたりの距離</td></tr></tbody></table>

### データの構成

ひまわり標準データの命名規則は次のとおりです。各 DAT ファイル名の Skkll の箇所から、そのフルディスクデータの総セグメント数 (ll) と当該 DAT ファイルのセグメント番号 (kk) が判別できます。 (詳細は、[手引書](https://www.data.jma.go.jp/mscweb/ja/info/sample_data_hsd.html)p.6を参照)

**HS\_aaa\_yyyymmdd\_hhnn\_Bbb\_cccc\_Rjj\_Skkll.DAT**

各 DAT ファイルは、ヘッダー ブロックとデータ ブロック (画像を構成するピクセル データ) から構成されています。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_std_structure-300x128.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_std_structure-300x128.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_std_structure.png)

今回使用するサンプルデータ (ひまわり9号、フルディスク、バンド番号01) は、2段階で圧縮した状態で構成されていました。1 つ目の ZIP ファイルを解凍すると、セグメント分割された数の .bz2 ファイルが展開されます。さらに各 .bz2 ファイルを解凍すると、10 個の .DAT ファイルが展開されます。以上から、このサンプルデータは、フルディスクの 1 つの観測データが、10 個のセグメントに分割されていることが分かります。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_zip-300x54.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_zip-300x54.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_zip.png)

セグメント単位のデータと静止気象衛星座標系のマップとの対応関係を整理したものを数に示します。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_map-300x226.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_map-300x226.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_map.png)

これで対象データを扱う準備ができましたので、各 .DAT ファイルに対応する hdr ファイルを作成してみます。

## ヘッダー ファイルの作成

### セグメント単位のヘッダー ファイルの作成

解凍したファイルのうちセグメント番号01のデータ (HS\_H09\_20180205\_0250\_B01\_FLDK\_R10\_S0110.DAT) に対応するヘッダー ファイルを作成してみます。[手引書](https://www.data.jma.go.jp/mscweb/ja/info/sample_data_hsd.html)の「４. ファイル命名規則」及び「表6各ブロック内容の詳細」を参考に、ヘッダー ファイルに記述する値を抽出しました。

ここで、画像の左上隅の座標である ulxmap と ulymap の与え方が重要です。この値はひまわり標準データには格納されていないため、次の考え方で算出しました。 (※ xdim / 2.0 と ydim / 2.0 は、ArcGIS でのラスターの座標の位置がピクセル中心であることから、反ピクセル分のオフセットとして減じたものです)

- ULXMAP 　= -1\* ((ncols \* xdim) / 2.0 – (xdim / 2.0))
- ULYMAP　 = (nrows \* ydim) / 2.0 – (ydim / 2.0)

ヘッダー ファイルに記述する値を下表にまとめます。ヘッダー ファイルは、セグメント番号01の DAT ファイルと同じ名前 (拡張子は hdr) とし、DAT ファイルと同じ階層に保存します。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_header-1-300x71.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_header-1-300x71.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_header-1.png)

※今回は手動での試行のため、バイナリ データの読込みには無料のバイナリ エディタを使用しました。

ArcGIS Pro のカタログ ウィンドウで確認すると、DAT ファイルがラスター データセットとして認識されたことが分かります。マップに DAT ファイルを追加した結果は図のとおりです。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_mapping-300x163.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_mapping-300x163.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_seg01_mapping.png)

### 全セグメントのヘッダー ファイル

セグメント番号02～10の DAT ファイルについては、原則、前述の要領でヘッダー ファイルを作成すれば良いわけですが、ulymap (左上隅の緯度方向のマップ座標) は緯度方向に座標をスライドさせる必要がある点に注意が必要です。

具体的には、各データのセグメント番号に応じて、緯度方向の距離のオフセットを与えることとし、次の考え方で各セグメントの ulymap を求めました。

- ulymap = (nrows \* ydim) / 2.0 – (ydim / 2.0) + ((セグメント番号 – 1) \* セグメント単体の行数 \* ydim)

最後に、各セグメントのヘッダー ファイルを上述の要領で作成することで、全セグメントがラスター データセットとして認識されました。各セグメントの画像が適切な位置に配置されたことが分かると思います。以降は、ラスターのモザイク ([モザイク](https://pro.arcgis.com/ja/pro-app/latest/tool-reference/data-management/mosaic.htm) ツール、[ラスターのモザイク関数)](https://pro.arcgis.com/ja/pro-app/latest/help/analysis/raster-functions/mosaic-rasters.htm) を行えば、1 つのラスター データセットとして扱えます。

[![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_all_mapping-300x163.png)

![](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_all_mapping-300x163.png)

](https://blog.esrij.com/arcgisblog/wp-content/uploads/2022/12/himawari_fulldisk_all_mapping.png)

本記事で紹介したフローは、当社で試行した結果の概要となります。細部の手順にご興味がありましたら当社までお問い合わせください。