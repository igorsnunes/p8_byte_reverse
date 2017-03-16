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
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).AP1.$(OUT) $(FLAGS) -D_INPUT32 -D_AP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).AP2.$(OUT) $(FLAGS) -D_INPUT32 -D_AP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).$(OUT) $(FLAGS) -D_INPUT32
		$(CC) $(C_FILES) -o $(BIN_DIR)/AP1.$(OUT) $(FLAGS) -D_AP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/AP2.$(OUT) $(FLAGS) -D_AP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(OUT) $(FLAGS)

debug:
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).AP1.$(OUT) $(DBG_FLAGS) -D_INPUT32 -D_AP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).AP2.$(OUT) $(DBG_FLAGS) -D_INPUT32 -D_AP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).$(OUT) $(DBG_FLAGS) -D_INPUT32
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).AP1.$(OUT) $(DBG_FLAGS) -D_AP1
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).AP2.$(OUT) $(DBG_FLAGS) -D_AP2
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(OUT) $(DBG_FLAGS)

test: le
		./$(BIN_DIR)/$(INPUT32).AP1.$(OUT) > $(INPUT32).AP1.$(TXT_O)
		./$(BIN_DIR)/$(INPUT32).AP2.$(OUT) > $(INPUT32).AP2.$(TXT_O)
		./$(BIN_DIR)/$(INPUT32).$(OUT)     > $(INPUT32).$(TXT_O)
		./$(BIN_DIR)/AP1.$(OUT) > AP1.$(TXT_O)
		./$(BIN_DIR)/AP2.$(OUT) > AP2.$(TXT_O)
		./$(BIN_DIR)/$(OUT)     > $(TXT_O)

clean:
		rm -rf $(BIN_DIR)
		rm -rf *.$(TXT_O)
