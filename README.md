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

Reproducer:
```
git clone https://github.com/ivanstepanovftw/glexample.git
cd glexample
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" ..

./myapp
```

Uncomment [app.h:7](https://github.com/ivanstepanovftw/glexample/blob/master/app.h#L7) and comment out [app.h:6](https://github.com/ivanstepanovftw/glexample/blob/master/app.h#L6) to solve bug.

Why is this happen? Why [Window](https://github.com/ivanstepanovftw/glexample/blob/master/window.h#L75) destructs itself?
