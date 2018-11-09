# Telescope Control System

Telescope Control System is a C++ program for the Raspberry Pi. The program communicates with a connected Arduino that reorients a telescope. The telescope can be reoriented using the inputted horizontal celestial coordinates from the Qt Interface on the Pi. 

## Getting Started

The instructions below will allow you to compile the project and run it on the Raspberry Pi.

### Prerequisites
Install the Qt libraries using `apt`: 
```
sudo apt install qt5-default
```

### Installation

Generate the `Makefile` using the existing project `telescope.pro`:
```
qmake telescope.pro
```

Build the program:
```
make
```

## Usage
After installation just run the program from the directory `group25`:
```
./telescope
```

## Development
If you wish to build the program with the files you are developing, edit the `telescope.pro` file to include `.h` and `.cpp` files. The `telescope.pro` file should look like this: 
```
QT += widgets

TEMPLATE = app
TARGET = telescope
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS


# Input
HEADERS += backendwrapper.h \
           telescopeui.h
FORMS += raspberrypiutility.ui
SOURCES += backendwrapper.cpp \
           main.cpp \
           telescopeui.cpp
RESOURCES += raspberrypiutility.qrc
```

Qt `.ui` files should be appended to `FORMS`, C++ header `.h` files to `HEADERS`, C++ files `.cpp` to `SOURCES`. 

To generate a fresh Qt project file:
```
qmake -project -o telescope.pro
```
Edit `telescope.pro` to include: 
```
QT += widgets
```

