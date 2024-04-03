# 第10回 VL講習会@千葉大学CEReS コンピュータ演習資料

Last update: Oct. 07, 2016

## ◎ VL講習会で行ったコンピュータ演習は以下のいずれかの方法により自宅等のコンピュータでも実習できます。

1. [Dockerを使う方法](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#docker)
2. [Jupyter Notebookをインストールする方法 (ある程度Linuxの知識がある人向き)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#notebook)
3. [IPythonを使う方法 (PartAのみ)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#ipython)

## 1\. Dockerを使う方法

Dockerは仮想化ソフトウェアの一種で、これを使うとVL講習会のコンピュータ演習と同じ環境を簡単に再現することができます。  
VL講習会のコンピュータ演習環境を実装したDockerイメージ([vlceres/vl2016)](https://hub.docker.com/r/vlceres/vl2016/)をDocker Hubにて公開しています。

### Windows、Mac OS Xの場合

◎ Windows、Mac OS Xであれば、[Docker Toolbox](https://www.docker.com/products/docker-toolbox)をインストールすればdockerが使えるようになります。  
  

1. お使いのOSに合わせたインストーラをダウンロードし、インストーラの指示に従って[Docker Toolboxをインストール![Docker Toolboxをインストール](docker_toolbox_install.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)してください。  
    (以下の説明では、ピンク色の文字の上にマウスカーソルを乗せるとサンプル画像が表示されます。)  
      
    
2. [「Docker Quickstart Terminal」アイコン![「Docker Quickstart Terminal」アイコン](docker_icon.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)をダブルクリックするとDockerターミナル([コマンドプロンプトのような画面![コマンドプロンプトのような画面](docker_start.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#))が起動します。
  
4. Jupyterサーバを立ち上げるため、Dockerターミナルに[以下のコマンドを入力してください![以下のコマンドを入力してください](docker_run.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)。  
    `docker run -d -p 8888:8888 --name jupyter-server vlceres/vl2016`  
      
    なお、Dockerターミナル上で右クリックするとクリップボードにコピーしたテキストをペーストできます。  
    また、Dockerターミナル上のテキストをマウスでなぞって色を反転させた部分を右クリックするとクリップボードにコピーできます。  
    Dockerターミナルでは、矢印キーで履歴を呼び出したり、タブキーで補完することもできます。  
      
    ローカルにDockerイメージ(vlceres/vl2016)がない場合は  
    `Unable to find image 'vlceres/vl2016:latest' locally`  
    というメッセージが表示された後、[Dockerイメージのダウンロード![Dockerイメージのダウンロード](docker_run_download.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)が始まります。  
    Anaconda(約3GB)と演習に使用するファイル(約1GB)を合わせて約4GBのディスク容量が必要になります。  
    Dockerターミナルに[$マーク(プロンプト)が表示![$マーク(プロンプト)が表示](docker_run_finish.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)されたらJupyterサーバの立ち上げは完了です。  
      
    Jupyterサーバが正常に立ち上がっていれば、Dockerターミナルで  
    `docker ps`  
    を実行すると[Dockerコンテナの情報が表示![Dockerコンテナの情報が表示](docker_ps.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)されます。  
    また、Dockerターミナルで  
    `docker images`  
    を実行すると[ローカルに保存されたDockerイメージを確認![ローカルに保存されたDockerイメージを確認](docker_images.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)できます。
  
6. Webブラウザから  
    `http://192.168.99.100:8888`  
    にアクセスすれば[Jupyterサーバにログイン![Jupyterサーバにログイン](jupyter_notebook.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)できます。(パスワードはvl2016です。)  
      
    192.168.99.100の部分にはdocker-machineのIPアドレスが入ります。  
    IPアドレスはDockerターミナルを立ち上げた時に表示されますが、 Dockerターミナルで  
    `docker-machine ip default`  
    を実行して[IPアドレスを表示させる![IPアドレスを表示させる](docker_machine_ip.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)こともできます。
  
8. Jupyterサーバにログインした後は、テキストに従って演習を進めてください。  
      
    新しいNotebook(拡張子が.ipynbとなっているファイル)を開いたら、  
    [CellメニューのRun All![CellメニューのRun All](jupyter_run_all.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)を実行すると表示が初期化されます。  
    (特にPartAのRGB合成、PartB、HICでは初期化が必要です。)  
      
    ひまわり8号のNetCDFデータ、標準データ(PartAの05、06で使用)はデータ取り扱いポリシーによりDockerイメージには含めていません。  
    これらのデータは例えば[NICTのWebサイト](http://sc-web.nict.go.jp/himawari/himawari-data-archive.html)から取得できます。  
    まず、取得した圧縮ファイルを適当な場所(以下の例ではC:\\Users\\manag)に置き、Dockerターミナルで  
    `bzip2 -d NC_H08_20160512_0400_B04_JP01_R10.nc.bz2`  
    `bzip2 -d HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT.bz2`  
    を実行して[圧縮ファイルを展開![圧縮ファイルを展開](bzip2.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)します。  
    次に、Dockerターミナルで  
    `docker cp NC_H08_20160512_0400_B04_JP01_R10.nc jupyter-server:/root/VL2016/PartA/`  
    `docker cp HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT jupyter-server:/root/VL2016/PartA/`  
    を実行すると[Jupyterサーバ上にデータをコピー![Jupyterサーバ上にデータをコピー](docker_cp.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)できます。  
      
    演習に必要なグリッドデータはDockerイメージに含まれていますが、  
    [千葉大のWebサイト](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/index_jp.html)から他のグリッドデータを取得することもできます。  
    ※ フルディスクグリッドデータの画像サイズは演習で使用したグリッドデータと異なることに注意してください。
  
10. [Jupyterサーバを停止![Jupyterサーバを停止](docker_stop.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)させる時は、Dockerターミナルで  
    `docker stop jupyter-server`  
    を実行してください。  
      
    なお、[停止中のDockerコンテナの情報![停止中のDockerコンテナの情報](docker_ps_a.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)は、Dockerターミナルで  
    `docker ps -a`  
    を実行すると表示されます。
  
12. [Jupyterサーバを再起動![Jupyterサーバを再起動](docker_restart.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)する時は  
    `docker start jupyter-server`  
    を実行してください。
  
14. Dockerコンテナを削除する時は、  
    まず手順fにしたがってJupyterサーバを停止させてください。  
    その後、Dockerターミナルで  
    `docker rm jupyter-server`  
    を実行すると[Dockerコンテナを削除![Dockerコンテナを削除](docker_rm.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)できます。  
    (注) Dockerコンテナ上のファイルは全て削除されます。
  
16. コンテナ削除後にJupyterサーバを再起動する場合、  
    手順cと同様に、Dockerターミナルで  
    `docker run -d -p 8888:8888 --name jupyter-server vlceres/vl2016`  
    を実行してください。これで新規に初期状態のDockerコンテナが作成されます。  
    [ローカルにDockerイメージがある場合![ローカルにDockerイメージがある場合](docker_run_no_download.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)はDockerイメージをダウンロードしないですぐにプロンプトが表示されます。
  
18. Dockerイメージを削除する時は、  
    まず手順hにしたがってDockerコンテナを削除してください。  
    その後、Dockerターミナルで  
    `docker rmi vlceres/vl2016`  
    を実行すると[Dockerイメージを削除![Dockerイメージを削除](docker_rmi.png)](http://www.cr.chiba-u.jp/databases/VL/VL-Lecture2016/exercise/#)できます。  
    ここで、`rm`ではなく、`rmi`であることに注意してください。

### Linuxの場合

1. まだdockerがインストールされていない場合、 Ubuntuであれば  
    `sudo apt-get install docker.io`  
    でdockerをインストールできます。
  
3. すでにdockerがインストールされていれば、  
    `sudo docker run -d -p 8888:8888 --name jupyter-server vlceres/vl2016`  
    を実行するとJupyterサーバを立ち上げることができます。  
      
    ローカルにDockerイメージ(vlceres/vl2016)がない場合は  
    `Unable to find image 'vlceres/vl2016:latest' locally`  
    というメッセージが表示された後、Dockerイメージのダウンロードが始まります。  
    Anaconda(約3GB)と演習に使用するファイル(約1GB)を合わせて約4GBのディスク容量が必要になります。  
      
    Jupyterサーバが正常に立ち上がっていれば、  
    `sudo docker ps`  
    を実行するとDockerコンテナの情報が表示されます。  
    また、  
    `sudo docker images`  
    を実行するとローカルに保存されたDockerイメージを確認できます。
  
5. Webブラウザから  
    `http://localhost:8888`  
    にアクセスすればJupyterサーバにログインできます。(パスワードはvl2016です。)
  
7. Jupyterサーバにログインした後は、テキストに従って演習を進めてください。  
      
    新しいNotebook(拡張子が.ipynbとなっているファイル)を開いたら、  
    CellメニューのRun Allを実行すると表示が初期化されます。  
    (特にPartAのRGB合成、PartB、HICでは初期化が必要です。)  
      
    ひまわり8号のNetCDFデータ、標準データ(PartAの05、06で使用)はデータ取り扱いポリシーによりDockerイメージには含めていません。  
    これらのデータは例えば[NICTのWebサイト](http://sc-web.nict.go.jp/himawari/himawari-data-archive.html)から取得できます。  
    まず、取得した圧縮ファイルをカレントディレクトリに置き、  
    `bzip2 -d NC_H08_20160512_0400_B04_JP01_R10.nc.bz2`  
    `bzip2 -d HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT.bz2`  
    を実行して圧縮ファイルを展開します。  
    次に、  
    `sudo docker cp NC_H08_20160512_0400_B04_JP01_R10.nc jupyter-server:/root/VL2016/PartA/`  
    `sudo docker cp HS_H08_20160512_0400_B04_FLDK_R10_S0210.DAT jupyter-server:/root/VL2016/PartA/`  
    を実行するとJupyterサーバ上にデータをコピーできます。  
      
    演習に必要なグリッドデータはDockerイメージに含まれていますが、  
    [千葉大のWebサイト](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/index_jp.html)から他のグリッドデータを取得することもできます。  
    ※ フルディスクグリッドデータの画像サイズは演習で使用したグリッドデータと異なることに注意してください。
  
9. Jupyterサーバを停止させる時は、  
    `sudo docker stop jupyter-server`  
    を実行してください。  
      
    なお、停止中のDockerコンテナの情報は、  
    `sudo docker ps -a`  
    を実行すると表示されます。
  
11. Jupyterサーバを再起動する時は  
    `sudo docker start jupyter-server`  
    を実行してください。
  
13. Dockerコンテナを削除する時は、  
    まず手順eにしたがってJupyterサーバを停止させてください。  
    その後、  
    `sudo docker rm jupyter-server`  
    を実行するとDockerコンテナを削除できます。  
    (注) Dockerコンテナ上のファイルは全て削除されます。
  
15. コンテナ削除後にJupyterサーバを再起動する場合、  
    手順bと同様に、  
    `sudo docker run -d -p 8888:8888 --name jupyter-server vlceres/vl2016`  
    を実行してください。これで新規に初期状態のDockerコンテナが作成されます。  
    ローカルにDockerイメージがある場合はDockerイメージをダウンロードしないですぐにプロンプトが表示されます。
  
17. Dockerイメージを削除する時は、  
    まず手順gにしたがってDockerコンテナを削除してください。  
    その後、  
    `sudo docker rmi vlceres/vl2016`  
    を実行するとDockerイメージを削除できます。  
    ここで、`rm`ではなく、`rmi`であることに注意してください。

## 2\. Jupyter Notebookをインストールする方法 (ある程度Linuxの知識がある人向き)

Jupyter NotebookをUbuntuマシンにインストールする方法を以下に示します。  
  
以下ではAnacondaを/usr/local/anaconda3にインストールすることを前提に説明しますが、  
別の場所(例えば、$HOME/anaconda3)にインストールすることも可能です。  
  
Anacondaを$HOME以下にインストールした場合、/usr/local/anaconda3を$HOME/anaconda3に置き換えてください。  
この場合、手順c以降のコマンドにsudoを付ける必要はありません。

1. sudoの際にPATHを引き継ぐための設定
`sudo update-alternatives --config editor` # visudoで使うエディタを選択する。  
`sudo visudo` # "Defaults secure\_path = ..." の行をコメントアウトする。  
  
7. Node.jsのインストール
`sudo apt-get install npm`  
`sudo ln -s /usr/bin/nodejs /usr/bin/node`  
`sudo npm install -g configurable-http-proxy`  
  
15. Anacondaのインストール
`wget https://repo.continuum.io/archive/Anaconda3-4.1.1-Linux-x86_64.sh`  
`sudo /bin/bash Anaconda3-4.1.1-Linux-x86_64.sh` # 対話的にインストールを行う。install locationには/usr/local/anaconda3を指定する。  
`rm Anaconda3-4.1.1-Linux-x86_64.sh`  
`export PATH=/usr/local/anaconda3/bin:$PATH`  
  
25. 追加モジュールのインストール
`sudo conda install basemap netcdf4`  
  
29. Jupyter環境の整備
`sudo conda update pip ipython jupyter jupyter_core jupyter_console jupyter_client ipywidgets`  
`sudo -H pip install jupyter_contrib_nbextensions jupyter-js-widgets-nbextension jupyter_nbextensions_configurator images2gif`  
`sudo jupyter nbextension enable --py --sys-prefix widgetsnbextension`  
`jupyter contrib nbextension install --user`  
  
39. Jupyterのカスタム設定
`wget https://github.com/vlceres/vl2016/archive/master.zip`  
`unzip master.zip`  
`rm master.zip`  
`cd vl2016-master`  
`sudo cp custom.js /usr/local/anaconda3/lib/python3.5/site-packages/notebook/static/custom/`  
`sudo cp custom.css /usr/local/anaconda3/lib/python3.5/site-packages/notebook/static/custom/`  
`sudo cp style.min.css /usr/local/anaconda3/lib/python3.5/site-packages/notebook/static/style/`  
`cp jupyter_notebook_config.py ~/.jupyter/`  
  
57. Nbextensionsのカスタム設定
`cp exercise_main.js ~/.local/share/jupyter/nbextensions/exercise/main.js`  
`cp exercise2_main.js ~/.local/share/jupyter/nbextensions/exercise2/main.js`  
`cp exercise2_main.css ~/.local/share/jupyter/nbextensions/exercise2/main.css`  
`mkdir ~/.jupyter/nbconfig`  
`cp notebook.json ~/.jupyter/nbconfig/`  
`cp tree.json ~/.jupyter/nbconfig/`  
  
71. IPythonの設定
`ipython profile create`  
`echo "c.InlineBackend.rc = {'image.cmap':'gray'}" >>~/.ipython/profile_default/ipython_config.py`  
  
77. Python3用images2gifの設定
`sudo cp __init__.py /usr/local/anaconda3/lib/python3.5/site-packages/images2gif/`  
`sudo cp images2gif.py /usr/local/anaconda3/lib/python3.5/site-packages/images2gif/`  
`cd ..`  
`rm -rf vl2016-master`  
  
87. 演習に使用するファイルの準備
`cd ~`  
`wget http://www.cr.chiba-u.jp/~kuze-lab/temporary/VL2016.tar.bz2`  
`tar -xjf VL2016.tar.bz2`  
`rm VL2016.tar.bz2`  
  
97. Jupyter Notebookの起動
`cd VL2016`  
`jupyter notebook`  

## 3\. IPythonを使う方法 (PartAのみ)

コンピュータ演習のPartAのみ(コマンドを入力して出力を確認するだけ)であれば、WebベースのJupyter Notebookを使わなくても  
ターミナルで動作するIPythonを使って実習できます。  
  
◎ IPythonは[Anaconda](https://www.continuum.io/downloads)をインストールすれば使えるようになります。  
(Pythonのバージョンは3.5でも2.7でも問題ありませんが、講習会で使用したのは3.5です。)  
  
Anacondaをインストールする場合、以下のコマンドでnetCDF4、Basemapを追加してください。  
`sudo conda install netcdf4`  
`sudo conda install basemap`  
  
◎ IPythonを使う場合、Jupyter Notebook用のコード：`%matplotlib inline`は入力しないようにしてください。  
  
◎ 演習に必要なグリッドデータは以下のアーカイブに含まれています。  
`http://www.cr.chiba-u.jp/~kuze-lab/temporary/VL2016.tar.bz2`  
[千葉大のWebサイト](http://www.cr.chiba-u.jp/databases/GEO/H8_9/FD/index_jp.html)から他のグリッドデータを取得することもできます。  
※ フルディスクグリッドデータの画像サイズは演習で使用したグリッドデータと異なることに注意してください。  
NetCDFデータ、標準データは例えば[NICTのWebサイト](http://sc-web.nict.go.jp/himawari/himawari-data-archive.html)から取得できます。