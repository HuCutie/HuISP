src = ../src/

tpg:
	g++ tpg.cpp $(src)tpg.cpp -o tpg
dgain:
	g++ dgain.cpp $(src)dgain.cpp -o dgain
lsc:
	g++ lsc.cpp $(src)lsc.cpp -o lsc
dpc:
	g++ dpc.cpp $(src)dpc.cpp -o dpc
rawdns:
	g++ rawdns.cpp $(src)rawdns.cpp -o rawdns
awb:
	g++ awb.cpp $(src)awb.cpp -o awb
wbc:
	g++ wbc.cpp $(src)wbc.cpp -o wbc
gb:
	g++ gb.cpp $(src)gb.cpp -o gb
demosaic:
	g++ demosaic.cpp $(src)demosaic.cpp -o demosaic
ee:
	g++ ee.cpp $(src)ee.cpp -o ee
cmc:
	g++ cmc.cpp $(src)cmc.cpp -o cmc
aec:
	g++ aec.cpp $(src)aec.cpp -o aec
gtm:
	g++ gtm.cpp $(src)gtm.cpp -o gtm
ltm:
	g++ ltm.cpp $(src)ltm.cpp -o ltm
cac:
	g++ cac.cpp $(src)cac.cpp -o cac


csc:
	g++ csc.cpp $(src)csc.cpp -o csc
yfc:
	g++ yfc.cpp $(src)yfc.cpp -o yfc
yuvdns:
	g++ yuvdns.cpp $(src)yuvdns.cpp -o yuvdns
scaledown:
	g++ scaledown.cpp $(src)scaledown.cpp -o scaledown
crop:
	g++ crop.cpp $(src)crop.cpp -o crop

afc:
	g++ afc.cpp $(src)afc.cpp -o afc
lut:
	g++ lut.cpp $(src)lut.cpp -o lut
sde:
	g++ sde.cpp $(src)sde.cpp -o sde

top:
	g++ top.cpp $(src)*.cpp -o top

all: tpg dgain lsc dpc rawdns awb wbc gb demosaic ee cmc gtm ltm cac csc yfc yuvdns scaledown crop

isp: tpg dgain lsc dpc rawdns awb wbc gb demosaic ee cmc gtm ltm cac

clean:
	rm tpg dgain lsc dpc rawdns awb wbc gb demosaic ee cmc gtm ltm cac isp top