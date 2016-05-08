# 1 "baudcheck.c"
# 1 "/home/kub/Transistortester/transistortester/bootloaders/optiboot//"
# 1 "<command-line>"
# 1 "baudcheck.c"
# 21 "baudcheck.c"
bpsx=115200
bps=${bpsx/L/}
bps=${bpsx/U/}
fcpux=16000000
fcpu=${fcpux/L/}
fcpu=${fcpux/U/}
# 78 "baudcheck.c"
BAUD_SETTING=$(( ( ( ( ($fcpu + ($bps * 4)) / ($bps * 8)) ) - 1) ))







BAUD_ACTUAL=$(( ($fcpu/(8 * (($BAUD_SETTING)+1))) ))
BAUD_ERROR=$(( (( 100*($BAUD_ACTUAL - $bps) ) / $bps) ))
ERR_TS=$(( ((( 1000*($BAUD_ACTUAL - $bps) ) / $bps) - $BAUD_ERROR * 10) ))
ERR_TENTHS=$(( ERR_TS > 0 ? ERR_TS: -ERR_TS ))




echo BAUD RATE CHECK: Desired: $bps, Real: $BAUD_ACTUAL, UBRRL = $BAUD_SETTING, Error=$BAUD_ERROR.$ERR_TENTHS\%
