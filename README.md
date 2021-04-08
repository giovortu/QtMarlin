# QtMarlin 

This project aim is to improve the old [QTMarlin](https://github.com/bkubicek/QTMarlin ) code using a more up to date Qt library and QSerialPort classes.

### 

### Used libraries

* Qt 5 library ( not included )
* Qwt library ( included ) 

#### Required versions

* Qt 5.1x version, tested on Qt 5.15.2
* Qwt library  : Qwt-6.2 SVN

Qwt library is located in 

```bash
libs/qwt-6.2
```
Qwt library is statically linked into the application. I've managed to not modify the code from SVN repository using a wrapper project.  
  
It is possible to update the Qwt library, please note that the content of **qwt.pri** must reflect the source / header files in **libs/qwt-6.2/src/src.pri**


### Build environments

- [x] Linux
- [ ] Windows
- [ ] Osx

### How to build

```bash

$ git clone git@github.com:giovortu/QtMarlin.git
$ mkdir build
$ cd build
$ qmake ../QtMarlin/
$ make 


```




## The old Readme
This will soon be a QT tool for the marlin firmware.

* indended features:
* Temp monitoring+PID adjustments,
* find accurate accelerations/velocities
* eeprom values managing
* configuration.h and pins.h creation.

requires: qt 4, qwt v5, qserialdevice 
currently tested in linux
to build, you have to adopt the qtmarlin.pro to have the correct dependency paths.
then qmake-qt4 or just qmake in case there is no qt3 installed.
