CMAKE = cmake
BUILD_DIR = build
CMAKE_FLAGS =-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

all: build shaders

build:
	mkdir -p $(BUILD_DIR)
	$(CMAKE) -S . -B $(BUILD_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR)

shaders:
	./shaders/compile_shaders.sh ./shaders

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build shaders clean

