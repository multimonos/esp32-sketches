.PHONY: build blinker

include ../boards/esp32-wroom-32e.mk

info:
	@echo '{"port":"$(PORT)","fqbn":"$(FQBN)"}' | jq

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
		--port $(PORT)

attach:
	arduino-cli board attach \
		--port $(PORT) \
		--fqbn $(FQBN) \
		--verbose


deploy: build upload monitor
