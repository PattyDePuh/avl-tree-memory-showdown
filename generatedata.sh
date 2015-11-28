#/bin/bash

BIN=./build/speedtest
TIMESTAMP=$(date +%s)
SUFFIX=.data
LOGFILE=$TIMESTAMP$SUFFIX

echo "Data will be logged to $LOGFILE"

#one call results in an all layouts run
log() {
  $BIN $1 RANDOM $2 $3 1>>$LOGFILE 2>/dev/null
  $BIN $1 SORTED $2 $3 1>>$LOGFILE 2>/dev/null
  $BIN $1 LAYERS $2 $3 1>>$LOGFILE 2>/dev/null
  $BIN $1 EMDEBOAS $2 $3 $4 1>>$LOGFILE 2>/dev/null
}
loglog() {
  log 4 100000 42 $1
  log 6 100000 42 $1
  log 8 100000 42 $1
  log 10 100000 42 $1
}

#call log function with exponent iterations seed blockheight
loglog 2
loglog 3
loglog 4
