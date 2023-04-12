# ISP C++
## 项目结构
```
|-- config
|   `-- ISP.cfg                          全局配置文件，自定义每个ISP模块的参数
|-- include                              全局头文件，主要包含结构体定义
|   |-- ac_channel.h
|   |-- ac_int.h
|   |-- afc.h
|   |-- awb.h
|   |-- cac.h
|   |-- cmc.h
|   |-- crop.h
|   |-- csc.h
|   |-- demosaic.h
|   |-- dgain.h
|   |-- dpc.h
|   |-- ee.h
|   |-- file_define.h
|   |-- gb.h
|   |-- gtm.h
|   |-- isp_top.h
|   |-- lsc.h
|   |-- ltm.h
|   |-- lut.h
|   |-- rawdns.h
|   |-- scaledown.h
|   |-- sde.h
|   |-- top.h
|   |-- tpg.h
|   |-- wbc.h
|   |-- yfc.h
|   `-- yuvdns.h
|-- input                                  输入文件以及产生的中间文件
|   `-- input.raw
|-- src                                     源文件，包含模块的实现
|   |-- afc.cpp
|   |-- awb.cpp
|   |-- cac.cpp
|   |-- cmc.cpp
|   |-- crop.cpp
|   |-- csc.cpp
|   |-- demosaic.cpp
|   |-- dgain.cpp
|   |-- dpc.cpp
|   |-- ee.cpp
|   |-- gb.cpp
|   |-- gtm.cpp
|   |-- isp_top.cpp
|   |-- lsc.cpp
|   |-- ltm.cpp
|   |-- lut.cpp
|   |-- rawdns.cpp
|   |-- scaledown.cpp
|   |-- sde.cpp
|   |-- tpg.cpp
|   |-- wbc.cpp
|   |-- yfc.cpp
|   `-- yuvdns.cpp
|-- test                                    单模块测试文件
|   |-- Makefile 
|   |-- afc
|   |-- afc.cpp
|   |-- cac.cpp
|   |-- cmc.cpp
|   |-- crop.cpp
|   |-- csc.cpp
|   |-- demosaic.cpp
|   |-- dgain.cpp
|   |-- dpc.cpp
|   |-- ee.cpp
|   |-- gb.cpp
|   |-- gtm.cpp
|   |-- isp_top.cpp
|   |-- lsc.cpp
|   |-- ltm.cpp
|   |-- lut.cpp
|   |-- rawdns.cpp
|   |-- scaledown.cpp
|   |-- sde.cpp
|   |-- tpg.cpp
|   |-- wbc.cpp
|   |-- yfc.cpp
|   `-- yuvdns.cpp
```
5 directories, 78 files
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
执行`make top`可产生isp的可执行文件，进行所有流程的测试。  
执行顺序：  
 0. input
 1. tgp
 2. dgain
 3. lsc
 4. dpc
 5. rawdns
 6. awb
 7. wb
 8. gb
 9. dmc
 10. ee
 11. cmc
 12. gtm
 13. ltm
 14. cac