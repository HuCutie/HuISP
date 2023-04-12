#include "../include/cmc.h"

int main(int argc, char **argv)
{
	top_register topParam;
	cmc_register cmc_param;
	hls::stream<uint36> src;
	hls::stream<uint42> dst;
	int x;
	uint12 red;
	uint12 green;
	uint12 blue;
	uint14 red_o;
	uint14 green_o;
	uint14 blue_o;
	uint36 srcdata;
	uint42 dstdata;

	printf("\tTest for ISP cmc module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&cmc_param, 0, sizeof(cmc_register));	

	const char *config_file = "../config/ISP.cfg";

	char buf[100] = "";
	FILE *fp_config = fopen((const char *)config_file, "r");
	char *p, *q;
	char key[100], value[100];

	if (fp_config == NULL)
	{
		printf("\t Warning: no configuration file!\n");
		printf("\t Will use default initial values!\n");
		topParam.frameWidth = 640;
		topParam.frameHeight = 480;
		topParam.imgPattern = 3;
		topParam.blc = 0;

		cmc_param.m_nEb = 1;
		cmc_param.m_bDiscardH = 0;
		cmc_param.m_nGain[0] = 6709;
		cmc_param.m_nGain[1] = -2591;
		cmc_param.m_nGain[2] = -22;
		cmc_param.m_nGain[3] = 0;
		cmc_param.m_nGain[4] = -632;
		cmc_param.m_nGain[5] = 5336;
		cmc_param.m_nGain[6] = -607;
		cmc_param.m_nGain[7] = 0;
		cmc_param.m_nGain[8] = 156;
		cmc_param.m_nGain[9] = -2970;
		cmc_param.m_nGain[10] = 6912;
		cmc_param.m_nGain[11] = 0;
	}
	else
	{
		while (fgets(buf, 100, fp_config))
		{
			p = strchr(buf, '=');
			q = strchr(buf, '\n');
			if (p != NULL && q != NULL)
			{
				*q = '\0';
				strncpy(key, buf, p - buf);
				strcpy(value, p + 1);

				if (strstr(key, "frame_width"))
				{
					topParam.frameWidth = atoi(value);
					printf("frame_width = %d\n", int(topParam.frameWidth));
					continue;
				}

				if (strstr(key, "frame_height"))
				{
					topParam.frameHeight = atoi(value);
					printf("frame_height = %d\n", int(topParam.frameHeight));
					continue;
				}

				if (strstr(key, "image_pattern"))
				{
					topParam.imgPattern = atoi(value);
					printf("image_pattern = %d\n", int(topParam.imgPattern));
					continue;
				}

				if (strstr(key, "blc"))
				{
					topParam.blc = atoi(value);
					printf("blc = %d\n", int(topParam.blc));
					continue;
				}

				if(strstr(key, "cmc_enable"))
                {
                    cmc_param.m_nEb = atoi(value);
                    printf("cmc_enable = %d\n", cmc_param.m_nEb);
                    continue;
                }

				if(strstr(key, "cmc_DiscardH"))
                {
                    cmc_param.m_bDiscardH = atoi(value);
                    printf("cmc_DiscardH = %d\n", cmc_param.m_bDiscardH);
                    continue;
                }

				if(strstr(key, "cmc_gain_0"))
                {
                    cmc_param.m_nGain[0] = atoi(value);
                    printf("cmc_gain_0 = %d\n", int(cmc_param.m_nGain[0]));
                    continue;
                }
				if(strstr(key, "cmc_gain_1"))
                {
                    cmc_param.m_nGain[1] = atoi(value);
                    printf("cmc_gain_1 = %d\n", int(cmc_param.m_nGain[1]));
                    continue;
                }
				if(strstr(key, "cmc_gain_2"))
                {
                    cmc_param.m_nGain[2] = atoi(value);
                    printf("cmc_gain_2 = %d\n", int(cmc_param.m_nGain[2]));
                    continue;
                }
				if(strstr(key, "cmc_gain_3"))
                {
                    cmc_param.m_nGain[3] = atoi(value);
                    printf("cmc_gain_3 = %d\n", int(cmc_param.m_nGain[3]));
                    continue;
                }
				if(strstr(key, "cmc_gain_4"))
                {
                    cmc_param.m_nGain[4] = atoi(value);
                    printf("cmc_gain_4 = %d\n", int(cmc_param.m_nGain[4]));
                    continue;
                }
				if(strstr(key, "cmc_gain_5"))
                {
                    cmc_param.m_nGain[5] = atoi(value);
                    printf("cmc_gain_5 = %d\n", int(cmc_param.m_nGain[5]));
                    continue;
                }
				if(strstr(key, "cmc_gain_6"))
                {
                    cmc_param.m_nGain[6] = atoi(value);
                    printf("cmc_gain_6 = %d\n", int(cmc_param.m_nGain[6]));
                    continue;
                }
				if(strstr(key, "cmc_gain_7"))
                {
                    cmc_param.m_nGain[7] = atoi(value);
                    printf("cmc_gain_7 = %d\n", int(cmc_param.m_nGain[7]));
                    continue;
                }
				if(strstr(key, "cmc_gain_8"))
                {
                    cmc_param.m_nGain[8] = atoi(value);
                    printf("cmc_gain_8 = %d\n", int(cmc_param.m_nGain[8]));
                    continue;
                }
				if(strstr(key, "cmc_gain_9"))
                {
                    cmc_param.m_nGain[9] = atoi(value);
                    printf("cmc_gain_9 = %d\n", int(cmc_param.m_nGain[9]));
                    continue;
                }
				if(strstr(key, "cmc_gain_ten"))
                {
                    cmc_param.m_nGain[10] = atoi(value);
                    printf("cmc_gain_10= %d\n", int(cmc_param.m_nGain[10]));
                    continue;
                }
				if(strstr(key, "cmc_gain_eleven"))
                {
                    cmc_param.m_nGain[11] = atoi(value);
                    printf("cmc_gain_11= %d\n", int(cmc_param.m_nGain[11]));
                    continue;
                }
			}
		}
	}

	uint16_t *frameIn = (uint16_t *)malloc(4 * topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	// uint16_t* frameGolden = (uint16_t*)malloc(3 * topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	uint16_t *frameOut = (uint16_t *)malloc(3 * topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));

	// In
	FILE *fp_r1 = fopen(CMC_SRC1, "r");
	if (!fp_r1)
	{
		printf("Can not open input file!\n");
	}

	for (x = 0; x < topParam.frameWidth * topParam.frameHeight; x++)
	{
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		red = (uint12)frameIn[x];
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		green = (uint12)frameIn[x];
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		blue = (uint12)frameIn[x];
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		srcdata(35, 24) = red;
		srcdata(23, 12) = green;
		srcdata(11, 0) = blue;
		src.write(srcdata);
	}
	printf("\tInit done!\n");

	// Golden
	//  FILE *fp_g1 = fopen(CMC_GOLDEN1, "r");
	//  if(!fp_g1){
	//      printf("Can not open golden file!\n");
	//  }

	// for (x = 0; x < 3*topParam.frameWidth*topParam.frameHeight; x++) {
	//     fread(&frameGolden[x], sizeof(uint16_t), 1, fp_g1);
	// }
	printf("\tEnvironment set up!\n");

	// Execution
	cmc(topParam, cmc_param, src, dst);
	printf("\tExecution completed!\n");
	printf("\t%d\n", int(dst.size()));

	// Out
	FILE *fp_w1 = fopen(CMC_DST1, "w");
	if (!fp_w1)
	{
		printf("\tCan not open write back file!\n");
	}

	for (x = 0; x < topParam.frameWidth * topParam.frameHeight; x++)
	{
		dstdata = dst.read();
		red_o = dstdata >> 28;
		green_o = (dstdata >> 14) & 0x3fff;
		blue_o = dstdata & 0x3fff;
		frameOut[3 * x] = red_o;
		frameOut[3 * x + 1] = green_o;
		frameOut[3 * x + 2] = blue_o;
	}

	fwrite(frameOut, sizeof(uint16_t), (3 * topParam.frameWidth * topParam.frameHeight), fp_w1);

	// Checker
	//  for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//      if(frameGolden[x] != frameOut[x]) {
	//          printf("\t\tFirst mismatch in pixel %d, channel %d!\n", x/3, x%3);
	//          cout << "Golden = " << setbase(16) << frameGolden[x] << endl;
	//          cout << "result = " << setbase(16) << frameOut[x] << endl;
	//          break;
	//      }
	//  }
	//  printf("\tTest passed!\n");

	fclose(fp_r1);
	// fclose(fp_g1);
	fclose(fp_w1);

	return 0;
}
