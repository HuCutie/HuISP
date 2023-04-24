#include "../include/wbc.h"

int main(int argc, char **argv)
{
	top_register topParam;
	wbc_register wbc_param;
	hls::stream<uint12> src;
	hls::stream<uint12> dst;
	int x;

	printf("\tTest for ISP wbc module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&wbc_param, 0, sizeof(wbc_register));
	topParam.frameWidth = 640;
	topParam.frameHeight = 480;
	topParam.imgPattern = 3;
	wbc_param.m_nEb = 1;

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

		wbc_param.m_nEb = 1;
		wbc_param.m_nR = 4821;
		wbc_param.m_nGr = 4096;
		wbc_param.m_nB = 6486;
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

				if (strstr(key, "wbc_enable"))
				{
					wbc_param.m_nEb = atoi(value);
					printf("wbc_enable = %d\n", int(wbc_param.m_nEb));
					continue;
				}

				if (strstr(key, "wbc_rgain"))
				{
					wbc_param.m_nR = atoi(value);
					printf("wbc_rgain = %d\n", int(wbc_param.m_nR));
					continue;
				}

				if (strstr(key, "wbc_ggain"))
				{
					wbc_param.m_nGr = atoi(value);
					wbc_param.m_nGb = atoi(value);
					printf("wbc_ggain = %d\n", int(wbc_param.m_nGr));
					continue;
				}

				if (strstr(key, "wbc_bgain"))
				{
					wbc_param.m_nB = atoi(value);
					printf("wbc_bgain = %d\n", int(wbc_param.m_nB));
					continue;
				}
			}
		}
	}

	uint16_t *frameIn = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	// uint16_t* frameGolden = (uint16_t*)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	uint16_t *frameOut = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));

	// In
	FILE *fp_r1 = fopen(WBC_SRC1, "r");
	if (!fp_r1)
	{
		printf("Can not input file!\n");
	}

	for (x = 0; x < topParam.frameWidth * topParam.frameHeight; x++)
	{
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		uint12 srcdata = (uint12)frameIn[x];
		src << srcdata;
	}
	printf("\tInit done!\n");

	// Golden
	//  FILE *fp_g1 = fopen(WBC_GOLDEN1, "r");
	//  if(!fp_g1){
	//      printf("Can not open golden file!\n");
	//  }

	// for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//     fread(&frameGolden[x], sizeof(uint16_t), 1, fp_g1);
	// }
	printf("\tEnvironment set up!\n");

	// Execution
	wbc(topParam, wbc_param, src, dst);
	printf("\tExecution completed!\n");

	// Out
	FILE *fp_w1 = fopen(WBC_DST1, "w");
	if (!fp_w1)
	{
		printf("\tCan not open write back file!\n");
	}

	for (x = 0; x < topParam.frameWidth * topParam.frameHeight; x++)
	{
		uint12 dstdata;
		dst >> dstdata;
		frameOut[x] = dstdata;
	}

	fwrite(frameOut, sizeof(uint16_t), (topParam.frameWidth * topParam.frameHeight), fp_w1);

	// Checker
	//  for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//      if(frameGolden[x] != frameOut[x]) {
	//          printf("\t\tFirst mismatch in pixel %d!\n", x);
	//          printf("\t\tGolden = %d, result = %d!\n", frameGolden[x], frameOut[x]);
	//          break;
	//      }
	//  }
	//  printf("\tTest passed!\n");

	fclose(fp_r1);
	// fclose(fp_g1);
	fclose(fp_w1);

	return 0;
}
