/* ----------------------------------------------------------------------------
	Sample source code for Himawari Standard Data

	Copyright (C) 2014 MSC (Meteorological Satellite Center) of JMA

	Disclaimer	:
		MSC does not guarantee regarding the correctness, accuracy, reliability,
		or any other aspect regarding use of these sample codes.

	Detail of Himawari Standard Format : 
		For data structure of Himawari Standard Format, prelese refer to MSC
		Website and Himawari Standard Data User's Guid.

		MSC Website
		https://www.data.jma.go.jp/mscweb/en/index.html

		Himawari Standard Data User's Guid
		https://www.data.jma.go.jp/mscweb/en/himawari89/space_segment/hsd_sample/HS_D_users_guide_en_v13.pdf

	History
	April,   2014  First release
	January, 2015  Change for version 1.1
        June,    2015  Change for version 1.2
        June,    2015  Version 2015-06
                       Fixed bug in funcntion lonlat_to_pixlin() (hisd_pixlin2lonlat.c)
                       ((8) check the reverse side of the Earth)
                       Fixed bug fixed of hisd_read_header() (hisd_read.c)
	June,    2017  Change for version 1.3
	January, 2022  modification to handle both version of 1.2 and 1.3
---------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hisd.h"

#define NORMAL_END 0
#define ERROR_ARG 1
#define ERROR_FILE_OPEN 2
#define ERROR_CALLOCATE 3
#define ERROR_READ_HEADER 4
#define ERROR_INFO 5

/*--------------------------------------------------------------------------- */
int main(int argc, char **argv){

	HisdHeader *header;
	char *InFile;
	FILE *fp;

	int  ii;
	
	/* ----------------------------------------------------------------------*/
	if(argc != 2){
		char *cPtr=strrchr(argv[0],'/');
		if(cPtr==NULL)
			{
			cPtr=argv[0];
			}
		else
			{
			cPtr++;
			}
		fprintf(stderr,"usage : %s HISD_FILE\n",cPtr);
		return(ERROR_ARG);
	}
	InFile  = argv[1];
    if(NULL==(fp=fopen(InFile,"rb"))){
        fprintf(stderr,"file open error\n");
		return(ERROR_FILE_OPEN);
    }
	/* ----------------------------------------------------------------------*/
	/* header block */
	header =(HisdHeader *)calloc(1,sizeof(HisdHeader));
	if(	header == NULL	){
		fprintf(stderr,"calloc error\n");
		return(ERROR_CALLOCATE);
	}
	if(0 != hisd_read_header(header,fp)){
		fprintf(stderr,"hisd_read_header() : error");
		return(ERROR_READ_HEADER);
	}
	if(0 != hisd_info(header)){
		fprintf(stderr,"hisd_info() : error");
		return(ERROR_INFO);
	}
    /* ----------------------------------------------------------------------*/
	/* projection */
	double Lon[5],Lat[5];
	float  Pix[5],Lin[5];

	Pix[0] = header->data->nPix / 9 * 3;
	Pix[1] = header->data->nPix / 9 * 4;
	Pix[2] = header->data->nPix / 9 * 5;
	Pix[3] = header->data->nPix / 9 * 6;
	Pix[4] = header->data->nPix / 9 * 7;

	Lin[0] = header->seg->strLineNo + header->data->nLin / 6 * 1;
	Lin[1] = header->seg->strLineNo + header->data->nLin / 6 * 2;
	Lin[2] = header->seg->strLineNo + header->data->nLin / 6 * 3;
	Lin[3] = header->seg->strLineNo + header->data->nLin / 6 * 4;
	Lin[4] = header->seg->strLineNo + header->data->nLin / 6 * 5;

	printf("\n# convert from (pixel,line) to (longitude,latitude) ---\n");
	for(ii=0;ii<5;ii++){
		pixlin_to_lonlat(header,Pix[ii],Lin[ii],&Lon[ii],&Lat[ii]);
		printf("(Pix,Lin)(%8.1f,%8.1f) ==> (Lon,Lat)(%9.3f,%9.3f)\n",
			Pix[ii],Lin[ii],Lon[ii],Lat[ii]);
	}

	printf("\n# convert from (longitude,latitude) to (pixel,line) ---\n");
	for(ii=0;ii<5;ii++){
		lonlat_to_pixlin(header,Lon[ii],Lat[ii],&Pix[ii],&Lin[ii]);
		printf("(Lon,Lat)(%9.3f,%9.3f) ==> (Pix,Lin)(%6.1f,%6.1f)\n",
			Lon[ii],Lat[ii],Pix[ii],Lin[ii]);
	}
	printf("\n");

	/* ----------------------------------------------------------------------*/
	/* read data */
	unsigned short count_value[5];
	ii=0;

	printf("# Digital count of (longitude,latitude) ---\n");
	for(ii=0;ii<5;ii++){
		hisd_getdata_by_pixlin(header,fp,Pix[ii],Lin[ii],&count_value[ii]);
		printf("(Lon,Lat)(%9.3f,%9.3f) ==> count value = %d\n",
			Lon[ii],Lat[ii],count_value[ii]);
	}
	printf("\n");

	/* ----------------------------------------------------------------------*/
	/* physical value */
	double rad[5];
	double rad_corr[5];
	double tbb[5];
	double albedo[5];
	double albedo_corr[5];
	/* IR band */
        if( (header->calib->bandNo>=7 &&
             strstr(header->basic->satName,"Himawari")!=NULL ) ||
            (header->calib->bandNo>=2 &&
             strstr(header->basic->satName,"MTSAT-2") !=NULL )      )
		{
		printf("# Radiance of (longitude,latitude) ---\n");
		}
	/* VNIR band */
	else 
		{ /* 2022.01 added */
		printf("# Radiance of (longitude,latitude) ---\n");
                printf("# (For detail on the corrected radiance, see the following link.)\n");
                printf("# https://www.data.jma.go.jp/mscweb/en/oper/eventlog/Update_of_Calibration_Information_2021.pdf\n");
	 	}
	for(ii=0;ii<5;ii++){
		if(count_value[ii] == header->calib->outCount ||
		   count_value[ii] == header->calib->errorCount){
			rad[ii]=INVALID_VALUE;
		}else{
		/* IR band */
		if(	(header->calib->bandNo>=7 &&
			 strstr(header->basic->satName,"Himawari")!=NULL ) ||
			(header->calib->bandNo>=2 &&
			 strstr(header->basic->satName,"MTSAT-2") !=NULL )	)
			{
			rad[ii] = (double)count_value[ii] * header->calib->gain_cnt2rad +
					header->calib->cnst_cnt2rad;
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> radiance = %7.4f\n",
			Lon[ii],Lat[ii],rad[ii]);
			}
		/* VNIR band */
		else if( strcmp(header->basic->verName,"1.3") < 0) /* 2022.01 added */
			{
			rad[ii] = (double)count_value[ii] * header->calib->gain_cnt2rad +
                                         header->calib->cnst_cnt2rad;
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> radiance = %7.4f\n",
				Lon[ii],Lat[ii],rad[ii]);
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> radiance(corrected) = -----\n",
				Lon[ii],Lat[ii]);
			}
		else
			{
			rad[ii] = (double)count_value[ii] * header->calib->gain_cnt2rad +
                                         header->calib->cnst_cnt2rad;
			rad_corr[ii] = (double)count_value[ii] * header->calib->gain_cnt2rad_mod +
						header->calib->cnst_cnt2rad_mod;
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> radiance = %7.4f\n",
				Lon[ii],Lat[ii],rad[ii]);
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> radiance(corrected) = %7.4f\n",
				Lon[ii],Lat[ii],rad_corr[ii]);
			}
		}
	}
	printf("\n");

	/* Inrared Band (Band No. 7-16)/(Band No.2-5 : backup operation) */
	if(	(header->calib->bandNo>=7 && 
		 strstr(header->basic->satName,"Himawari")!=NULL ) ||
		(header->calib->bandNo>=2 && 
		 strstr(header->basic->satName,"MTSAT-2") !=NULL )	){
		
		printf("# Brightness temprature of (longitude,latitude) ---\n");
		for(ii=0;ii<5;ii++){
			hisd_radiance_to_tbb(header,rad[ii],&tbb[ii]);
			printf("(Lon,Lat)(%9.3f,%9.3f) ==> tbb = %5.2f\n",
				Lon[ii],Lat[ii],tbb[ii]);
		}
	/* Visible,Near Infrared Band (Band No. 1-6)/(Band No.1:backup operation)*/
	}else{
		printf("# Albedo of (longitude,latitude) ---\n");
		for(ii=0;ii<5;ii++){
			if(rad[ii] != INVALID_VALUE){
				if( strcmp(header->basic->verName,"1.3") < 0 ) /* 2022.01 added */
					{
					albedo[ii] = header->calib->rad2albedo * rad[ii];
					printf("(Lon,Lat)(%9.3f,%9.3f) ==> albedo = %5.3f\n",
						Lon[ii],Lat[ii],albedo[ii]);
					printf("(Lon,Lat)(%9.3f,%9.3f) ==> albedo(corrected) = -----\n",
						Lon[ii],Lat[ii]);
					}
				else
					{
					albedo[ii] = header->calib->rad2albedo * rad[ii];
					albedo_corr[ii] = header->calib->rad2albedo * rad_corr[ii];
					printf("(Lon,Lat)(%9.3f,%9.3f) ==> albedo = %5.3f\n",
						Lon[ii],Lat[ii],albedo[ii]);
					printf("(Lon,Lat)(%9.3f,%9.3f) ==> albedo(corrected) = %5.3f\n",
						Lon[ii],Lat[ii],albedo_corr[ii]);
					
					}
				
			}else{
				albedo[ii] = INVALID_VALUE;
			}
		}
	}
	printf("\n");
	/* ----------------------------------------------------------------------*/
	hisd_free(header);

	return(NORMAL_END);
}
