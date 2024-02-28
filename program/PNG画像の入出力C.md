# [PNG画像の入出力](https://www.mm2d.net/main/prog/c/image_io-15.html)

作成：2015/10/16

<iframe id="google\_ads\_frame0"> (adsbygoogle = window.adsbygoogle || \[\]).push({});

前回まで画像ファイルの入出力について、ファイルフォーマットの詳細説明から、 入出力を全て自前で実装する場合の説明を行ってきた。 今回は画像フォーマットについて理解した上で、読み書きの処理を一から全て実装するのではなく、 オープンソースのライブラリを利用する方法を説明する。

今回説明するのはPNG画像の入出力だ。 PNG 形式の登場は1996年であり、 コンピュータ黎明期から存在しているフォーマットというにはやや歴史は浅いが、 現在では、おそらく画像を扱うソフトウェアで、 扱えないものを探すほうが難しいぐらい一般的に普及している画像形式だろう。

**PNG** は **P**ortalbe **N**etwork **G**raphics の頭字語（アクロニム）とされる。 また、かつて可逆圧縮の画像フォーマットとして インターネットを中心に普及した GIF 形式の特許問題を発端として開発された経緯から、 **P**NG is **N**ot **G**IFという再帰的頭字語としての意味も込められている。

画像形式の特徴としては、インデックスカラー、グレースケール、 RGB フルカラー、 透過についてはアルファチャンネルと、特定の色を透過として指定するクロマキー形式での透過、 両方に対応し、 RGB 及びアルファチャンネルは 8bit ないしは 16bit で表現される。 また、画像データは Deflate という圧縮アルゴリズムを利用し、可逆圧縮される。 圧縮を行うためデータサイズを小さくすることができ、可逆圧縮であるため劣化することはない。 データ構造はチャンクと呼ばれるブロックの組み合わせで実現されており、 様々なメタデータを埋め込むことができ、拡張性と前方互換性を両立させている。

様々なプラットホームで使用可能であり、 無劣化のラスター画像を扱うフォーマットとしてはデファクトスタンダードといってよいだろう。 ただし、その仕様はこれまで説明したPNMやBMPに比べて大きく、 全て実装するには数倍以上のコード量が必要になるだろう。

## libpngの利用

