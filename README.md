# Sandbox for me to learn graphics programming.

This project uses my own vulkan wrapper and framework to abstract away shaders,
descriptors,pipelines,synchronization and a lot more.

## Building and Running

### Requirements:
- [glitch](https://github.com/Gl1tchs/glitch) should be installed in your system.
- glslc or other spirv compiler (note that the compiler should preserve the
bindings via -fpreserve-bindings for reflection purposes).

```bash
git clone https://github.com/Gl1tchs/glitch-sandbox.git # clone the repository
cd glitch-sandbox # enter the directory
make # build it
build/glitch-sandbox # run it
```

## Examples

You can access each individual examples using the provided "Examples" widget within
the application. The source code of each examples can be found under examples/ directory.
