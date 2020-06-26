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
    for (size_t i=0; i<neurons; i++) {
        this->_neuronsNet->push_back(0.0);
        this->_neuronsOut->push_back(0.0);
    }
}

NeuralLayer::NeuralLayer(const LayerType& type, const size_t& neurons, ActivationFunction f, ActivationFunction df, ErrorFunction e, ErrorFunction de, const Matrix& weights) 
    : NeuralLayer(type, neurons, f, df, e, de)
{
    // Weights allowed for non-input layers 
    if (this->_type == LayerType::Input) throw runtime_error("Weights not allowed for input layer.");

    // Weight matrix rows must be equal to layer's neurons (not including bias)
    if (weights.Rows() != neurons) throw runtime_error("Weight matrix invalid: must have as many rows as layer's neurons!");

    // Weight matrix cols must be equal to layer's input (cannot check there)

    this->_weights = make_unique<Matrix>(weights);
}

NeuralLayer::NeuralLayer(const LayerType& type, const size_t& neurons, ActivationFunction f, ActivationFunction df, ErrorFunction e, ErrorFunction de, const std::initializer_list<std::initializer_list<double>>& weights)
    : NeuralLayer(type, neurons, f, df, e, de, Matrix{weights})
{
}

NeuralLayer::~NeuralLayer() {
    this->_weights.reset();
    this->_neuronsNet.reset();
    this->_neuronsOut.reset();
    this->_delta.reset();
}

void NeuralLayer::SetBiasWeights(const vector<double>& bias_weights) { 
    // Allowed only for input or hidden layer
    if (this->_type != LayerType::Hidden && this->_type != LayerType::Input) throw runtime_error("Bias allowed only for input or hidden layer.");

    this->_bias_weights = make_unique<vector<double>>(bias_weights); 
}

/**********************************************************************
    FCNN class
***********************************************************************/

FCNN::FCNN() {
    this->_hasOutputs = false;
    this->_layers = make_unique<vector<unique_ptr<NeuralLayer>>>();
}

FCNN::~FCNN() {
    this->_layers.reset();
}

void FCNN::AddInputLayer(const size_t& inputs) {
    // Check
    if (this->_layers->size() > 0) throw runtime_error("Input layer has been added before.");

    auto layer = make_unique<NeuralLayer>(LayerType::Input, inputs, nullptr, nullptr, nullptr, nullptr);
    this->_layers->push_back(std::move(layer));
}

void FCNN::AddInputLayer(const size_t& inputs, const vector<double>& values) {
    // Check
    if (values.size() != inputs) throw runtime_error("Input values: invalid size.");

    this->AddInputLayer(inputs);

    // Initialize values
    for (int i = 0; i<inputs; i++) this->_layers->at(0)->_neuronsOut->at(i) = values[i];
}

void FCNN::SetInput(const vector<double>& values) {
    // Check
    if (this->_layers == nullptr || this->_layers->size() < 1) throw runtime_error("Cannot set input values: missing input layer.");
    if (values.size() != this->_layers->at(0)->_neuronsOut->size()) throw runtime_error("Input values: invalid size.");

    for (int i = 0; i<this->_layers->at(0)->_neuronsOut->size(); i++) this->_layers->at(0)->_neuronsOut->at(i) 