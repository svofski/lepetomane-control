mkdir -p bin
export BOARD="Arduino_STM32:STM32F1:genericSTM32F103C6:upload_method=STLinkMethod,cpu_speed=speed_72mhz,opt=osstd"
arduino-cli compile -v -b $BOARD --build-property "build.path=bin/" --build-path build --build-cache-path cache arduino-test $1
