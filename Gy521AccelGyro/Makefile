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

# plots the y-value = [-1, 1]
plot:
	@/usr/bin/script -q /dev/null pio device monitor -b $(BAUDRATE) |grep --line-buffered -v '^---' \
		| fx 'd => d.accel ? d.accel.y : null' \
		| ttyplot -M -1 -m 1;
			stty sane # reset terminal

run: deploy monitor
