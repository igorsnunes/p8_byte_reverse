.PHONY: all le debug clean

CC=gcc
C_FILES=le.c
DBG_FLAGS=-O0 -g
FLAGS=-O3
OUT=le.o
INPUT32=input32
DBG=dbg
BIN_DIR=./bin
TXT_O=le.txt


all: le debug

le: $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).AP1.$(OUT) $(FLAGS) -DINPUT32 -DAP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).AP2.$(OUT) $(FLAGS) -DINPUT32 -DAP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).CVERSION.$(OUT) $(FLAGS) -DINPUT32 -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).$(OUT) $(FLAGS) -DINPUT32
		$(CC) $(C_FILES) -o $(BIN_DIR)/AP1.$(OUT) $(FLAGS) -DAP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/AP2.$(OUT) $(FLAGS) -DAP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/CVERSION.$(OUT) $(FLAGS) -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(OUT) $(FLAGS)

debug:
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).AP1.$(OUT) $(DBG_FLAGS) -DINPUT32 -DAP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).AP2.$(OUT) $(DBG_FLAGS) -DINPUT32 -DAP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).CVERSION.$(OUT) $(DBG_FLAGS) -DINPUT32 -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).$(OUT) $(DBG_FLAGS) -DINPUT32
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).AP1.$(OUT) $(DBG_FLAGS) -DAP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).AP2.$(OUT) $(DBG_FLAGS) -DAP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).CVERSION.$(OUT) $(DBG_FLAGS) -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(OUT) $(DBG_FLAGS)

test: le
		./$(BIN_DIR)/$(INPUT32).AP1.$(OUT) > $(INPUT32).AP1.$(TXT_O)
		./$(BIN_DIR)/$(INPUT32).AP2.$(OUT) > $(INPUT32).AP2.$(TXT_O)
		./$(BIN_DIR)/$(INPUT32).CVERSION.$(OUT) > $(INPUT32).CVERSION.$(TXT_O)
		./$(BIN_DIR)/$(INPUT32).$(OUT)     > $(INPUT32).$(TXT_O)
		./$(BIN_DIR)/AP1.$(OUT) > AP1.$(TXT_O)
		./$(BIN_DIR)/AP2.$(OUT) > AP2.$(TXT_O)
		./$(BIN_DIR)/CVERSION.$(OUT) > CVERSION.$(TXT_O)
		./$(BIN_DIR)/$(OUT)     > $(TXT_O)

clean:
		rm -rf $(BIN_DIR)
		rm -rf *$(TXT_O)
