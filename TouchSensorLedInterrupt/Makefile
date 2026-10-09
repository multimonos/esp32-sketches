.PHONY: build 

BAUDRATE:=115200

info:
	@cat ./platformio.ini \
		&& echo "baudrate: $(BAUDRATE)"

# generate the compile_commands.json
compile:
	pio run -t compiledb

# compile
build:
	pio run

# compile + upload to board
deploy:
	pio run --target upload 

# interactive monitoring
monitor:
	pio device monitor -b $(BAUDRATE)

# non-interactive monitor ( which is pipeable ... use 'sed -u' )
log:
	@/usr/bin/script -q /dev/null pio device monitor -b $(BAUDRATE) |grep --line-buffered -v '^---'

# sample plot command given each line is printing "value: 1234.56" ... exit with "qq"
plot:
	@/usr/bin/script -q /dev/null pio device monitor -b $(BAUDRATE) \
		|grep --line-buffered -v '^---' \
		|sed -u 's/^value: //g' \
		|ttyplot -t 'esp32 data'; \
		stty sane # reset terminal

run: deploy monitor
