.PHONY: build 

BAUDRATE:=115200

info:
	@echo '{"port":"$(PORT)","fqbn":"$(FQBN)"}' | jq

dev:
	pio run -t compiledb

build:
	pio run

deploy:
	pio run --target upload 

monitor:
	pio device monitor -b $(BAUDRATE)

