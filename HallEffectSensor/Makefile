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

plot:
	@/usr/bin/script -q /dev/null pio device monitor -b $(BAUDRATE) \
		|grep --line-buffered -v '^---' \
		|sed -u 's/^.*\:\s//g' \
		|ttyplot -t 'hall-effect'

run: deploy monitor

