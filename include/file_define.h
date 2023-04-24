//TPG
#define TPG_SRC1 "../input/input.raw"
#define TPG_DST1 "../input/tpg_out.raw"
//Dgain
#define Dgain_SRC1 "../input/input.raw"
#define Dgain_DST1 "../input/dgain_out.raw"
//LSC
#define LSC_SRC1 "../input/dgain_out.raw"
#define LSC_DST1 "../input/lsc_out.raw"
//DPC
#define DPC_SRC1 "../input/lsc_out.raw"
#define DPC_DST1 "../input/dpc_out.raw"
//RAWDNS
#define RAWDNS_SRC1 "../input/dpc_out.raw"
#define RAWDNS_DST1 "../input/rawdns_out.raw"
//AWB
#define AWB_SRC1 "../input/rawdns_out.raw"
#define AWB_DST1 "../input/rawdns_out.raw"
//WBC
#define WBC_SRC1 "../input/rawdns_out.raw"
#define WBC_DST1 "../input/wbc_out.raw"
//GB
#define GB_SRC1 "../input/wbc_out.raw"
#define GB_DST1 "../input/gb_out.raw"
//Demosaic
#define DEMOSAIC_SRC1 "../input/gb_out.raw"
#define DEMOSAIC_DST1 "../input/demosaic_out.rgbh"
//EE
#define EE_SRC "../input/demosaic_out.rgbh"
#define EE_DST "../input/ee_out.rgbh"
//Hist
//Histeq
//CMC
#define CMC_SRC1 "../input/ee_out.rgbh"
#define CMC_DST1 "../input/cmc_out.rgb"
//AEC
#define AEC_SRC1 "../input/cmc_out.rgb"
#define AEC_DST1 "../input/aec_out.rgb"
//GTM
#define GTM_SRC1 "../input/cmc_out.rgb"
#define GTM_DST1 "../input/gtm_out.rgb"
//LUT
#define LUT_SRC1 "../input/gtm_out.rgb"
#define LUT_DST1 "../input/lut_out.rgb"
#define LUT_CUBE "../input/integer.cube"
#define LUT_CUBE_17 "../input/integer_17.cube"
//LTM
#define LTM_SRC1    "../input/gtm_out.rgb"
#define LTM_DST1    "../input/ltm_out.rgb"
//DEHAZE
#define DEHAZE_SRC1    "../input/gtm_out.rgb"
#define DEHAZE_DST1    "../input/dehaze_out.rgb"
//CAC
#define CAC_SRC1 "../input/ltm_out.rgb"
#define CAC_DST1 "../input/cac_out.rgb"
//CSC
#define CSC_SRC1 "../input/cac_out.rgb"
#define CSC_DST1 "../input/csc_out.rgb"
//YFC
#define YFC_SRC "../input/csc_out.rgb"
#define YFC_DST1 "../input/yfc_out_444.yuv"
#define YFC_DST2 "../input/yfc_out_422.yuv"
#define YFC_DST3 "../input/yfc_out_420.yuv"
//YUVDNS
#define YUVDNS_SRC1 "../input/yfc_out_444.yuv"
#define YUVDNS_DST1 "../input/yuvdns_out_60_80.yuv"
//Scale down
#define scaledown_SRC1 "../input/yuvdns_out_60_80.yuv"
#define scaledown_DST1 "../input/scaledown_out.yuv"
//Crop
#define CROP_SRC1 "../input/scaledown_out.yuv"
#define CROP_DST1 "../input/crop_out.yuv"