今回は、PNG画像の入出力を行うライブラリとして [libpng](http://www.libpng.org/pub/png/libpng.html) を利用する。 libpng はオープンソースで開発されているライブラリであり、 おそらくPNG画像を扱うソフトウェアの多くはこのライブラリを使っているだろう。 このライブラリのライセンスは、 [zlib/libpng License](http://opensource.org/licenses/Zlib) という、オープンソースライセンスの中でも比較的ゆるいライセンスのもと公開されており、 プロプライエタリなソフトウェアでもよく利用されるライブラリである。

libpng は移植性も高く、様々なプラットホーム上で利用する事ができる。 何より広く利用されているということは、動作実績が豊富であり、よくデバッグされているということである。 また、十分に最適化されており、高速化なども図られているし、 単に読み書きするだけでなく、何らかの独自の処理を追加したい場合にも対応できるよう拡張性も高く設計されている。 PNG画像を扱うにあたっては、相当特別な理由がない限り、このライブラリを使って実装するのが通常だろう。

libpng自体のライセンスは[こちら](http://www.libpng.org/pub/png/src/libpng-LICENSE.txt)を参照。 私自身法律の専門家ではないため、当サイトではライセンスについては厳密には解説しない。 上記ライセンスを参照の上、自己の責任の上で利用してほしい。

外部のライブラリを利用するためそのライブラリは何らかの方法で入手する必要がある。 Ubuntuにてlibpngの開発環境をインストールするには以下のようにする。

$ sudo apt-get install libpng12-dev

libpngは圧縮・伸長アルゴリズム部分に[zlib](http://zlib.net/)を利用している。 パッケージ管理システムがあれば依存関係も自動的に解決してくれるだろうが、 個別にlibpngのパッケージを組み込んだりする場合はzlibも必要になるので注意してほしい。

実行バイナリを作成する際は当然 libpng とのリンクが必要になる。 例えば、gccでコンパイルの際は、以下のように<kbd>-lpng</kbd>オプションが必要となる。

$ gcc hoge.c -o hoge -lpng

libpng を使ったコーディングを行う上での注意点としては、 本稿執筆時点では libpng の最新バージョンは 1.6 系なのだが、 1.2 系とそれ以降で構造体メンバへのアクセス方法が変わっている。 1.6 系では構造体メンバはプライベートメンバに変更され直接アクセスできない。 読み書きを行うにはアクセス API を経由する必要がある。 アクセス API 自体は 1.2 系にも存在するため、 1.6 系向けのソースコードは 1.2 系の環境でもビルド可能だ。 逆に 1.2 系向けに開発されたソースコードはそのままでは 1.6 系の環境ではビルドできない場合がある。

そのような関係もあり、libpngのサイトでは 1.6 系だけでなく 1.2 系についてもサポートが継続している。 本稿執筆時点ではまだ 1.2 系の方が広く使われているようで、 Ubuntu の環境では apt の標準リポジトリからは 1.2 系しかインストール出来ない。 Cygwin の環境ではバージョンの選択ができるようである。 1.6 系の環境なら特に気にする必要はないだろうが、 1.2 系の環境でコーディングを行う際は、将来 1.6 系以降へアップデートする可能性も考慮し、 1.6 系でもビルドできるよう考慮したほうが良いだろう。

ここで紹介するコードは 1.2 系、 1.6 系両方でビルド及び動作することを確認している。

## PNG画像入出力

以下、PNG画像の読み書きの方法を紹介する。 これまでと同様、ソースコード全体は [GitHub](https://github.com/ohmae/image-io) にて公開している。 PNGの入出力を記述しているのは [png.c](https://github.com/ohmae/image-io/blob/master/png.c) である。

これまでと異なり、画像フォーマットに依存する部分はライブラリに任せている。 決まった手順でそれら関数を呼び出しているだけなので、肝心の読み書きの処理は非常にシンプルなコードになっている。 ただし、この解説を通じて利用している画像データの構造体と、ライブラリで提供される構造体が異なり、 そのコンバート処理が必要なため行数としてはあまり短くはなっていないが、 処理内容はシンプルなもので難しいところはないと思う。

libpngの関数群を使う場合は、 png.h を inclue する必要がある。

1. `#include <png.h>`

このヘッダ内で、libpngの関数群とそれに関連する構造体等の定義が行われているのだが、 データ型の定義の仕方に少し癖があるのでそれをまず説明する。

png.h で定義されるデータ型及び関数は`png_`の接頭辞を持つ。 これで他のライブラリなどと名前空間の衝突を防いでいる。 また、データ型は、`png_struct`などという名前で定義されているのだが、 このデータ型のポインタ型、ポインタのポインタ型なども`typedef`を使って定義されている。 例えば、`png_struct`型のポインタ型として`png_structp`、 ポインタのポインタ型として`png_structpp`と言ったように、 **ポインタ型は末尾にp、ポインタのポインタ型は末尾にppがつくという形で定義されている。**

このルールを知っていればどうということはないのだが、 ポインタとして定義されているように見えない変数をポインタとして扱っていたり、 別の型のように見えて、ポインタ演算子で相互変換を行ったりするところで 混乱しないよう頭の片隅において読んで欲しい。

## PNG画像の読み込み

以下にPNG画像を読み込むコードを示す。 全体については [png.c](https://github.com/ohmae/image-io/blob/master/png.c) を参照

1. `image_t *read_png_stream(FILE *fp) {`
2.  `image_t *img = NULL;`
3.  `int i, x, y;`
4.  `int width, height;`
5.  `int num;`
6.  `png_colorp palette;`
7.  `png_structp png = NULL;`
8.  `png_infop info = NULL;`
9.  `png_bytep row;`
10.  `png_bytepp rows;`
11.  `png_byte sig_bytes[8];`
12.  `if (fread(sig_bytes, sizeof(sig_bytes), 1, fp) != 1) {`
13.  `return NULL;`
14.  `}`
15.  `if (png_sig_cmp(sig_bytes, 0, sizeof(sig_bytes))) {`
16.  `return NULL;`
17.  `}`
18.  `png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);`
19.  `if (png == NULL) {`
20.  `goto error;`
21.  `}`
22.  `info = png_create_info_struct(png);`
23.  `if (info == NULL) {`
24.  `goto error;`
25.  `}`
26.  `if (setjmp(png_jmpbuf(png))) {`
27.  `goto error;`
28.  `}`
29.  `png_init_io(png, fp);`
30.  `png_set_sig_bytes(png, sizeof(sig_bytes));`
31.  `png_read_png(png, info, PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, NULL);`
32.  `width = png_get_image_width(png, info);`
33.  `height = png_get_image_height(png, info);`
34.  `rows = png_get_rows(png, info);`
35.  `// 画像形式に応じて詰め込み`
36.  `switch (png_get_color_type(png, info)) {`
37.  `case PNG_COLOR_TYPE_PALETTE: // インデックスカラー`
38.  `if ((img = allocate_image(width, height, COLOR_TYPE_INDEX)) == NULL) {`
39.  `goto error;`
40.  `}`
41.  `png_get_PLTE(png, info, &palette, &num);`
42.  `img->palette_num = num;`
43.  `for (i = 0; i < num; i++) {`
44.  `png_color pc = palette[i];`
45.  `img->palette[i] = color_from_rgb(pc.red, pc.green, pc.blue);`
46.  `}`
47.  `{`
48.  `png_bytep trans = NULL;`
49.  `int num_trans = 0;`
50.  `if (png_get_tRNS(png, info, &trans, &num_trans, NULL) == PNG_INFO_tRNS`
51.  `&& trans != NULL && num_trans > 0) {`
52.  `for (i = 0; i < num_trans; i++) {`
53.  `img->palette[i].a = trans[i];`
54.  `}`
55.  `for (; i < num; i++) {`
56.  `img->palette[i].a = 0xff;`
57.  `}`
58.  `}`
59.  `}`
60.  `for (y = 0; y < height; y++) {`
61.  `row = rows[y];`
62.  `for (x = 0; x < width; x++) {`
63.  `img->map[y][x].i = *row++;`
64.  `}`
65.  `}`
66.  `break;`
67.  `case PNG_COLOR_TYPE_GRAY: // グレースケール`
68.  `if ((img = allocate_image(width, height, COLOR_TYPE_GRAY)) == NULL) {`
69.  `goto error;`
70.  `}`
71.  `for (y = 0; y < height; y++) {`
72.  `row = rows[y];`
73.  `for (x = 0; x < width; x++) {`
74.  `img->map[y][x].g = *row++;`
75.  `}`
76.  `}`
77.  `break;`
78.  `case PNG_COLOR_TYPE_GRAY_ALPHA: // グレースケール+α`
79.  `if ((img = allocate_image(width, height, COLOR_TYPE_RGBA)) == NULL) {`
80.  `goto error;`
81.  `}`
82.  `for (y = 0; y < height; y++) {`
83.  `row = rows[y];`
84.  `for (x = 0; x < width; x++) {`
85.  `uint8_t g = *row++;`
86.  `img->map[y][x].c.r = g;`
87.  `img->map[y][x].c.g = g;`
88.  `img->map[y][x].c.b = g;`
89.  `img->map[y][x].c.a = *row++;`
90.  `}`
91.  `}`
92.  `break;`
93.  `case PNG_COLOR_TYPE_RGB: // RGB`
94.  `if ((img = allocate_image(width, height, COLOR_TYPE_RGB)) == NULL) {`
95.  `goto error;`
96.  `}`
97.  `for (y = 0; y < height; y++) {`
98.  `row = rows[y];`
99.  `for (x = 0; x < width; x++) {`
100.  `img->map[y][x].c.r = *row++;`
101.  `img->map[y][x].c.g = *row++;`
102.  `img->map[y][x].c.b = *row++;`
103.  `img->map[y][x].c.a = 0xff;`
104.  `}`
105.  `}`
106.  `break;`
107.  `case PNG_COLOR_TYPE_RGB_ALPHA: // RGBA`
108.  `if ((img = allocate_image(width, height, COLOR_TYPE_RGBA)) == NULL) {`
109.  `goto error;`
110.  `}`
111.  `for (y = 0; y < height; y++) {`
112.  `row = rows[y];`
113.  `for (x = 0; x < width; x++) {`
114.  `img->map[y][x].c.r = *row++;`
115.  `img->map[y][x].c.g = *row++;`
116.  `img->map[y][x].c.b = *row++;`
117.  `img->map[y][x].c.a = *row++;`
118.  `}`
119.  `}`
120.  `break;`
121.  `}`
122.  `error:`
123.  `png_destroy_read_struct(&png, &info, NULL);`
124.  `return img;`
125. `}`

### マジックナンバーのチェック

まず最初に行っているのがマジックナンバーのチェックだ。

1.  `png_byte sig_bytes[8];`
2.  `if (fread(sig_bytes, sizeof(sig_bytes), 1, fp) != 1) {`
3.  `return NULL;`
4.  `}`
5.  `if (png_sig_cmp(sig_bytes, 0, sizeof(sig_bytes))) {`
6.  `return NULL;`
7.  `}`

PNG 形式と明らかに異なるものを検出するための処理であり、この処理は必須ではない。 処理内容としては、 PNG ファイルは先頭 8Byte は`89 50 4E 47 0D 0A 1A 0A`と決まっており、 この値が一致するかの確認が行われている。

この 8Byte の詳細は割愛するが、 `50 4E 47`はASCIIコードの「PNG」になっているので、 テキストエディタで開いてもPNGファイルであることを識別しやすいようになっているという点は覚えておくと良いだろう。 ただ、日本語環境ではSJISと判定されて`89 50 4E 47`で「臼NG」と表示される場合が多いようだ。

以下がマジックナンバーのチェックを行う関数だ。

1. `int png_sig_cmp(png_bytep sig, png_size_t start, png_size_t num_to_check);`

`png_byte`は png.h で定義された 1Byte 符号なし整数型であり、`png_bytep`はそのポインタである。 合致した場合 0 が戻り、問題がある場合は 0 以外の値が返る。 そのため戻り値を真偽値として判定すると、合致した場合に偽となる。

`sig`はマジックナンバーを含むバイト配列へのポインタ、 `start`は比較の開始位置、`num_to_check`は比較する長さを指定する。 通常は`start`は 0 、`num_to_ckeck`は 8 を指定する。 あまりそのような必要性はないだろうが、 マジックナンバーの一部のみ比較したい場合はこれらの値を変更する。

### 構造体の初期化

まずは、読み込みに使用する構造体の準備を行う。 libpngでは`png_struct`と`png_info`という２つの構造体を利用し読み書きを行う。

1.  `png_structp png = NULL;`
2.  `png_infop info = NULL;`
3.  `...`
4.  `png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);`
5.  `if (png == NULL) {`
6.  `goto error;`
7.  `}`
8.  `info = png_create_info_struct(png);`
9.  `if (info == NULL) {`
10.  `goto error;`
11.  `}`
12.  `if (setjmp(png_jmpbuf(png))) {`
13.  `goto error;`
14.  `}`
15.  `png_init_io(png, fp);`
16.  `png_set_sig_bytes(png, sizeof(sig_bytes));`

以下の関数で`png_struct`構造体の確保を行い、読み出し処理用に初期化を行う。

1. `png_structp png_create_read_struct(png_const_charp user_png_ver,`
2.  `png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);`

`user_png_ver`は`PNG_LIBPNG_VER_STRING`という定数を渡す。 この定数は png.h 内で以下のよう定義されていて、バージョンを示す文字列になっている。

1. `#define PNG_LIBPNG_VER_STRING "1.6.18"`

この引数でビルド時に利用しているヘッダファイルと、リンクされたライブラリのミスマッチが無いかのチェックが行われる。 マイナーバージョン以上が異なる場合はバイナリ互換が担保されないため、警告が出るようになっている。 （通常「.」区切りのバージョンは上位からメジャーバージョン・マイナーバージョン・パッチバージョンと呼ばれる）

その他の引数はエラー処理に利用される。`error_ptr`はユーザ定義の任意のポインタを登録する場合に利用する。 使用例としては今から読み込もうとしているファイル名などを登録しておき、エラー時の表示に利用するなどである。 名前にエラーと付いているが、エラー処理以外に利用することも可能だ。 `error_fn``warn_fn`はエラー発生時にコールされるコールバック関数である。 いずれも、エラー処理を自前で実装する場合に指定する。 NULLを指定した場合はデフォルトのエラー処理が実行される。

1. `png_infop png_create_info_struct(png_structp png_ptr);`

`png_struct`の初期化が終わると、それを元に`png_info`構造体を確保、初期化を行う。 以降、この２つの構造体を使って読み書きの処理が行われる。 読み出したデータへのアクセスもこの２つの構造体を指定し、アクセス関数を呼び出すという形になる。

1.  `if (setjmp(png_jmpbuf(png))) {`
2.  `goto error;`
3.  `}`

ここでは、libpng内部の処理でエラーが発生した場合に、制御を戻すための実行コンテキストの保存を行っている。 保存処理が行われた時は戻り値は偽である。 libpngの処理中にエラーが発生した場合は内部で`longjmp`がコールされ、 制御がこの位置に戻る。制御が戻った時の戻り値は真となるため、 if文の中にはエラーで抜けてきた場合の処理を書く。

`setjump``longjump`は、 よく利用の是非で話題にあげられる`goto`よりもさらに大胆な制御を行う。 `goto`は一つの関数内で制御を移動させるものだが、 `setjump``longjump`は、関数間で制御の移動が発生する。 そのため、不用意に使用すると非常に危険であり、多くの開発の現場では使用が禁止されているだろう。

ただし、C++やJavaなどの言語での throw / catch で実現される例外処理の原型とでも言うべき機能であり、 この機能そのものが悪というわけではなく、危険性も含めてよく理解し、適切に利用すれば問題はない。

`setjmp`を実行していない状態で libpng 内部でエラーが発生した場合、 アボートがコールされ、プログラム全体が強制終了する。 実験用のプログラムならアボートしても構わない場合もあるだろうが、 通常はlibpngの処理ができなかったからといってプログラム全体が強制終了してもらっては困るはずだ。 適切に設定し、エラー処理を行うようにする必要がある。

1. `void png_init_io(png_structp png_ptr, png_FILE_p fp);`

読み込みを行うため、リード属性でオープン済みのファイルストリームを登録する。 ここでは構造体へ引数ポインタが格納されるだけであり、この関数をコールした時点ではまだ読み込み処理は実行されない。 引数の型が`png_FILE_p`という名前になっているが、通常のファイル入出力で利用する FILE 構造体へのポインタである。

1. `void png_set_sig_bytes(png_structp png_ptr, int num_bytes);`

ファイルストリームから既に読みだしてしまったマジックナンバーの長さを設定する。 マジックナンバーのチェックを行っていない場合は、この処理は必要ない。

以上で画像データを読み込む準備が完了する。

### 画像データの読み込み

PNG画像の読み込み処理は以下の関数で行われる。 読み込み処理はこの関数内で完結するため、この関数コールのみである。 読み込み処理を一気に行ってしまう高レベル API 以外に、個々の読み込み処理を記述できる低レベル API も用意されている。 読み込み処理の過程をカスタマイズしたい場合などでは低レベル API を利用する。

1. `void png_read_png(png_structp png_ptr, png_infop info_ptr,`
2.  `int transforms, png_voidp params);`

`png_ptr``info_ptr`で指定する構造体は初期化処理で準備した構造体である。 `transforms`で指定するのは、読み込み処理のオプションをビット和で指定する。 コード例で指定している値は`PNG_TRANSFORM_PACKING`と`PNG_TRANSFORM_STRIP_16`だ。 `PNG_TRANSFORM_PACKING`は 8bit より小さいビット深度の場合に 8bit 深度に拡張変換を行う指定だ。 また、`PNG_TRANSFORM_STRIP_16`は 16bit 深度の場合に、 8bit に丸める変換を行う指定である。 上記２つの値を設定することで、全て 8bit 値として処理できるようになる。 今回、画像情報を格納する表現方法として RGB 各色 8bit 深度での表現を採用しているため、 この指定をしておけば読み出し後に変換処理を自前で実装する手間が省ける。 その他のオプションとその意味については[マニュアル](http://www.libpng.org/pub/png/libpng-manual.txt)を参照。 `params`は定義されているが、公式に使用されないパラメータなのでNULLを指定する。

これで読み込みの処理は完了し、読み込まれたデータは`png_struct`及び`png_info`型構造体の中に格納される。 以降はそれぞれの構造体に格納されたデータを読みだす処理になる。

### 画像情報の参照

以下の関数を利用して画像の高さと幅を読みだす。 戻り値はいずれも符号なし 32bit 整数だ。

1. `png_uint_32 png_get_image_width(png_structp png_ptr, png_infop info_ptr);`
2. `png_uint_32 png_get_image_height(png_structp png_ptr, png_infop info_ptr);`

以下の関数を利用して、画像データを読みだす。 戻り値は 符号なし 8bit 整数のポインタのポインタである。 格納方法の基本的な考え方は、読み出し先である構造体と似ていて 横方向の画素情報を格納した配列があり、その配列を格納した配列という構成になっている。 横方向の画素情報の内訳については、この後に読み出す画像タイプによって異なる。

1. `png_bytepp png_get_rows(png_structp png_ptr, png_infop info_ptr);`

以下の関数で画像種別（色の表現方法）を読みだし、その値に基づき読み出し処理を分岐させている。

1. `png_byte png_get_color_type(png_structp png_ptr, png_infop info_ptr);`

画像タイプがインデックスカラーであった場合は、カラーパレットの情報を読みだす必要がある。 カラーパレットの読み出しは以下の関数を利用する。

1. `png_uint_32 png_get_PLTE(png_structp png_ptr, png_infop info_ptr,`
2.  `png_colorp * palette, int * num_palette);`

`palette`にカラーパレットの色を表現する構造体の配列へのポインタが格納され。 `num_palette`にパレットの数が格納される。 カラーパレットの色は`png_color`という以下の構造体で表現される。

1. `typedef struct png_color_struct`
2. `{`
3.  `png_byte red;`
4.  `png_byte green;`
5.  `png_byte blue;`
6. `} png_color;`

インデックスカラーについてはもう一つ処理を行っている。

1.  `png_bytep trans = NULL;`
2.  `int num_trans = 0;`
3.  `if (png_get_tRNS(png, info, &trans, &num_trans, NULL) == PNG_INFO_tRNS`
4.  `&& trans != NULL && num_trans > 0) {`
5.  `for (i = 0; i < num_trans; i++) {`
6.  `img->palette[i].a = trans[i];`
7.  `}`
8.  `for (; i < num; i++) {`
9.  `img->palette[i].a = 0xff;`
10.  `}`
11.  `}`

これは透過色指定に対応するための処理だ。 最近はあまり見かけないが、GIF形式は透過色指定での透過しかサポートしていなかったり、 Internet Explorerが7になるまでは、アルファチャンネルが扱えなかったり、という経緯で、 かつては透過色指定の透過機能もよく利用されていた。 PNGの仕様上はRGBやグレースケールであっても透過色の指定が可能なのだが、 そちらについての処理は省略している。

1. `png_uint_32 png_get_tRNS(png_structp png_ptr, png_infop info_ptr,`
2.  `png_bytep * trans, int * num_trans, png_color_16p * trans_values);`

透過色指定の情報はこの関数で取得することができる。 透過色指定は必ずしもあるとは限らない、 情報がある場合は戻り値が`PNG_INFO_tRNS`となるためそこで判断する。

インデックスカラーの場合の透過色指定は、`trans``num_trans`の値を参照し、 RGBやグレースケールでは`trans_values`の値を参照する。 `trans`にはカラーパレットの各色に対応するアルファ値が格納されている。 `num_trans`は`trans`に格納されたアルファ値の数である。

`num_trans`はカラーパレットの数と同じかそれより少なく、 数に差がある場合は残りの色のアルファ値は全て 255 として解釈する。 通常は、透過色 1 色のみを指定するため、カラーパレットの順番を最適化し、透過色がパレットの先頭にあり、 `num_trans`は 1 `trans[0]`が 0 という構成になっている場合が多いだろう。

格納されるアルファ値は 0 と 255 のみという制約もなく、0～255の任意の値が格納できるので、 仕様上は特定の色を完全に透過させるだけでなく、カラーパレットの色全てに 8bit 深度のアルファ値を設定することも可能だ。 ただし、そのようなPNG画像を作成したとしても正常に扱えるソフトウェアはごく限られたものになるだろう。

### 画像データの変換

読み出し処理の`switch`文以降はバイト配列を読み出し先のフォーマットに合わせて変換する処理になる。 （インデックスカラーについてはカラーパレットの読み出し、透過色指定の読み出しが加わる） いずれも直感的にわかりやすい格納順序になっていると思う。 `PNG_COLOR_TYPE_PALETTE`はカラーパレットのインデックス値、 `PNG_COLOR_TYPE_GRAY`は輝度、 `PNG_COLOR_TYPE_GRAY_ALPHA`は輝度、アルファ値、 `PNG_COLOR_TYPE_RGB` は R, G, B の各値、 `PNG_COLOR_TYPE_RGB_ALPHA`は R, G, B, α の各値、 の順で格納されているため、格納先の構造体に合わせて格納していく。 グレースケール＋アルファ値については読み出し先の構造体でそのまま保持することができないため RGBAとして格納している。

### 構造体の開放

読み出し処理が完了したあとは、`png_struct`と`info_stuct`構造体を開放する。 この構造体そのものもそうだが、読み出し処理の過程で読み出されたチャンク情報や複合された画像データなどを格納するため、 随時メモリ確保され、そのポインタがこれら構造体に登録されている。 ライブラリ内部で確保されたこれらメモリは、この関数の呼び出しで全て開放される。

1. `void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr,`
2.  `png_infopp end_info_ptr_ptr);`

引数に`png_info`が2つあるのが気になるかもしれない。 これは低レベル API を利用し、読み出しを行った場合に、画像データの前後でチャンク情報を別々に保持したい場合に `png_info`を2つ用意し、使い分ける。 この時、一つの読み出し処理に対して`png_info`構造体が2つ出てくるためその時に使用する。 高レベル API ではそもそも使い分けることができないので、`end_info_ptr_ptr`にはNULLを指定する。

以上で読み出し処理が完了である。 どのような関数をどのような順で呼び出すか、結果がどのように格納されているか、 さえ理解してしまえば非常に簡単に実装できると思う。

## PNG画像の書き出し

以下にPNG画像を書き出すコードを示す。 全体については [png.c](https://github.com/ohmae/image-io/blob/master/png.c) を参照

1. `result_t write_png_stream(FILE *fp, image_t *img) {`
2.  `int i, x, y;`
3.  `result_t result = FAILURE;`
4.  `int row_size;`
5.  `int color_type;`
6.  `png_structp png = NULL;`
7.  `png_infop info = NULL;`
8.  `png_bytep row;`
9.  `png_bytepp rows = NULL;`
10.  `png_colorp palette = NULL;`
11.  `if (img == NULL) {`
12.  `return result;`
13.  `}`
14.  `switch (img->color_type) {`
15.  `case COLOR_TYPE_INDEX: // インデックスカラー`
16.  `color_type = PNG_COLOR_TYPE_PALETTE;`
17.  `row_size = sizeof(png_byte) * img->width;`
18.  `break;`
19.  `case COLOR_TYPE_GRAY: // グレースケール`
20.  `color_type = PNG_COLOR_TYPE_GRAY;`
21.  `row_size = sizeof(png_byte) * img->width;`
22.  `break;`
23.  `case COLOR_TYPE_RGB: // RGB`
24.  `color_type = PNG_COLOR_TYPE_RGB;`
25.  `row_size = sizeof(png_byte) * img->width * 3;`
26.  `break;`
27.  `case COLOR_TYPE_RGBA: // RGBA`
28.  `color_type = PNG_COLOR_TYPE_RGBA;`
29.  `row_size = sizeof(png_byte) * img->width * 4;`
30.  `break;`
31.  `default:`
32.  `return FAILURE;`
33.  `}`
34.  `png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);`
35.  `if (png == NULL) {`
36.  `goto error;`
37.  `}`
38.  `info = png_create_info_struct(png);`
39.  `if (info == NULL) {`
40.  `goto error;`
41.  `}`
42.  `if (setjmp(png_jmpbuf(png))) {`
43.  `goto error;`
44.  `}`
45.  `png_init_io(png, fp);`
46.  `png_set_IHDR(png, info, img->width, img->height, 8,`
47.  `color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,`
48.  `PNG_FILTER_TYPE_DEFAULT);`
49.  `rows = png_malloc(png, sizeof(png_bytep) * img->height);`
50.  `if (rows == NULL) {`
51.  `goto error;`
52.  `}`
53.  `png_set_rows(png, info, rows);`
54.  `memset(rows, 0, sizeof(png_bytep) * img->height);`
55.  `for (y = 0; y < img->height; y++) {`
56.  `if ((rows[y] = png_malloc(png, row_size)) == NULL) {`
57.  `goto error;`
58.  `}`
59.  `}`
60.  `switch (img->color_type) {`
61.  `case COLOR_TYPE_INDEX: // インデックスカラー`
62.  `palette = png_malloc(png, sizeof(png_color) * img->palette_num);`
63.  `for (i = 0; i < img->palette_num; i++) {`
64.  `palette[i].red = img->palette[i].r;`
65.  `palette[i].green = img->palette[i].g;`
66.  `palette[i].blue = img->palette[i].b;`
67.  `}`
68.  `png_set_PLTE(png, info, palette, img->palette_num);`
69.  `for (i = img->palette_num - 1; i >= 0 && img->palette[i].a != 0xff; i--);`
70.  `if (i >= 0) {`
71.  `int num_trans = i + 1;`
72.  `png_byte trans[255];`
73.  `for (i = 0; i < num_trans; i++) {`
74.  `trans[i] = img->palette[i].a;`
75.  `}`
76.  `png_set_tRNS(png, info, trans, num_trans, NULL);`
77.  `}`
78.  `png_free(png, palette);`
79.  `for (y = 0; y < img->height; y++) {`
80.  `row = rows[y];`
81.  `for (x = 0; x < img->width; x++) {`
82.  `*row++ = img->map[y][x].i;`
83.  `}`
84.  `}`
85.  `break;`
86.  `case COLOR_TYPE_GRAY: // グレースケール`
87.  `for (y = 0; y < img->height; y++) {`
88.  `row = rows[y];`
89.  `for (x = 0; x < img->width; x++) {`
90.  `*row++ = img->map[y][x].g;`
91.  `}`
92.  `}`
93.  `break;`
94.  `case COLOR_TYPE_RGB: // RGB`
95.  `for (y = 0; y < img->height; y++) {`
96.  `row = rows[y];`
97.  `for (x = 0; x < img->width; x++) {`
98.  `*row++ = img->map[y][x].c.r;`
99.  `*row++ = img->map[y][x].c.g;`
100.  `*row++ = img->map[y][x].c.b;`
101.  `}`
102.  `}`
103.  `break;`
104.  `case COLOR_TYPE_RGBA: // RGBA`
105.  `for (y = 0; y < img->height; y++) {`
106.  `row = rows[y];`
107.  `for (x = 0; x < img->width; x++) {`
108.  `*row++ = img->map[y][x].c.r;`
109.  `*row++ = img->map[y][x].c.g;`
110.  `*row++ = img->map[y][x].c.b;`
111.  `*row++ = img->map[y][x].c.a;`
112.  `}`
113.  `}`
114.  `break;`
115.  `}`
116.  `png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);`
117.  `result = SUCCESS;`
118.  `error:`
119.  `if (rows != NULL) {`
120.  `for (y = 0; y < img->height; y++) {`
121.  `png_free(png, rows[y]);`
122.  `}`
123.  `png_free(png, rows);`
124.  `}`
125.  `png_destroy_write_struct(&png, &info);`
126.  `return result;`
127. `}`

### 出力形式と行サイズの計算

はじめのswitch文では画像の形式から、libpng の出力形式への変換と、 1行のデータサイズを計算している。 いずれも見たままの処理なので特に説明は不要だろう。

### 構造体の初期化

次に行うのが構造体の初期化である。 これは読み込み時とほぼ同じ処理となる。

1.  `png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);`
2.  `if (png == NULL) {`
3.  `goto error;`
4.  `}`
5.  `info = png_create_info_struct(png);`
6.  `if (info == NULL) {`
7.  `goto error;`
8.  `}`
9.  `if (setjmp(png_jmpbuf(png))) {`
10.  `goto error;`
11.  `}`
12.  `png_init_io(png, fp);`

`png_struct`を書き出し用に初期化する。この関数のプロトタイプは以下であり、引数は読み込み時に利用する `png_create_read_struct`と同じだ。

1. `png_structp png_create_write_struct(png_const_charp user_png_ver,`
2.  `png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);`

それ以外の関数は読み込みと同じで、`png_struct`を元に`png_info`を初期化する。 エラー時に制御を戻すための実行コンテキストの保存を行い、 書き出し先のファイルストリームを登録する。

### 画像情報の登録

以下の処理で行っているのが、画像情報の登録である。 幅、高さ、ビット深度、画像タイプ、インタレースの有無、圧縮タイプ、フィルタータイプをまとめて設定する。

1.  `png_set_IHDR(png, info, img->width, img->height, 8,`
2.  `color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,`
3.  `PNG_FILTER_TYPE_DEFAULT);`

この関数のプロトタイプ宣言としては以下

1. `void png_set_IHDR(png_structp png_ptr, png_infop info_ptr,`
2.  `png_uint_32 width, png_uint_32 height, int bit_depth, int color_type,`
3.  `int interlace_type, int compression_type, int filter_type);`

`bit_depth`は、色のビット深度ではなくチャンネルごとのビット深度を指定する。 インデックスカラーについてのみパレットインデックスのビット数を指定する。 ここでは無条件に 8 としているが、インデックスカラーでパレットの数が少ない場合はそのビット数を選択したほうが良いだろう。

`interlace_type`は、 `PNG_INTERLACE_NONE`でインタレースなし、 `PNG_INTERLACE_ADAM7`インタレースありになる。 インタレースありにすると少しサイズが大きくなるが、データの取得中に徐々に詳細化していく表示が可能となる。

`compression_type`は、 引数として用意されているが、`PNG_COMPRESSION_TYPE_DEFAULT`以外の値は定義されておらず、 この値を指定する必要がある。

`filter_type`は、通常のPNG画像であれば、`PNG_FILTER_TYPE_DEFAULT`を指定する必要がある。 `PNG_INTRAPIXEL_DIFFERENCING`という値も定義されているが、これはMNGデータが埋め込まれている場合に指定するため、 通常使うことはないだろう。

### 画像データメモリの確保

以下で行っているのが、書き込み画像データの格納先メモリの確保である。 画像情報はポインタのポインタになっており、行方向データを格納する配列を格納する配列という構成になっている。

1.  `rows = png_malloc(png, sizeof(png_bytep) * img->height);`
2.  `if (rows == NULL) {`
3.  `goto error;`
4.  `}`
5.  `png_set_rows(png, info, rows);`
6.  `memset(rows, 0, sizeof(png_bytep) * img->height);`
7.  `for (y = 0; y < img->height; y++) {`
8.  `if ((rows[y] = png_malloc(png, row_size)) == NULL) {`
9.  `goto error;`
10.  `}`
11.  `}`

列方向のポインタ配列のメモリを確保し、`png_set_rows`で登録、 次に行方向のメモリを確保し、はじめのポインタ配列へ格納していく。 すこし順序がおかしい印象を受けるかもしれないが、 `png_set_rows`では、ポインタの値が内部で構造体に格納されるだけなので、 行方向のメモリ確保前に登録を行っても問題は発生しない。

### パレット情報の登録

インデックスカラーの場合はパレット情報の登録が必要となる。

1.  `palette = png_malloc(png, sizeof(png_color) * img->palette_num);`
2.  `for (i = 0; i < img->palette_num; i++) {`
3.  `palette[i].red = img->palette[i].r;`
4.  `palette[i].green = img->palette[i].g;`
5.  `palette[i].blue = img->palette[i].b;`
6.  `}`
7.  `png_set_PLTE(png, info, palette, img->palette_num);`
8.  `png_free(png, palette);`

カラーパレットは`png_color`型の配列で表現されるため 格納先のメモリを確保し、カラーパレットの情報を移し替え、登録する。 カラーパレットについては、引数で渡した配列がそのまま構造体に登録されるわけではなく、 別途確保されたメモリへコピーされる。 そのため、`png_set_PLTE`をコールしたあとは、すぐにメモリを開放して問題ない。 ここでは`png_malloc`を使用して動的にメモリを確保しているが、 データ量が大きく変動するわけでもなく、必要となるサイズもそれほど大きくないため、 オート変数として配列定義したほうが実装の筋としては良いかもしれない。

1.  `for (i = img->palette_num - 1 ; i >= 0 && img->palette[i].a != 0xff; i--);`
2.  `if (i >= 0) {`
3.  `int num_trans = i + 1;`
4.  `png_byte trans[255];`
5.  `for (i = 0; i < num_trans; i++) {`
6.  `trans[i] = img->palette[i].a;`
7.  `}`
8.  `png_set_tRNS(png, info, trans, num_trans, NULL);`
9.  `}`

次に透過色情報の登録を行う。 はじめの for 文では、アルファ値が 255 でない（透明度のある）色が初めて現れる場所を後ろから調べている。 この理由は、アルファ値の情報がない場合は不透明と解釈されるので、 透明度を持つ最後のパレットまでの透過情報だけを登録すれば良いためである。 透明度を持つ色が見つかれば、前方からその色までのアルファ値の配列を作成し、`png_set_tRNS`を使って登録する。 透明度を持つ色までを登録する必要があるため、`num_trans`の値は見つかった位置に1を加算する必要がある点に注意。 先のカラーパレットと同様に、アルファ値の配列は渡したポインタが構造体に登録されるわけではなく、 内部で確保されたメモリ領域にコピーされるため、メモリのライフサイクルに配慮する必要はない。 ここでは配列の大きさはたかだか 256 であり、メモリ確保を簡略化するため、オート変数の配列を利用している。

### 画像データの格納

インデックスカラーについては前項のパレット情報の登録が必要となるが、 それ以降は他の形式と同じく、画像情報の詰め込みを行う。 読み出しの時に格納される順序と同様に、 `PNG_COLOR_TYPE_PALETTE`はカラーパレットのインデックス値、 `PNG_COLOR_TYPE_GRAY`は輝度、 `PNG_COLOR_TYPE_RGB` は R, G, B の各値、 `PNG_COLOR_TYPE_RGB_ALPHA`は R, G, B, α の各値、 の順で格納していく。

### 書き出し処理

必要なデータの登録が完了したら、以下の関数をコールすることでPNGファイルの書き込み処理が行われる。 書き込みに必要な処理は全てこの関数内で完結する。 書き出しについても一気に全ての処理を行ってしまう高レベル API 以外に、 個々の書き出し処理を記述できる低レベル API も用意されている。

1. `void png_write_png(png_structp png_ptr, png_infop info_ptr,`
2.  `int transforms, png_voidp params);`

`transforms`には書き出しでの変換処理をビット和で指定する。 ここでは`PNG_TRANSFORM_IDENTITY`を指定し、何も行わない指定にしている。 インデックスカラーで、ビット深度が 8 より小さい場合は`PNG_TRANSFORM_PACKING`を指定し、 1色1Byteで詰め込んだデータをビット単位で詰め込み直しを行わせることもできる。 `params`は未使用のパラメータなので`NULL`を指定する。

### メモリの開放

書き出しが終了したら、途中で確保したメモリの開放を行う。 まず、画像データについて開放を行う。 読み出しの場合は、libpng内部でメモリ確保が行われているため、destroy関数が自動で開放してくれるが、 書き出しではライブラリ外部でメモリ確保を行う関係上、destroy関数では開放してくれないので注意。

1.  `if (rows != NULL) {`
2.  `for (y = 0; y < img->height; y++) {`
3.  `png_free(png, rows[y]);`
4.  `}`
5.  `png_free(png, rows);`
6.  `}`

最後に以下の関数を使って、書き込みに使用した`png_struct`と`png_info`の開放を行う。

1. `void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);`

書き出しの場合は、`png_info`は一つだけだ。

以上で書き出し処理は完了となる。

libpng を利用したPNG画像の読み書き処理についての説明は以上になる。 ライブラリを使用する場合、ライブラリの仕様をしっかりと理解する必要があるが、 理解できていればあと用意された関数を呼びだけでその機能を自分のプログラム内に組み込むことが可能だ。