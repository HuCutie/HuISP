#include "../include/rawdns.h"

int main(int argc, char *argv[])
{
	top_register topParam;
	rawdns_register rawdnsParam;

	hls::stream<uint12> src("input stream");
	hls::stream<uint12> dst("output stream");

	printf("\tTest for ISP rawdns module!\n");
	memset(&topParam, 0, sizeof(top_register));
	memset(&rawdnsParam, 0, sizeof(rawdns_register));

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

		rawdnsParam.eb = 1;
		rawdnsParam.sigma = 30;
		rawdnsParam.Filterpara = 50;
		rawdnsParam.invksigma2 = 12;
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

				if (strstr(key, "rawdns_enable"))
				{
					rawdnsParam.eb = atoi(value);
					printf("rawdns_enable = %d\n", int(rawdnsParam.eb));
					continue;
				}

				if (strstr(key, "rawdns_sigma"))
				{
					rawdnsParam.sigma = atoi(value);
					printf("rawdns_sigma = %d\n", int(rawdnsParam.sigma));
					continue;
				}

				if (strstr(key, "rawdns_filter"))
				{
					rawdnsParam.Filterpara = atoi(value);
					printf("rawdns_filter = %d\n", int(rawdnsParam.Filterpara));
					continue;
				}

				if (strstr(key, "rawdns_bitwidth"))
				{
					uint5 bitwidth = atoi(value);
					printf("rawdns_bitwidth = %d\n", int(bitwidth));
					rawdnsParam.invksigma2 = 4096 * 256 / (rawdnsParam.Filterpara * rawdnsParam.sigma) * (65536 >> ((bitwidth - 8) * 2)) / (rawdnsParam.Filterpara * rawdnsParam.sigma);
					printf("rawdnsParam.invksigma2 = %d\n", int(rawdnsParam.invksigma2));
					continue;
				}
			}
		}
	}

	uint16_t *frame_in = (uint16_t *)malloc(sizeof(uint16_t) * topParam.frameWidth * topParam.frameHeight);
	// uint16_t* golden_in = (uint16_t*)malloc(sizeof(uint16_t) * topParam.frameWidth * topParam.frameHeight);
	uint16_t *frame_out = (uint16_t *)malloc(sizeof(uint16_t) * topParam.frameWidth * topParam.frameHeight);

	uint12 src_in;
	uint12 dst_out;

	FILE *fp4 = fopen(RAWDNS_SRC1, "r");
	if (fp4 == NULL)
	{
		printf("SRC file open failed!\n");
		return false;
	}

	for (int i = 0; i < topParam.frameWidth * topParam.frameHeight; i++)
	{
		fread(&frame_in[i], sizeof(uint16_t), 1, fp4);
		src_in = (uint12)frame_in[i];
		src << src_in;
	}
	fclose(fp4);

	// read ref in and store in heap golden in
	//  FILE* fp5 = fopen(RAWDNS_GOLDEN1, "r");
	//  if (fp5 == NULL)
	//  {
	//      printf("GOLDEN file open failed!\n");
	//      return false;
	//  }

	// for (int i = 0; i < topParam.frameWidth * topParam.frameHeight; i++) {
	//     fread(&golden_in[i], sizeof(uint16_t), 1, fp5);
	// }
	// fclose(fp5);

	// execution and write out
	isp_rawdns(topParam, rawdnsParam, src, dst);

	FILE *fp6 = fopen(RAWDNS_DST1, "w");
	if (fp6 == NULL)
	{
		printf("DST file open failed!\n");
		return false;
	}

	for (int i = 0; i < topParam.frameWidth * topParam.frameHeight; i++)
	{
		dst >> dst_out;
		frame_out[i] = dst_out;
	}

	fwrite(frame_out, sizeof(uint16_t), topParam.frameWidth * topParam.frameHeight, fp6);
	fclose(fp6);

	// Compare and print results
	//  for (int i = 0; i < topParam.frameWidth * topParam.frameHeight; i++) {
	//      uint16_t golden_pixel = golden_in[i];
	//      uint16_t dst_pixel = frame_out[i];

	//     if (golden_pixel != dst_pixel)
	//     {
	//         cout << "Golden = " << setbase(10) << golden_in[i] << endl;
	//         cout << "result = " << setbase(10) << frame_out[i] << endl;
	//         printf("\t i=%d, \trows=%d,\tcols=%d\n", i, i / topParam.frameWidth.to_int(), i - (i / topParam.frameWidth.to_int()) * topParam.frameWidth.to_int());
	//         break;
	//     }
	// }

	// printf("Test Passed !\n");
	printf("Total pixel number is %d\n", topParam.frameWidth.to_int() * topParam.frameHeight.to_int());
	// printf("640x480 Verification finished!\n");

	free(frame_in);
	// free(golden_in);
	free(frame_out);
	return 0;
}
