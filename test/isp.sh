#! /bin/bash
current_time1=$(date "+%s")
./tpg
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "TPG module consumes ${result}s."

current_time1=$(date "+%s")
./dgain
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "DGAIN module consumes ${result}s."

current_time1=$(date "+%s")
./lsc
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "LSC module consumes ${result}s."

current_time1=$(date "+%s")
./dpc
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "DPC module consumes ${result}s."

current_time1=$(date "+%s")
./rawdns
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "RAW DENOISE module consumes ${result}s."

current_time1=$(date "+%s")
./awb
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "AWB module consumes ${result}s."

current_time1=$(date "+%s")
./wbc
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "WBC module consumes ${result}s."

current_time1=$(date "+%s")
./gb
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "GB module consumes ${result}s."

current_time1=$(date "+%s")
./demosaic
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "demosaic module consumes ${result}s."

current_time1=$(date "+%s")
./ee
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "EE module consumes ${result}s."

current_time1=$(date "+%s")
./cmc
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "CMCmodule consumes ${result}s."

current_time1=$(date "+%s")
./gtm
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "GTM module consumes ${result}s."

current_time1=$(date "+%s")
./ltm
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "LTM module consumes ${result}s."

current_time1=$(date "+%s")
./cac
current_time2=$(date "+%s")
result=$((current_time2 - current_time1))
echo "CAC module consumes ${result}s."