#/bin/bash

BIN=./build/speedtest
TIMESTAMP=$(date +%s)
SUFFIX=.data
LOGFILE=$TIMESTAMP$SUFFIX

echo "Data will be logged to $LOGFILE"

#one call results in an all layouts run
log() {
  echo "$BIN $1 RANDOM $2 $3"
  $BIN $1 RANDOM $2 $3 1>>$LOGFILE 2>/dev/null
  echo "$BIN $1 SORTED $2 $3"
  $BIN $1 SORTED $2 $3 1>>$LOGFILE 2>/dev/null
  echo "$BIN $1 LAYERS $2 $3"
  $BIN $1 LAYERS $2 $3 1>>$LOGFILE 2>/dev/null
  echo "$BIN $1 EMDEBOAS $2 $3 $4"
  $BIN $1 EMDEBOAS $2 $3 $4 1>>$LOGFILE 2>/dev/null
}
loglog() {
  log 10 1000 42 $1
  log 12 1000 42 $1
  log 14 1000 42 $1
  log 16 1000 42 $1
  log 18 1000 42 $1
  #log 20 1000 42 $1
}

#call log function with exponent iterations seed blockheight
loglog 3
loglog 4
loglog 5
