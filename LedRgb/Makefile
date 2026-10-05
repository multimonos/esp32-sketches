.PHONY: build blinker

FQBN:=esp32:esp32:esp32
PORT:=/dev/cu.usbserial-11530

info:
	@echo '{"port":"$(PORT)","fqbn":"$(FQBN)"}' | jq

# create the compile commands json file for neovim
dev:
	arduino-cli compile --fqbn $(FQBN) --build-path ./build --only-compilation-database . \
	&& cp ./build/compile_commands.json . \
	&& tree

build:
	arduino-cli compile \
		--fqbn $(FQBN) \
		--verbose \
		--clean \
		--export-binaries

upload:
	arduino-cli upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--verbose

monitor:
	arduino-cli monitor \
		--fqbn $(FQBN) \
		--port $(PORT) \
		-c baudrate=115200


attach:
	arduino-cli board attach \
		--port $(PORT) \
		--fqbn $(FQBN) \
		--verbose


deploy: build upload monitor
