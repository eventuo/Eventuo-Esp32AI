
/** Copyright (C) 2023 briand (https://github.com/briand-hub)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef BRIAND_AI_DEBUG
    #define BRIAND_AI_DEBUG 1 // DEBUG MODE (print to stdout calculus and other info)
#endif

#ifndef BRIAND_INCLUDE_H
#define BRIAND_INCLUDE_H

    /* All headers needed in library, includes the porting to other platforms */

    // C++ STL

    #include <iostream>
    #include <cstdio>
    #include <cmath>
    #include <memory>
    #include <vector>
    #include <map>
    #include <cstdlib>
    #include <cstring>
    #include <thread>
    #include <chrono>
    #include <algorithm>
    #include <unistd.h>
    #include <signal.h>
	#include <limits>
	#include <cassert>

    /* 
        Small code redefining in linux/windows platform used ESP functions and types in order to compile and test on other platforms
    */

    #if defined(ESP_PLATFORM)
        // Set BRIAND_PLATFORM for printing out current platform if needed
        #define BRIAND_PLATFORM "ESP32"

        // Here normal ESP Headers must be used

        #include "esp_log.h"
		#include "esp_random.h"
		#include "esp_timer.h"

    #elif defined(__linux__) | defined(_WIN32)
        // Set BRIAND_PLATFORM for printing out current platform if needed
        #if defined(__linux__)
            #define BRIAND_PLATFORM "Linux"
        #elif defined(_WIN32)
            #define BRIAND_PLATFORM "Windows"
        #endif

        // Define the entry point (app_main will never be called!)