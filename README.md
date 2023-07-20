# Fake FC for MSP (DP) testing purposes using the Piduino library

This is a fork of https://github.com/hd-zero/hdzero-vtx-arduino (with additional changes from https://github.com/benlumley/hdzero-vtx-arduino/) to provide a fake MSP (DP) FC for testing purposes.

It has been ported to run on a Raspberry PI with the help of [Piduino](https://github.com/epsilonrt/piduino).

## Pre-requesites

First, install the Piduino libraries. On raspbian this can be achieved with:

```
wget -O- http://www.piduino.org/piduino-key.asc | sudo apt-key add -
echo 'deb http://raspbian.piduino.org stretch piduino' | sudo tee /etc/apt/sources.list.d/piduino.list
sudo apt update
sudo apt install libpiduino-dev piduino-utils
```

## On serial ports

One has to adjust the serial port used by the Piduino library in `src/fakefc.cpp` according to one's setup. Please note that the port numbering provided by `pinfo` is not always accurate and some trial and error might be required.

## Compiling and running
```
make
./fakefc
```