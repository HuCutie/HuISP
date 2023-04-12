#include "../include/demosaic.h"

int main(int argc, char** argv)
{
    top_register topParam;
    demosaic_register demosaic_param;
    hls::stream<uint12> src;
    hls::stream<uint36> dst;
    int x;
    uint64_t red;
    uint64_t green;
    uint64_t blue;

    printf("\tTest for ISP demosaic module!\n");
    memset(&topParam, 0, sizeof(top_register));
    memset(&demosaic_param, 0, sizeof(demosaic_register));
    topParam.frameWidth = 1920;
    topParam.frameHeight = 1080;
    demosaic_param.eb = 1;

    uint16_t* frameIn = (uint16_t*)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint16_t));
    uint64_t* frameGolden = (uint64_t*)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint64_t));
    uint64_t* frameOut = (uint64_t*)malloc(topParam.frameWidth * topParam.frameHeight * sizeof(uint64_t));

    topParam.frameWidth = 640;
    topParam.frameHeight = 480;
    topParam.imgPattern = 3;

    //In
    FILE *fp_r1 = fopen(DEMOSAIC_SRC1, "r");
    if(!fp_r1){
        printf("Can not open input file!\n");
    }

    for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
        fread(&frameIn[x], sizeof(uint16_t), 1, fp_r1);
        uint12 srcdata = (uint12)frameIn[x];
        src << srcdata;
    }
    printf("\tInit done!\n");

    //Golden
    // FILE *fp_g1 = fopen(DEMOSAIC_GOLDEN1, "r");
    // if(!fp_g1){
    //     printf("Can not open golden file!\n");
    // }

    // for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
    //     fread(&frameGolden[x], sizeof(uint64_t), 1, fp_g1);
    // }
    printf("\tEnvironment set up!\n");

    //Execution
    demosaic(topParam, demosaic_param, src, dst);
    printf("\tExecution completed!\n");
    printf("\t%d\n",int(dst.size()));

    //Out
    FILE *fp_w1 = fopen(DEMOSAIC_DST1, "w");
    if(!fp_w1){
        printf("\tCan not open write back file!\n");
    }

    for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
        uint36 dstdata;
        dstdata = dst.read();
        red = dstdata >> 24;
        green = (dstdata >> 12) & 0xfff;
        blue = dstdata & 0xfff;
        //printf("%#16x\n",dstdata.to_long());
        //printf("%#2x\n%#2x\n%#2x\n",red,green,blue);
        uint64_t temp;
        temp = red | (green << 16) | (blue << 32);
        frameOut[x] = temp;
        //cout << setbase(16) << frameOut[x] << endl;
        //cout << setbase(16) << temp << endl;
    }

    fwrite(frameOut, sizeof(uint64_t), (topParam.frameWidth * topParam.frameHeight), fp_w1);

    //Checker
    for (x = 0; x < topParam.frameWidth*topParam.frameHeight; x++) {
        if(frameGolden[x] != frameOut[x]) {
            printf("\t\tFirst mismatch in pixel %d!\n", x);
            cout << "Golden = " << setbase(16) << frameGolden[x] << endl;
            cout << "result = " << setbase(16) << frameOut[x] << endl;
            break;
        }
    }
    printf("\tTest passed!\n");

    fclose(fp_r1);
    // fclose(fp_g1);
    fclose(fp_w1);

    return 0;
}

