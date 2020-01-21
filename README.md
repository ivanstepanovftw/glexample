Requirements:
- OS: Linux preferred
- cmake 3.16.2-1
- glfw-x11 3.3-2
- libepoxy 1.5.4-1
- glm 0.9.9.6-2

See [CMakeLists.txt](https://github.com/ivanstepanovftw/glexample/blob/master/CMakeLists.txt#L45-L52).

pacman:
```
pacman -S cmake glfw-x11 libepoxy glm
```

apt:
```
apt install cmake libglfw3 libepoxy-dev libglm-dev
```

Compilation and run:
```
git clone https://github.com/ivanstepanovftw/glexample.git
cd glexample
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ..
cmake --build . --target myapp -- -j 6

./myapp
```




install vcpkg somewere:
```shell script
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg
./vcpkg integrate install

# TODO:
#$env:Path += ";SomeRandomPath"
#vcpkg integrate powershell
#./vcpkg integrate bash
```

-DCMAKE_TOOLCHAIN_FILE=C:/Users/ashft/vcpkg/scripts/buildsystems/vcpkg.cmake

