
# Eventuo-Esp32AI

This repository contains a simple C++17 Neural Network (NN), Convolutional Neural Network (CNN), and Deep Learning for Esp32 on IDF from scratch.

## Intro

After Espressif's ESP32-S3 and devkits derivates (such as ESP-EYE), the goal is to create an easy library in C++17 as an alternative to ESP-DL and ESP-NN, working with IDF version 5.0. This library can also be used in Windows or Linux o.s. for testing, learning, and fun.

The project is composed of a library as an IDF Component (includes a tutorial) that can be used as a source or, if preferred, as a static library (.a file). It also includes a main.cpp file with a sample project which contains library testing and performance details. More information can be found in the test and project examples sections.

### Why from scratch?

Because it's all about learning, overcoming challenges, and continuing to improve. Technology should be a passion, a learning journey every step of the way.

*Simply... because we love it*

<a href="https://www.buymeacoffee.com/eventuo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee&emoji=&slug=eventuo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" /></a>

## Aside from the library...

Take a look at the [Tutorial](AI Tutorial.md). It explains this project in a fun and easy way, perfect for beginners and includes notes collected over the years. The tutorial is closely related to the project, each major chapter has a "see in the code" section for easy reference.

## Library contents

The library includes a unique and easy-to-use header file. Just `#include "BriandAI.hxx"` and you're ready to get started with your own C++ software.

**Note:** This tutorial and all related files are under the *Briand* namespace.

More details are available in the `components/briand_ai/` directory.

## Performing tests

A series of tests and examples are available in the [examples.cpp](main/examples.cpp) file. By default, all are run with the [main.cpp](main/main.cpp) file.

## Using with ESP32

This project is compatible with any ESP32 platform with adequate power and SPIRAM. The [sdkconfig](sdkconfig) file is included but can be replaced with your own configuration.

## Using with Linux

For Linux users, the `components/briand_ai/BriandPorting.hxx` file redefines needed ESP-IDF functions for Linux use. You can see and adjust what you need in the [Makefile](/platform_porting/Makefile). Run the `make` command to compile the library under Linux. The main.cpp file is then compiled, and an executable is created.

**Note:** The library has been tested under *g++ (Debian 8.3.0-6) 8.3.0*.

## Using with Windows

The library *could* be used under Windows too with the same makefile. However, there may be some slight differences which will be updated accordingly.

## Library performances and future tasks

A variety of performance tests and future enhancements are being planned. Stay tuned for more information which will be updated periodically.

## Contributions

Feel free to fork the project, create a PR if you want to enhance this code by adding new functionalities or by improving the current ones. All your comments a