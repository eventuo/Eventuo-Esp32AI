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

#include "BriandFCNN.hxx"

using namespace std;
using namespace Briand;

/**********************************************************************
    Neural Layer class
***********************************************************************/

NeuralLayer::NeuralLayer(const LayerType& type, const size_t& neurons, ActivationFunction f, ActivationFunction df, ErrorFunction e, ErrorFunction de) {
    // Check
    if (neurons == 0) throw out_of_range("Neurons must be > 0 for any layer");
    if (type == LayerType::Input && (f != nullptr || df != nullptr || e != nullptr)) throw runtime_error("Cannot specify f, df or e for input layer!");
    if (type != LayerType::Input && (f == nullptr || df == nullptr)) throw runtime_error("Must specify f and df for non-input layers!");
    if (type == LayerType::Output && e == nullptr) throw runtime_error("Must specify cost/error calculation for output layer!");
    if (type != LayerType::Output && e != nullptr) throw runtime_error("Cannot specify cost/error calculation for non-output layers!");

    // Initialize
    this->_f = f;
    this->_df = df;
    this->_E = e;
    this->_dE = de;
    this->_type = type;
    this->_weights = nullptr;
    this->_delta = nullptr;

    // Bias neuron value is always 1 so just handle the weights (FCN)
    this->_bias_weights = nullptr;
    if (this->_type == LayerType::Input || this->_type == LayerType::Hidden) {
        // Initialize all weights to 1
        this->_bias_weights = make_unique<vector<double>>(neurons, 1.0);
    }

    this->_neuronsNet = make_unique<vector<double>>();
    this->_neuronsNet->reserve(neurons);

    this->_neuronsOut = make_unique<vector<double>>();
    this->_neuronsOut->reserve(neurons);

    // Initialize neurons to 0
    fo