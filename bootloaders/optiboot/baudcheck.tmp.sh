# 1 "baudcheck.c"
# 1 "/home/kub/Transistortester/transistortester/bootloaders/optiboot//"
# 1 "<command-line>"
# 1 "baudcheck.c"
# 44 "baudcheck.c"
bps=`$ECHO_CMD 115200 | $TR_CMD -d LU`






fcpu=`$ECHO_CMD 16000000 | $TR_CMD -d LU`





$ECHO_CMD ---------------------------------------------------------------------------
# 146 "baudcheck.c"
BAUD_SETTING=$(( ( ( ($fcpu / 4 / $bps ) - 1) / 2) ))
UartDelay=$(( (8 * ((BAUD_SETTING) +1)) ))
# 162 "baudcheck.c"
$ECHO_CMD BAUD RATE CHECK: Desired: $bps, Real: `$ECHO_CMD "scale=0;($fcpu / $UartDelay)" | $BC_CMD`, UBRR = $BAUD_SETTING, Error=`$ECHO_CMD "scale=2;(100*(($fcpu / $UartDelay) - $bps) ) / $bps"| $BC_CMD`\%






$ECHO_CMD ---------------------------------------------------------------------------
