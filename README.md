# PIDinfo

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Usage](#usage)

## General info
Program written in **C** (C99) under **Linux** which prints PIDs and names of processes running in the system.

## Technologies
Project is created with:
* gcc 9.3.0
* cmake 3.16.3
* make 4.2.1.

## Setup
To run this project:
* open a Linux terminal 
* enter project's root directory in the terminal
```bash
  cd Linux-Process-PID-Printer
```
* create a new directory with a name "build" (or any other name, it doesn't really matter)
```bash
  mkdir build
```
* enter the newly created directory
```bash
  cd build
```
* run the cmake program in order to generate makefiles from CMakeLists.txt files
```bash
  cmake ..
```
* run the make program to compile the code into an executable and libraries
```bash
  make
```
At this point, if no errors have been encountered, the program PIDinfo, ready to use, should be inside build directory.

## Usage
```bash
  ./PIDinfo { -a | -u <pid> | -n <name> } [ -f <file> ]
```
* **-a**, print pids and names of all running processes;
* **-u**, print name of process with given `<pid>`
* **-n**, print pid of process with given `<name>`
* **-f**, write output to `<file>` instead of stdout
