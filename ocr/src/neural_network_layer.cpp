//
//  neural_network_layer.cpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#include "neural_network_layer.hpp"

NeuralNetworkLayer::NeuralNetworkLayer()
{
    parent_layer_ = nullptr;
    child_layer_ = nullptr;
    linear_output_ = false;
    use_momentum_ = false;
    momentum_factor_ = 0.0;
}

void NeuralNetworkLayer::Initialize(int num_nodes, NeuralNetworkLayer *parent, NeuralNetworkLayer *child)
{
    number_of_nodes_ = num_nodes;
    
    neuron_values_.assign(number_of_nodes_, 0.0);
    desired_values_.assign(number_of_nodes_, 0.0);
    errors_.assign(number_of_nodes_, 0.0);
    
    if (parent)
        parent_layer_ = parent;
    
    if (child) {
        child_layer_ = child;
        
        std::vector<double> child_weights;
        
        child_weights.assign(number_of_child_nodes_, 0.0);
        for (int i = 0; i < number_of_nodes_; i++) {
            weights_.push_back(child_weights);
            weight_changes_.push_back(child_weights);
        }
        
        bias_values_.assign(number_of_child_nodes_, -1.0);
        bias_weights_.assign(number_of_child_nodes_, 0.0);
    } else {
        weights_.clear();
        bias_values_.clear();
        bias_weights_.clear();
    }
}

void NeuralNetworkLayer::CleanUp()
{
    weights_.clear();
    weight_changes_.clear();
    neuron_values_.clear();
    desired_values_.clear();
    errors_.clear();
    bias_weights_.clear();
    bias_values_.clear();
}

void NeuralNetworkLayer::RandomizeWeights()
{
    int i, j;
    int min = 0;
    int max = 200;
    int number = 0;
    
    srand((unsigned)time(nullptr));
    
    for (i = 0; i < number_of_nodes_; i++) {
        for (j = 0; j < number_of_child_nodes_; j++) {
            number = ((abs(rand()) % (max - min + 1)) + min);
            
            if (number > max)
                number = max;
            if (number < min)
                number = min;
            
            weights_[i][j] = static_cast<double>(number) / 100.0 - 1;
        }
    }
    
    for (j = 0; j < number_of_child_nodes_; j++) {
        number = ((abs(rand()) % (max - min + 1)) + min);
        
        if (number > max)
            number = max;
        if (number < min)
            number = min;
        
        bias_weights_[j] = static_cast<double>(number) / 100.0 - 1;
    }
}

void NeuralNetworkLayer::CalculatesErrors()
{
    int i, j;
    double sum;
    
    if (child_layer_ == nullptr) {
        // output layer
        for (i = 0; i < number_of_nodes_; i++) {
            errors_[i] = (desired_values_[i] - neuron_values_[i]) * neuron_values_[i] * (1.0 - neuron_values_[i]);
        }
    } else if (parent_layer_ == nullptr) {
        // input layer
        for (i = 0; i < number_of_nodes_; i++) {
            errors_[i] = 0.0;
        }
    } else {
        // hidden layer
        for (i = 0; i < number_of_nodes_; i++) {
            sum = 0.0;
            for (j = 0; j < number_of_child_nodes_; j++) {
                sum += child_layer_->errors_[j] * weights_[i][j];
            }
            errors_[i] = sum * neuron_values_[i] * (1.0 - neuron_values_[i]);
        }
    }
}

void NeuralNetworkLayer::AdjustWeights()
{
    int i, j;
    double dw;
    
    if (child_layer_) {
        for (i = 0; i < number_of_nodes_; i++) {
            for (j = 0; j < number_of_child_nodes_; j++) {
                dw = leaning_rate_ * child_layer_->errors_[j] * neuron_values_[i];
                weights_[i][j] = dw + momentum_factor_ * weight_changes_[i][j];
                weight_changes_[i][j] = dw;
            }
        }
        
        for (j = 0; j < number_of_child_nodes_; j++) {
            bias_weights_[j] = leaning_rate_ * child_layer_->errors_[j] * bias_values_[j];
        }
    }
}

void NeuralNetworkLayer::CalculateNeuronValues()
{
    int i, j;
    double x;
    
    if (parent_layer_) {
        for (j = 0; j < number_of_nodes_; j++) {
            x = 0.0;
            for (i = 0; i < number_of_parent_nodes_; i++) {
                x += parent_layer_->neuron_values_[i] * parent_layer_->weights_[i][j];
            }
            x += parent_layer_->bias_values_[j] * parent_layer_->bias_weights_[j];
            
            if (!child_layer_ && linear_output_) {
                neuron_values_[j] = x;
            } else {
                neuron_values_[j] = 1.0 / (1.0 * exp(-x));
            }
        }
    }
}
