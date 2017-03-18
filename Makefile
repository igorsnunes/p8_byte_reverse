.PHONY: all le debug clean test

CC=gcc
C_FILES=le.c
DBG_FLAGS=-O0 -g
FLAGS=-O3
OUT=le.o
INPUT32=input32
INPUT64=input64
DBG=dbg
BIN_DIR=./bin
TXT_O=out.txt


all: le debug

le: $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).VPERM.$(OUT) $(FLAGS) -DINPUT32 -DVPERM
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).ROTATE.$(OUT) $(FLAGS) -DINPUT32 -DROTATE
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).CVERSION.$(OUT) $(FLAGS) -DINPUT32 -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT32).LBRX.$(OUT) $(FLAGS) -DINPUT32 -DLBRX
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT64).VPERM.$(OUT) $(FLAGS) -DVPERM
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT64).ROTATE.$(OUT) $(FLAGS) -DROTATE
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT64).CVERSION.$(OUT) $(FLAGS) -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(INPUT64).LBRX.$(OUT) $(FLAGS) -DLBRX

debug: $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).VPERM.$(OUT) $(DBG_FLAGS) -DINPUT32 -DVPERM
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).ROTATE.$(OUT) $(DBG_FLAGS) -DINPUT32 -DROTATE
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).CVERSION.$(OUT) $(DBG_FLAGS) -DINPUT32 -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).$(INPUT32).LBRX.$(OUT) $(DBG_FLAGS) -DINPUT32 -DLBRX
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).VPERM.$(OUT) $(DBG_FLAGS) -DVPERM
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).ROTATE.$(OUT) $(DBG_FLAGS) -DROTATE
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).CVERSION.$(OUT) $(DBG_FLAGS) -DCVERSION
		$(CC) $(C_FILES) -o $(BIN_DIR)/$(DBG).LBRX.$(OUT) $(DBG_FLAGS) -DLBRX

test: le
		sh plot_results.sh "32-bits-byte-reverse-op"  $(INPUT32).VPERM.$(OUT) $(INPUT32).ROTATE.$(OUT) $(INPUT32).CVERSION.$(OUT) $(INPUT32).LBRX.$(OUT) $(BIN_DIR)
		sh plot_results.sh "64-bits-byte-reverse-op"  $(INPUT64).VPERM.$(OUT) $(INPUT64).ROTATE.$(OUT) $(INPUT64).CVERSION.$(OUT) $(INPUT64).LBRX.$(OUT) $(BIN_DIR)

clean:
		rm -rf $(BIN_DIR)
		rm -rf $(TXT_O).*
		rm -rf *.dat
		rm -rf *.png
