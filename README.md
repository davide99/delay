## Build instructions (Debian)

1. `git submodule update --init --recursive`
1. `sudo apt install libmariadbclient-dev`
1. `sudo apt install libfftw3-dev`

## Build instructions (MSys2)

1. `git submodule update --init --recursive`
1. `pacman -S mingw-w64-x86_64-libmariadbclient`
1. `pacman -S mingw-w64-x86_64-fftw`