# TODO: choose it:  -I vulkan_renderer 
CFLAGS = -std=c11 -O2 -g -I src -D_DEBUG
LDFLAGS = -lvulkan -lX11 -lxcb -lpthread 
BIN = main
C_COMPILER = clang

OUT_DIR = output

# main binary file
main: $(OUT_DIR)/main.o $(OUT_DIR)/logger.o $(OUT_DIR)/platform.o $(OUT_DIR)/rmemory.o $(OUT_DIR)/darray.o
	$(C_COMPILER) $^ -o $@ $(LDFLAGS)

$(OUT_DIR)/main.o: main.c
	$(C_COMPILER) $< -c -o $@ $(CFLAGS) 


# core
$(OUT_DIR)/logger.o: src/core/logger.c src/core/logger.h src/core/asserts.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS)

$(OUT_DIR)/rmemory.o: src/core/rmemory.c src/core/rmemory.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS)


#containers
$(OUT_DIR)/darray.o: src/containers/darray.c src/containers/darray.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS)


#platform
$(OUT_DIR)/filesystem.o: src/platform/filesystem.c src/platform/filesystem.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS)

# platform layer
ifdef COMSPEC
$(OUT_DIR)/platform.o: src/platform/platform_windows.c src/platform/platform.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS) 
else
$(OUT_DIR)/platform.o: src/platform/platform_linux.c src/platform/platform.h
	$(C_COMPILER) $< -c -o $@ $(CFLAGS) 
endif

# cleaning rules
.PHONY: clean clean-all

clean:
	@rm main

clean-all:
	@rm main
	@rm output/*
