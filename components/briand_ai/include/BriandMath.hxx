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

#ifndef BRIAND_MATH_H
#define BRIAND_MATH_H

#include "BriandInclude.hxx"

using namespace std;

namespace Briand {

    /** @brief class with math functions used in all the project. 
        If a more performing way of calculus is found then you need only to change the implementation here!
    */
    class Math {
        public:

        /** @brief Identity f(x) = x */
        static constexpr double Identity(const double& x) { return x; }
        
        /** @brief Identity derivative f'(x) = 1 */
        static constexpr double DeIdentity(const double& x) { return 1; }

        /** @brief ReLU function */
        static constexpr double ReLU(c