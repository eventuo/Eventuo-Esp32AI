
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

//#define ESP_PLATFORM

// Only one header is needed to use library.
#include "BriandAI.hxx"

#include "examples.hxx"

// STL and library Namespeces
using namespace std;
using namespace Briand;

/** @brief Porting test */
void test_porting() {
    printf("CURRENT PLATFORM: %s\n", BRIAND_PLATFORM);
}

/** @brief Performance test */
void performance_test(){

    printf("\n\n");
    printf("***********************************************************\n");   
    printf("******************** PERFORMANCE TESTS ********************\n\n");

    long start = 0, took = 0, min = 0, max = 0;
    double result = 0, random = 0, avg = 0;

    // 10 test per task take max/min/avg time
    const uint8_t TESTS = 10;

    //
    // Matrixes
    // 

    unique_ptr<Matrix> m1, m2, m3;

    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        m1 = make_unique<Briand::Matrix>(5, 7, 2.2);
        took = esp_timer_get_time() - start;