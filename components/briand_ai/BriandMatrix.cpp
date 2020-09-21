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

#include "BriandMatrix.hxx"

using namespace std;
using namespace Briand;

Matrix::Matrix(const int& rows, const int& cols, const double& initialValue /*= 0.0*/) {
    this->_rows = rows;
    this->_cols = cols;
    this->InstanceMatrix(initialValue);
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& m) {
    this->_rows = m.size();
    this->_cols = 0;
    
    this->_matrix = new double*[this->_rows];
    size_t i = 0;
    size_t j;

    fo