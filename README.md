# Music recognition system in C++17
Library for recognizing songs using short noisy recordings. It is designed to be 
fast without sacrificing code readability.

The average time spent analyzing a song of 3 min is 1.9s on a i5-6200U with
release optimizations turned on.

The algorithm is discussed in the [algorithm.pdf](algorithm.pdf) file.

##### Table of Contents
[Configuration](#configuration)  
[Requirements](#requirements)
[Convert an audio to WAV](#convertWav)
[Build instructions](#build)
[Contributing](#contrib)

<a name="configuration"/>
## Configuration

1. In the `Consts.h` file insert the correct hostname, username and password
   (the database will be automatically created if not existent)
1. Put some WAV files in a directory
1. Run the program with the following parameters: `-i <path to wav files>`
1. Wait until the program exits
1. Record a small piece of song previously in the WAV directory
1. Feed the recording to the program with the following parameters: 
   `-s <path to recording>`
1. Eventually a result will be showed

You might also need set to maximum allowed packed size in MariaDB / MySQL.
To do so add `max_allowed_packet=64M` to `/etc/my.cnf` or
`C:\Program Files\MariaDB <ver>\data`.

<a name="requirements"/>
## Requirements
* MariaDB / MySQL
* Some WAV files
* ffmpeg (optional)

<a name="convertWav"/>
## Convert an audio to WAV
`ffmpeg -i audiofile.ext -ar 8000 -ac 1 out.wav`

<a name="build"/>
## Build instructions
### Debian
1. `git submodule update --init --recursive`
1. `sudo apt install libmariadbclient-dev`
1. `sudo apt install libfftw3-dev`

### Windows (MSys2)
1. `git submodule update --init --recursive`
1. `pacman -S mingw-w64-x86_64-libmariadbclient`
1. `pacman -S mingw-w64-x86_64-fftw`

<a name="contrib"/>
## Contributing
Since C++ is a bit new to me there might be some errors or incorrectness
in the code: feel free to make a pull request, open a issue or contact
me :)
