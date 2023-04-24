src = ../src/

tpg:
	g++ -pg tpg.cpp $(src)tpg.cpp -o tpg
dgain:
	g++ -pg dgain.cpp $(src)dgain.cpp -o dgain
lsc:
	g++ -pg lsc.cpp $(src)lsc.cpp -o lsc
dpc:
	g++ -pg dpc.cpp $(src)dpc.cpp -o dpc
rawdns:
	g++ -pg rawdns.cpp $(src)rawdns.cpp -o rawdns
awb:
	g++ -pg awb.cpp $(src)awb.cpp -o awb
wbc:
	g++ -pg wbc.cpp $(src)wbc.cpp -o wbc
gb:
	g++ -pg gb.cpp $(src)gb.cpp -o gb
demosaic:
	g++ -pg demosaic.cpp $(src)demosaic.cpp -o demosaic
ee:
	g++ -pg ee.cpp $(src)ee.cpp -o ee
cmc:
	g++ -pg cmc.cpp $(src)cmc.cpp -o cmc
aec:
	g++ -pg aec.cpp $(src)aec.cpp -o aec
gtm:
	g++ -pg gtm.cpp $(src)gtm.cpp -o gtm
ltm:
	g++ -pg ltm.cpp $(src)ltm.cpp -o ltm
cac:
	g++ -pg cac.cpp $(src)cac.cpp -o cac


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
	rm tpg dgain lsc dpc rawdns awb wbc gb demosaic ee cmc gtm ltm cac isp