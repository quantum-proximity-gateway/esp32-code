.PHONY: all run monitor

all: run

run:
	pio run --target upload

monitor:
	pio device monitor
