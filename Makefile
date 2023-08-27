TEST_SKETCH := test/test.ino
LIB := src
LIB_NAME := ParallelServo
EXAMPLES := examples
LIB_PROPS := library.properties
LIB_KEYS := keywords.txt
LICENSE := LICENSE
DIST_DIR := dist

ARDUINO_CLI_BIN ?= ${HOME}/.local/bin/arduino-cli
AUNITER_BIN ?= ${HOME}/.local/share/AUniter/auniter.sh

BOARD_SHORT ?= uno
BOARD_LONG ?= arduino:avr:uno
PORT ?= /dev/ttyUSB0

list-todos:
	@rg -n 'todo:' ./ | sed 's/: *\/\//: \/\//'

test-aunit:
	@echo "log: Compoiling tests with the auniter.sh command line tool"
	@echo "\nwarn: In order to use auniter.sh, you'll need to change the source"
	@echo "code of that test script to allow you to pass options to the arduino-cli"
	@echo "binnary string...\n"
	AUNITER_ARDUINO_CLI="$(ARDUINO_CLI_BIN) --library $(LIB)" \
		$(AUNITER_BIN) --cli test $(BOARD_SHORT):$(PORT) $(TEST_SKETCH)

test-cli:
	@echo "log: Uploading the test sketch"
	@stty -F $(PORT) raw 115200
	@$(ARDUINO_CLI_BIN) compile --library $(LIB) -u -b $(BOARD_LONG) -p $(PORT) $(TEST_SKETCH)
	@cat $(PORT)

build:
	@[ -e $(DIST_DIR) ] && rm -rf $(DIST_DIR)
	@mkdir -vp $(DIST_DIR)/$(LIB_NAME)/examples
	@cp -r $(EXAMPLES)/* $(DIST_DIR)/$(LIB_NAME)/examples
	@cp    $(LIB)/*      $(DIST_DIR)/$(LIB_NAME)
	@cp    $(LIB_KEYS)   $(DIST_DIR)/$(LIB_NAME)
	@cp    $(LIB_PROPS)  $(DIST_DIR)/$(LIB_NAME)
	@cp    $(LICENSE)    $(DIST_DIR)/$(LIB_NAME)
	@VERSION=$$(grep "version" $(LIB_PROPS) | cut -d= -f2); \
		cd $(DIST_DIR); \
		zip -r $(LIB_NAME)-$${VERSION}.zip $(LIB_NAME)
	@rm -rf $(DIST_DIR)/$(LIB_NAME)
