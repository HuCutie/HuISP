#include "../include/gb.h"

int main(int argc, char **argv)
{
	top_register topParam;
	gb_register gb_param;
	hls::stream<uint12> src("input_stream");
	hls::stream<uint12> dst("output_stream");
	int x;

	printf("\tTest for ISP greenbalance module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&gb_param, 0, sizeof(gb_register));

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

		gb_param.eb = 1;
		gb_param.win_size = 7;
		gb_param.Lbound = 4;
		gb_param.Hbound = 20;
		gb_param.threhold = 683;
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

				if (strstr(key, "gb_enable"))
				{
					gb_param.eb = atoi(value);
					printf("gb_enable = %d\n", int(gb_param.eb));
					continue;
				}

				if (strstr(key, "gb_win_size"))
				{
					gb_param.win_size = atoi(value);
					printf("gb_win_size = %d\n", int(gb_param.win_size));
					continue;
				}

				if (strstr(key, "gb_Lbound"))
				{
					gb_param.Lbound = atoi(value);
					printf("gb_Lbound = %d\n", int(gb_param.Lbound));
					continue;
				}

				if (strstr(key, "gb_Hbound"))
				{
					gb_param.Hbound = atoi(value);
					printf("gb_Hbound = %d\n", int(gb_param.Hbound));
					continue;
				}

				if (strstr(key, "gb_threhold"))
				{
					gb_param.threhold = atoi(value);
					printf("gb_threhold = %d\n", int(gb_param.threhold));
					continue;
				}
			}
		}
	}

	uint16_t *frameIn = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	// uint16_t* frameGolden = (uint16_t*)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
	uint16_t *frameOut = (uint16_t *)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));

	// In
	FILE *fp_r1 = fopen(GB_SRC1, "r");
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
	//  FILE *fp_g1 = fopen(GB_GOLDEN1, "r");
	//  if(!fp_g1){
	//      printf("Can not open golden file!\n");
	//  }

	// for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//     fread(&frameGolden[x], sizeof(uint16_t), 1, fp_g1);
	// }
	printf("\tEnvironment set up!\n");

	// Execution
	greenbalance2(topParam, gb_param, src, dst);
	printf("\tExecution completed!\n");

	// Out
	FILE *fp_w1 = fopen(GB_DST1, "w");
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
	//   for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
	//       if(frameGolden[x] != frameOut[x]) {
	//           printf("\t\tFirst mismatch in pixel %d!\n", x);
	//           printf("\t\tGolden = %d, result = %d!\n", frameGolden[x], frameOut[x]);
	//           break;
	//       }
	//   }
	//   printf("\tTest passed!\n");

	fclose(fp_r1);
	// fclose(fp_g1);
	fclose(fp_w1);

	return 0;
}
