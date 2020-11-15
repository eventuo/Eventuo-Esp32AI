
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

#ifndef BRIAND_FCNN_H
#define BRIAND_FCNN_H

#include "BriandInclude.hxx"
#include "BriandMatrix.hxx"
#include "BriandMath.hxx"

using namespace std;
using namespace Briand;

namespace Briand {

    /** @brief A layer of neurons */
    class NeuralLayer {
        protected:

        /// @brief Weights FROM PREVIOUS LAYER
        unique_ptr<Matrix> _weights;

        /// @brief Neuron net values (weighted sum)
        unique_ptr<vector<double>> _neuronsNet;

        /// @brief Neuron activated values 
        unique_ptr<vector<double>> _neuronsOut;
        
        /// @brief Bias neuron weights (input and hidden layers only, otherwise nullptr)
        unique_ptr<vector<double>> _bias_weights;

        /// @brief Delta of this layer
        unique_ptr<vector<double>> _delta;

        /// @brief Layer type
        LayerType _type;

        /// @brief Layer activation function (hidden and output layer only)
        ActivationFunction _f;

        /// @brief Layer activation function derivative (hidden and output layer only)
        ActivationFunction _df;

        /// @brief Error calculation function
        ErrorFunction _E;

        /// @brief Error calculation function derivative
        ErrorFunction _dE;

        public:

        /// @brief Builds a layer.
        /// @param type Layer type
        /// @param neurons Number of neurons
        /// @param f Activation function (hidden and output layer only, mandatory)
        /// @param df Activation function derivative (hidden and output layer only, mandatory)