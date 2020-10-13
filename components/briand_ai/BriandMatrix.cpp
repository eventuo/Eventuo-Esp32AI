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

    for (auto& r : m) {
        if (this->_cols == 0) this->_cols = r.size();
        if (this->_cols != r.size()) throw out_of_range("Matrix cols not uniform in size");
        this->_matrix[i] = new double[this->_cols];
        j = 0;
        for (auto& c : r) this->_matrix[i][j++] = c;
        i++;
    }
}

Matrix::Matrix(const Matrix& other) {
    // Instance new matrix with same rows and cols
    this->_rows = other.Rows();
    this->_cols = other.Cols();
    
    // Copy matrix weights while instancing
    this->_matrix = new double*[this->_rows];
    for (size_t i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new double[this->_cols];
        for (size_t j = 0; j < this->_cols; j++)
            this->_matrix[i][j] = other[i][j];
    }    
}

void Matrix::InstanceMatrix(const double& initialValue /* = 0.0*/) {
    this->_matrix = new double*[this->_rows];
    for (size_t i = 0; i < this->_rows; i++) {
        this->_matrix[i] = new double[this->_cols];
        std::fill_n(this->_matrix[i], this->_cols, initialValue);
    }
}

Matrix::~Matrix() {
    for (size_t i = 0; i < this->_rows; i++) {
        if (this->_matrix[i] != nullptr) delete[] this->_matrix[i];
    }
    
    if (this->_matrix != nullptr) delete[] this->_matrix;
}

const size_t& Matrix::Rows() const {
    return this->_rows;
}

const size_t& Matrix::Cols() const {
    return this->_cols;
}

void Matrix::Randomize() {
    for (size_t i = 0; i < this->_rows; i++) {
        for (size_t j = 0; j < this->_cols; j++) {
            // Random between 0 and 1
            this->at(i, j) = static_cast<double>(esp_random()) / static_cast<double>(RAND_MAX);        }
    }
}

void Matrix::MultiplyScalar(con