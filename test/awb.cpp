#include "../include/awb.h"

int main(int argc, char **argv)
{
	top_register topParam;
	awb_register awb_param;
	hls::stream<uint12> src("in");
	hls::stream<uint12> dst("out");
	int x;

	printf("\tTest for ISP awb module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&awb_param, 0, sizeof(awb_register));

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

		awb_param.m_nEb = 1;
		awb_param.coeff = 1;
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

				if (strstr(key, "awb_enable"))
				{
					awb_param.m_nEb = atoi(value);
					printf("awb_enable = %d\n", int(awb_param.m_nEb));
					continue;
				}

				if (strstr(key, "awb_coeff"))
				{
					awb_param.coeff = atoi(value);
					printf("awb_coeff = %d\n", int(awb_param.coeff));
					continue;
				}
			}
		}
	}

	uint16_t *frameIn = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	uint16_t *frameOut = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));

	// In
	FILE *fp_r1 = fopen(AWB_SRC1, "r");
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

	// Execution
	awb(topParam, awb_param, src, dst);
	printf("\tExecution completed!\n");

	// Out
	FILE *fp_w1 = fopen(AWB_DST1, "w");
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
	//      if(frameIn[x] != frameOut[x]) {
	//          printf("\t\tFirst mismatch in pixel %d!\n", x);
	//          printf("\t\tGolden = %d, result = %d!\n", frameIn[x], frameOut[x]);
	//          break;
	//      }
	//  }
	//  printf("\tTest passed!\n");

	// cout << "c_r_gain = " << 4821 << endl;
	// cout << "c_g_gain = " << 4096  << endl;
	// cout << "c_b_gain = " << 6486 << endl;
	cout << "r_gain = " << awb_param.r_gain << endl;
	cout << "g_gain = " << awb_param.g_gain << endl;
	cout << "b_gain = " << awb_param.b_gain << endl;

	fclose(fp_r1);
	fclose(fp_w1);

	return 0;
}
