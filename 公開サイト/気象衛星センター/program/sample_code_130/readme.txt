MSC has developed a C sample program for reading the Himawari Standard Data.
It prints out the header dump, the (pixel, line) <-> (longitude, latitude) conversion, and the digital count -> radiance -> TBB/ALBEDO conversion at some particular points.
It has been compiled and checked on LINUX (RedHat, 64bit)
We would appreciate it if you could give us some comments or/and bug reports (E-mail: jma-msc-contact@ml.kishou.go.jp).

Files:
    hisd.h                 - define the structure of the header of the Himawari Standard Data
    main.c                 - main function
    hisd_info.c            - function for printing out header information
    hisd_pixlin2lonlat.c   - function for projection transformation
    hisd_read.c            - function for reading the Himawari Standard Data

Make/Run:
    (1) extract zip file      (>unzip sample_code_130.zip     )
    (2) make executable file  (>make                       )
    (3) run the file          (>hisd_sample SampleFileName )

Note:
	The invalid values of the output are followings:
        -9999 in (Lon,Lat) means out of the Earth
        -9999 in (Pix,Lin) means out of the observation area
        -10000000000.0000 in digital count/radiance/TBB/ALBEDO means invalid data

Disclaimer:
    MSC does not guarantee regarding the correctness, accuracy, reliability, or any other aspect regarding use of these sample codes.

Detail of Himawari Standard Format:
    For data structure of Himawari Standard Format, please refer to MSC Website and Himawari Standard Data User's Guid.

    MSC Website
    https://www.data.jma.go.jp/mscweb/en/index.html

    Himawari Standard Data User's Guid
    https://www.data.jma.go.jp/mscweb/en/himawari89/space_segment/hsd_sample/HS_D_users_guide_en_v13.pdf

History
    April,   2014  First release
    January, 2015  Change for version 1.1
    May,     2015  Change for version 1.2
    June,    2015  Version 2015-06
                   Fixed bug in funcntion lonlat_to_pixlin() (hisd_pixlin2lonlat.c)
                   ((8) check the reverse side of the Earth)
                   Fixed bug in funcntion hisd_read_header() (hisd_read.c)
    June,    2017  Change for version 1.3
    January, 2022  modification to handle both version of 1.2 and 1.3
