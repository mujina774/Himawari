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
		May,     2015  Change for version 1.2
		June,    2017  Change for version 1.3

---------------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hisd.h"

/* ----------------------------------------------------------------------------
	hisd_info()
 ----------------------------------------------------------------------------*/
int hisd_info(HisdHeader *header){
	float version;
	int ii;

	/* -1--------------------------------------------------------------------*/
	printf("\n");
	printf("# 1  Basic informatin block --------\n");
	printf("header block number          : %d\n",header->basic->HeaderNum);
	printf("block length                 : %d\n",header->basic->BlockLen);
	printf("total number of header blocks: %d\n",header->basic->headerNum);
	printf("byte order                   : %d\n",header->basic->byteOrder);
	printf("satellite name               : %s\n",header->basic->satName);
	printf("processing center name       : %s\n",header->basic->proName);
	printf("observation area             : %s\n",header->basic->ObsType1);
	printf("other observation information: %s\n",header->basic->ObsType2);
	printf("observation Timeline         : %d\n",header->basic->TimeLine);
	printf("observation start time       : %f\n",header->basic->ObsStartTime);
	printf("observation end time         : %f\n",header->basic->ObsEndTime);
	printf("file creation time           : %f\n",header->basic->fileCreationMjd);
	printf("total header length          : %d\n",header->basic->totalHeaderLen);
	printf("total data length            : %d\n",header->basic->dataLen);
	printf("quality flag 1               : %d\n",header->basic->qflag1);
	printf("quality flag 2 (spare)       : %d\n",header->basic->qflag2);
	printf("quality flag 3               : %c\n",header->basic->qflag3);
	printf("quality flag 4               : %d\n",header->basic->qflag4);
	printf("file format version          : %s\n",header->basic->verName);
	printf("file name                    : %s\n",header->basic->fileName);
	printf("spare                        : %s\n",header->basic->spare);

	/* -2--------------------------------------------------------------------*/
	printf("\n");
	printf("# 2  Data information Block --------\n");
	printf("header block number          : %d\n",header->data->HeaderNum);
	printf("block length                 : %d\n",header->data->BlockLen);
	printf("number of bits per pixel     : %d\n",header->data->bitPix);
	printf("number of columns            : %d\n",header->data->nPix);
	printf("number of lines              : %d\n",header->data->nLin);
	printf("compression flag for data    : %d\n",header->data->comp);
	printf("spare                        : %s\n",header->data->spare);
	/* -3--------------------------------------------------------------------*/
	printf("\n");
	printf("# 3  Projection information block --\n");
	printf("header block number          : %d\n",header->proj->HeaderNum);
	printf("block length                 : %d\n",header->proj->BlockLen);
	printf("sub_lon                      : %f\n",header->proj->subLon);
	printf("CFAC                         : %d\n",header->proj->cfac);
	printf("LFAC                         : %d\n",header->proj->lfac);
	printf("COFF                         : %f\n",header->proj->coff);
	printf("LOFF                         : %f\n",header->proj->loff);
	printf("Rs                           : %f\n",header->proj->satDis);
	printf("Earth's equatorial radius    : %f\n",header->proj->eqtrRadius);
	printf("Earth's polar radius         : %f\n",header->proj->polrRadius);
	printf("(req^2 - rpol^2)/req^2       : %13.11f\n",header->proj->projParam1);
	printf("rpol^2 / req^2               : %13.11f\n",header->proj->projParam2);
	printf("req^2 / rpol^2               : %13.11f\n",header->proj->projParam3);
	printf("coefficient for Sd           : %f\n",header->proj->projParamSd);
	printf("resampling types             : %d\n",header->proj->resampleKind);
	printf("resampling size              : %d\n",header->proj->resampleSize);
	printf("spare                        : %s\n",header->proj->spare);
	/* -4--------------------------------------------------------------------*/
	printf("\n");
	printf("# 4  Navigation information block --\n");
	printf("header block number           : %d\n",header->nav->HeaderNum);
	printf("block length                  : %d\n",header->nav->BlockLen);
	printf("navigation information time   : %f\n",header->nav->navMjd);
	printf("SSP longitude                 : %f\n",header->nav->sspLon);
	printf("SSP latitude                  : %f\n",header->nav->sspLat);
	printf("distance from Earth's center to satellite\n");
	printf("                              : %f\n",header->nav->satDis);
	printf("nadir longitude               : %f\n",header->nav->nadirLon);
	printf("nadir latitude                : %f\n",header->nav->nadirLat);
	printf("Sun's position  (x)           : %f\n",header->nav->sunPos_x);
	printf("                (y)           : %f\n",header->nav->sunPos_y);
	printf("                (z)           : %f\n",header->nav->sunPos_z);
	printf("Moon's position (x)           : %f\n",header->nav->moonPos_x);
	printf("                (y)           : %f\n",header->nav->moonPos_y);
	printf("                (z)           : %f\n",header->nav->moonPos_z);
	printf("spare                         : %s\n",header->nav->spare);
	/* -5--------------------------------------------------------------------*/
	printf("\n");
	printf("# 5  Calibration information block -\n");
	printf("header block number           : %d\n",header->calib->HeaderNum);
	printf("block length                  : %d\n",header->calib->BlockLen);
	printf("band number                   : %d\n",header->calib->bandNo);
	printf("central wave length           : %f\n",header->calib->waveLen);
	printf("valid number of bits per pixel: %d\n",header->calib->bitPix);
	printf("count value of error pixels   : %d\n",header->calib->errorCount);
	printf("count value of pixels out of scan area : %d\n",header->calib->outCount);
	printf("count-radiance conversion equation\n");
	printf("   gain                       : %f\n",header->calib->gain_cnt2rad);
	printf("   constant                   : %f\n",header->calib->cnst_cnt2rad);
	/* MWIR/LWIR */
	if(	(header->calib->bandNo>=7 &&
		 strstr(header->basic->satName,"Himawari")!=NULL ) ||
		(header->calib->bandNo>=2 &&
		 strstr(header->basic->satName,"MTSAT-2") !=NULL )	){
	printf("correction coefficient of sensor Planck functions for converting\n");
	printf("radiance to brightness temperature\n");
	printf("                         (c0) : %f\n",header->calib->rad2btp_c0);
	printf("                         (c1) : %f\n",header->calib->rad2btp_c1);
	printf("                         (c2) : %f\n",header->calib->rad2btp_c2);
	printf("brightness temperature to radiance\n");
	printf("                         (c0) : %f\n",header->calib->btp2rad_c0);
	printf("                         (c1) : %f\n",header->calib->btp2rad_c1);
	printf("                         (c2) : %f\n",header->calib->btp2rad_c2);
	printf("light speed                   : %10.8e\n",header->calib->lightSpeed);
	printf("Planck's constant             : %10.8e\n",header->calib->planckConst);
	printf("Boltzmann constant            : %10.8e\n",header->calib->bolzConst);
	printf("spare                         : %s\n",header->calib->spare);
	/* VNIR */
	}else{
	printf("transformation coefficeint(c') from radiance(I) to albedo(A)\n");
	printf("transformation coefficeint(c'): %f\n",header->calib->rad2albedo);

	printf("modified calibration coefficient\n");
	printf("   modified time       : %f\n",header->calib->coeff_mjd);
	printf("   gain                : %f\n",header->calib->gain_cnt2rad_mod);
	printf("   constant            : %f\n",header->calib->cnst_cnt2rad_mod);

	}
	/* -6--------------------------------------------------------------------*/
	printf("\n");
	printf("# 6  Inter-calibration information block -\n");
	printf("header block number           : %d\n",header->interCalib->HeaderNum);
	printf("block length                  : %d\n",header->interCalib->BlockLen);
	version = atof(header->basic->verName);
	if(version >  1.1){
		/* for version 1.2 */
		printf("GSICS calibration coefficient)\n");
		printf("  coefficient (Intercept)     : %f\n",header->interCalib->gsicsCorr_C);
		printf("  coefficient (Slope)         : %f\n",header->interCalib->gsicsCorr_1);
		printf("  coefficient (Quadratic Term): %f\n",header->interCalib->gsicsCorr_2);
		printf("Radiance bias and its uncertainty\n");
		printf("  Radiance bias               : %f\n",header->interCalib->gsicsBias);
		printf("  Uncertainty                 : %f\n",header->interCalib->gsicsUncert);
		printf("  Radiance for standard scene : %f\n",header->interCalib->gsicsStscene);
		printf("start time of validity period : %f\n",header->interCalib->gsicsCorr_StrMJD);
		printf("end time of validity period   : %f\n",header->interCalib->gsicsCorr_EndMJD);
		printf("Radiance valid range of GSICS Calibration Coefficients\n");
		printf("  upper limit                 : %f\n",header->interCalib->gsicsUpperLimit);
		printf("  lower limit                 : %f\n",header->interCalib->gsicsLowerLimit);
		printf("File name of GSICS Correction : %s\n",header->interCalib->gsicsFilename);
		printf("spare                         : %s\n",header->interCalib->spare);
	}else if(version >  1.0){
		/* for version 1.1 */
		printf("GSICS calibration coefficient)\n");
		printf("  coefficient (Intercept)     : %f\n",header->interCalib->gsicsCorr_C);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_C_er);
		printf("  coefficient (Slope)         : %f\n",header->interCalib->gsicsCorr_1);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_1_er);
		printf("  coefficient (Quadratic Term): %f\n",header->interCalib->gsicsCorr_2);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_2_er);
		printf("start time of validity period : %f\n",header->interCalib->gsicsCorr_StrMJD);
		printf("end time of validity period   : %f\n",header->interCalib->gsicsCorr_EndMJD);
		printf("Radiance valid range of GSICS Calibration Coefficients\n");
		printf("  upper limit                 : %f\n",header->interCalib->gsicsUpperLimit);
		printf("  lower limit                 : %f\n",header->interCalib->gsicsLowerLimit);
		printf("File name of GSICS Correction : %s\n",header->interCalib->gsicsFilename);
		printf("spare                         : %s\n",header->interCalib->spare);
	}else{
		/* for version 1.0 and 0.0 */
		printf("GSICS calibration coefficient (Intercept)\n");
		printf("  coefficient (Intercept)     : %f\n",header->interCalib->gsicsCorr_C);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_C_er);
		printf("GSICS calibration coefficient (Slope)\n");
		printf("  coefficient (Slope)         : %f\n",header->interCalib->gsicsCorr_1);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_1_er);
		printf("GSICS calibration coefficient (Quadratic Term)\n");
		printf("  coefficient (Quadratic Term): %f\n",header->interCalib->gsicsCorr_2);
		printf("  standard error              : %f\n",header->interCalib->gsicsCorr_2_er);
		printf("start time of validity period : %f\n",header->interCalib->gsicsCorr_StrMJD);
		printf("end time of validity period   : %f\n",header->interCalib->gsicsCorr_EndMJD);
		printf("ancillary text                : %s\n",header->interCalib->gsicsCorrInfo);
		printf("spare                         : %s\n",header->interCalib->spare);
	}
	/* -7--------------------------------------------------------------------*/
	printf("\n");
	printf("# 7  Segment information block -----\n");
	printf("header block number           : %d\n",header->seg->HeaderNum);
	printf("block length                  : %d\n",header->seg->BlockLen);
	printf("total number of segments      : %d\n",header->seg->totalSegNum);
	printf("segment sequence number       : %d\n",header->seg->segSeqNo);
	printf("first line number of the image segment: %d\n",header->seg->strLineNo);
	printf("spare                         : %s\n",header->seg->spare);
	/* -8--------------------------------------------------------------------*/
	printf("\n");
	printf("# 8  Navigation correction information block -\n");
	printf("header block number           : %d\n",header->navcorr->HeaderNum);
	printf("block length                  : %d\n",header->navcorr->BlockLen);
	printf("center column of rotation     : %f\n",header->navcorr->RoCenterColumn);   
	printf("center line of rotation       : %f\n",header->navcorr->RoCenterLine);   
	printf("amount of rotational correction: %f\n",header->navcorr->RoCorrection);   
	printf("correction information for column and line direction\n");
	printf("number of correction information  : %d\n",header->navcorr->correctNum);   
	for(ii=0;ii<header->navcorr->correctNum;ii++){
		printf("line number after the rotation     : %d\n",
				header->navcorr->lineNo[ii]);
		printf("shift amount for column direction  : %f\n",
				header->navcorr->columnShift[ii]);
		printf("shift amount for line   direction  : %f\n",
				header->navcorr->lineShift[ii]);
	}
	printf("spare                         : %s\n",header->navcorr->spare);   
	/* -9--------------------------------------------------------------------*/
	printf("\n");
	printf("# 9  Observation information block -\n");
	printf("header block number           : %d\n",header->obstime->HeaderNum);
	printf("block length                  : %d\n",header->obstime->BlockLen);
	printf("number of observation time information : %d\n",header->obstime->obsNum);
	for(ii=0;ii<header->obstime->obsNum;ii++){
		printf("line number                        : %d\n",header->obstime->lineNo[ii]);
		printf("observation time (MJD)             : %f\n",header->obstime->obsMJD[ii]);
	}
	printf("spare                         : %s\n",header->obstime->spare);   
	/* 10--------------------------------------------------------------------*/
	printf("\n");
	printf("#10  Error information block -------\n");
	printf("header block number           : %d\n",header->error->HeaderNum);
	printf("block length                  : %d\n",header->error->BlockLen);
	printf("number of error information : %d\n",header->error->errorNum);
	for(ii=0;ii<header->error->errorNum;ii++){
		printf("line number                        : %d\n",header->error->lineNo[ii]);
		printf("number of error pixels per one line: %d\n",header->error->errPixNum[ii]); 
	}
	printf("spare                         : %s\n",header->error->spare);   
	/* 11--------------------------------------------------------------------*/
	printf("\n");
	printf("#11  Spare block -------------------\n");
	printf("header block number           : %d\n",header->spare->HeaderNum);
	printf("block length                  : %d\n",header->spare->BlockLen);
	printf("spare                         : %s\n",header->spare->spare);   
	/* ----------------------------------------------------------------------*/
	return(0);
}
