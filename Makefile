.PHONY: all run monitor

all: run

run:
	cd BLE-Broadcasting && \
	pio run --target upload

monitor:
	cd BLE-Broadcasting && \
	pio device monitor
