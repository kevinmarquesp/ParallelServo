TEST_SKETCH ?= test/test.ino
LIB ?= src

ARDUINO_CLI_BIN ?= ${HOME}/.local/bin/arduino-cli
AUNITER_BIN ?= ${HOME}/.local/share/AUniter/auniter.sh

BOARD_SHORT ?= uno
BOARD_LONG ?= arduino:avr:uno
PORT ?= /dev/ttyUSB0

test-avr-uno:
	@echo "log: Compoiling tests for the arduino:avr:uno board"
	@echo "\nwarn: In order to use auniter.sh, you'll need to change the source"
	@echo "code of that test script to allow you to pass options to the arduino-cli"
	@echo "binnary string...\n"
	AUNITER_ARDUINO_CLI="$(ARDUINO_CLI_BIN) --library $(LIB)" \
		$(AUNITER_BIN) --cli test $(BOARD_SHORT):$(PORT) $(TEST_SKETCH)
