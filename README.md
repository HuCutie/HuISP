# ISP C++
## 项目结构
```
|-- README.md
|-- config
|   `-- ISP.cfg
|-- include
|   |-- aec.h
|   |-- afc.h
|   |-- ap_common.h
|   |-- ap_decl.h
|   |-- ap_fixed.h
|   |-- ap_fixed_base.h
|   |-- ap_fixed_ref.h
|   |-- ap_fixed_special.h
|   |-- ap_int.h
|   |-- ap_int_base.h
|   |-- ap_int_ref.h
|   |-- ap_int_special.h
|   |-- awb.h
|   |-- cac.h
|   |-- cmc.h
|   |-- crop.h
|   |-- csc.h
|   |-- dehaze.h
|   |-- demosaic.h
|   |-- dgain.h
|   |-- dpc.h
|   |-- ee.h
|   |-- etc
|   |   `-- ap_private.h
|   |-- file_define.h
|   |-- gb.h
|   |-- gtm.h
|   |-- hls_stream.h
|   |-- isp_top.h
|   |-- lsc.h
|   |-- ltm.h
|   |-- lut.h
|   |-- rawdns.h
|   |-- scaledown.h
|   |-- tnr.h
|   |-- top.h
|   |-- tpg.h
|   |-- wbc.h
|   |-- yfc.h
|   `-- yuvdns.h
|-- input
|   `-- input.raw
|-- src
|   |-- aec.cpp
|   |-- afc.cpp
|   |-- awb.cpp
|   |-- cac.cpp
|   |-- cmc.cpp
|   |-- crop.cpp
|   |-- csc.cpp
|   |-- dehaze.cpp
|   |-- demosaic.cpp
|   |-- dgain.cpp
|   |-- dpc.cpp
|   |-- ee.cpp
|   |-- gb.cpp
|   |-- gtm.cpp
|   |-- lsc.cpp
|   |-- ltm.cpp
|   |-- lut.cpp
|   |-- rawdns.cpp
|   |-- scaledown.cpp
|   |-- sde.cpp
|   |-- tnr.cpp
|   |-- tpg.cpp
|   |-- wbc.cpp
|   |-- yfc.cpp
|   `-- yuvdns.cpp
`-- test
    |-- Makefile
    |-- aec.cpp
    |-- afc.cpp
    |-- awb.cpp
    |-- cac.cpp
    |-- cmc.cpp
    |-- crop.cpp
    |-- csc.cpp
    |-- dehaze.cpp
    |-- demosaic.cpp
    |-- dgain.cpp
    |-- dpc.cpp
    |-- ee.cpp
    |-- gb.cpp
    |-- gtm.cpp
    |-- lsc.cpp
    |-- ltm.cpp
    |-- lut.cpp
    |-- rawdns.cpp
    |-- scaledown.cpp
    |-- top.cpp
    |-- tpg.cpp
    |-- wbc.cpp
    |-- yfc.cpp
    `-- yuvdns.cpp
```

6 directories, 92 files
## 参数解释
1. Bayer阵列排布方式  
   这里使用2bit数据来表示：  
   0-RGGB  
   1-GRGB  
   2-BGGR  
   3-
2. 每个流程中都会包括一个GOLDEN文件的读取，目前不知道是为了什么
## 运行说明
进入test文件夹后执行`make` + 模块名即可生成指定模块的可执行测试文件，接受上个模块的输入，并产生本模块的输出。  
执行`make isp`可产生isp的可执行文件，进行所有流程的测试。  
执行顺序(1-8是在raw格式下进行，8-14是在rgb格式下进行)：  
 1. tgp
 2. dgain
 3. lsc
 4. dpc
 5. rawdns
 6. awb
 7. wbc
 8. gb
 9. demosaic
 10. ee
 11. cmc
 12. gtm
 13. ltm
 14. cac