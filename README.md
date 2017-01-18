# PixeLab
整合OpenCv与wxWidgets尝试性小测试

### 1. 需要的支持库与版本
* OpenCV 3.1.0
* wxWidgets 3.1.0

### 2. 编译步骤
* Linux
```bash
mkdir build
cd build
cmake /path/to/PixeLab
make
```

* Linux下MinGW32交叉编译环境
```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain/file
make
```
### 3.注意事项
*由于安装部署还没有做,工程构建完成后，将plugins/graylize/graylize.so复制到gui/下（和主程序pixelab同一路径），否则会报错*
