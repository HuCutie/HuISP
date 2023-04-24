#include "../include/dgain.h"

int main(int argc, char **argv)
{
	top_register topParam;
	dgain_register dgain_param;
	hls::stream<uint12> src;
	hls::stream<uint12> dst;
	int x;

	printf("\tTest for ISP dgain module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&dgain_param, 0, sizeof(dgain_register));

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

		dgain_param.m_nEb = 1;
		dgain_param.m_nR = 16384;
		dgain_param.m_nGr = 16384;
		dgain_param.m_nGb = 16384;
		dgain_param.m_nB = 16384;
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

				if (strstr(key, "dgain_enable"))
				{
					dgain_param.m_nEb = atoi(value);
					printf("dgain_enable = %d\n", dgain_param.m_nEb);
					continue;
				}

				if (strstr(key, "dgain_rgain"))
				{
					dgain_param.m_nR = atoi(value);
					printf("dgain_rgain = %d\n", int(dgain_param.m_nR));
					continue;
				}

				if (strstr(key, "dgain_grgain"))
				{
					dgain_param.m_nGr = atoi(value);
					printf("dgain_grgain = %d\n", int(dgain_param.m_nGr));
					continue;
				}

				if (strstr(key, "dgain_gbgain"))
				{
					dgain_param.m_nGb = atoi(value);
					printf("dgain_gbgain = %d\n", int(dgain_param.m_nGb));
					continue;
				}

				if (strstr(key, "dgain_bgain"))
				{
					dgain_param.m_nB = atoi(value);
					printf("dgain_bdgain = %d\n", int(dgain_param.m_nB));
					continue;
				}
			}
		}
	}

	uint16_t *frameIn = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	// uint16_t *frameGolden = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	uint16_t *frameOut = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));

	// In
	FILE *fp_r1 = fopen(Dgain_SRC1, "r");
	if (!fp_r1)
	{
		printf("Can not open input file!\n");
	}

	for (x = 0; x < topParam.frameWidth * topParam.frameHeight; x++)
	{
		fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
		uint12 srcdata = (uint12)frameIn[x];
		src << srcdata;
	}
	printf("\tInit done!\n");

	// Golden
	//  FILE *fp_g1 = fopen(Dgain_GOLDEN1, "r");
	//  if(!fp_g1){
	//      printf("Can not open golden file!\n");
	//  }

	// for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//     fread(&frameGolden[x], sizeof(uint16_t), 1, fp_g1);
	// }
	// printf("\tEnvironment set up!\n");

	// Execution
	dgain(topParam, dgain_param, src, dst);
	printf("\tExecution completed!\n");

	// Out
	FILE *fp_w1 = fopen(Dgain_DST1, "w");
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