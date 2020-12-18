
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
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Matrix 5x7 allocation took: AVG = %ldus MIN = %ldus MAX = %luus.\n", static_cast<long>(avg), min, max, random);
    
    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        m1->ApplyFunction(Briand::Math::Identity);
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Matrix 5x7 function apply took: AVG = %ldus MIN = %ldus MAX = %luus.\n", static_cast<long>(avg), min, max, random);
    
    m1 = make_unique<Matrix>(5, 7, 2.2);
    m2 = make_unique<Matrix>(7, 3, 0.5);

    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        m3 = m1->MultiplyMatrix(*m2.get());
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Matrix 5x7 multiply by 7x3 took: AVG = %ldus MIN = %ldus MAX = %luus.\n", static_cast<long>(avg), min, max, random);

    m1 = make_unique<Matrix>(5, 7, 2.2);
    for (uint8_t i = 0; i<TESTS; i++) {
        auto vin = make_unique<vector<double>>(7, 0.5);
        start = esp_timer_get_time();
        auto vout = m1->MultiplyVector(*vin.get());
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Matrix 5x7 multiply by vector of 7 elements took: AVG = %ldus MIN = %ldus MAX = %luus.\n", static_cast<long>(avg), min, max, random);

    m1 = make_unique<Matrix>(5, 7, 2);
    m2 = make_unique<Matrix>(5, 7, 2);
    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        m3 = m1->MultiplyMatrixHadamard(*m2.get());
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Matrix 5x7 Hadamard product took: AVG = %ldus MIN = %ldus MAX = %luus.\n", static_cast<long>(avg), min, max, random);

    /* tests

    {
        m1 = make_unique<Matrix>(std::initializer_list<std::initializer_list<double>>( { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} } ));
        auto vin = make_unique<vector<double>>(3, 0.5);
        auto vout = m1->MultiplyVector(*vin.get());
        printf("\n\nVOUT = ");
        for (int i =0; i<vout->size(); i++) printf("%lf ", vout->at(i));
        printf("\n\n");
    }

    m1 = make_unique<Matrix>(std::initializer_list<std::initializer_list<double>>( { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} } ));
    m2 = make_unique<Matrix>(std::initializer_list<std::initializer_list<double>>( { {3, 5}, {2, 0}, {6, 1} } ));

    m3 = m1->MultiplyMatrix(*m2.get());
    m3->Print();

    m1 = make_unique<Matrix>(std::initializer_list<std::initializer_list<double>>( { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} } ));

    */
    
    m1.reset();
    m2.reset();
    m3.reset();

    //
    // Function calculations
    //

    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        random = Briand::Math::Random();
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Random generation took: AVG = %ldus MIN = %ldus MAX = %luus. Latest random is: %lf\n", static_cast<long>(avg), min, max, random);
    
    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        result = Briand::Math::ReLU(random*3.0);
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("ReLU(x) took: AVG = %ldus MIN = %ldus MAX = %luus. X = %lf\n", static_cast<long>(avg), min, max, random*3.0);

    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        result = Briand::Math::Sigmoid(random*100.0);
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));
    } 
    printf("Sigmoid(x) took: AVG = %ldus MIN = %ldus MAX = %ldus. X = %lf\n", static_cast<long>(avg), min, max, random*100.0);

    for (uint8_t i = 0; i<TESTS; i++) {
        start = esp_timer_get_time();
        result = Briand::Math::MSE(random*10.0, random*4.279);
        took = esp_timer_get_time() - start;
        avg = (i == 0 ? 0 : avg);
        min = (i == 0 ? took : ( took < min ? took : min ));
        max = (i == 0 ? took : ( took > max ? took : max ));
        avg += (static_cast<double>(took) / static_cast<double>(TESTS));