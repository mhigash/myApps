//
//  neural_network.cpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#include "neural_network.hpp"

NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::Initialize(int nodes_input, int nodes_hidden, int nodes_output)
{
    input_layer_.number_of_nodes_ = nodes_input;
    input_layer_.number_of_child_nodes_ = nodes_hidden;
    input_layer_.number_of_parent_nodes_ = 0;
    input_layer_.Initialize(nodes_input, nullptr, &hidden_layer_);
    input_layer_.RandomizeWeights();

    hidden_layer_.number_of_nodes_ = nodes_hidden;
    hidden_layer_.number_of_child_nodes_ = nodes_output;
    hidden_layer_.number_of_parent_nodes_ = nodes_input;
    hidden_layer_.Initialize(nodes_hidden, &input_layer_, &output_layer_);
    hidden_layer_.RandomizeWeights();
    
    output_layer_.number_of_nodes_ = nodes_output;
    output_layer_.number_of_child_nodes_ = 0;
    output_layer_.number_of_parent_nodes_ = nodes_hidden;
    output_layer_.Initialize(nodes_output, &hidden_layer_, nullptr);
}

void NeuralNetwork::ClearnUp()
{
    input_layer_.CleanUp();
    hidden_layer_.CleanUp();
    output_layer_.CleanUp();
}

void NeuralNetwork::SetInput(int i, double value)
{
    if (i < 0) return;
    if (i >= input_layer_.number_of_nodes_) return;
    input_layer_.neuron_values_[i] = value;
}

double NeuralNetwork::GetOutput(int i)
{
    double error = std::numeric_limits<double>::max();
    if (i < 0) return error;
    if (i >= output_layer_.number_of_nodes_) return error;
    return output_layer_.neuron_values_[i];
}

void NeuralNetwork::SetDesiredOutput(int i, double value)
{
    if (i < 0) return;
    if (i >= output_layer_.number_of_nodes_) return;
    output_layer_.desired_values_[i] = value;
}

void NeuralNetwork::FeedForward()
{
    input_layer_.CalculateNeuronValues();
    hidden_layer_.CalculateNeuronValues();
    output_layer_.CalculateNeuronValues();
}

void NeuralNetwork::BackPropagate()
{
    output_layer_.CalculatesErrors();
    hidden_layer_.CalculatesErrors();
    
    hidden_layer_.AdjustWeights();
    input_layer_.AdjustWeights();
}

int NeuralNetwork::GetMaxOutputId()
{
    int i, id;
    double max_value;
    
    max_value = output_layer_.neuron_values_[0];
    
    for (i = 1; i < output_layer_.number_of_nodes_; i++) {
        if (output_layer_.neuron_values_[i] > max_value) {
            max_value = output_layer_.neuron_values_[i];
            id = i;
        }
    }
    return id;
}

double NeuralNetwork::CaluculateError()
{
    int i;
    double error = 0.0;
    
    for (i = 0; i < output_layer_.number_of_nodes_; i++) {
        error += powf(output_layer_.neuron_values_[i] - output_layer_.desired_values_[i], 2);
    }
    
    error /= output_layer_.number_of_nodes_;
    return error;
}

void NeuralNetwork::SetLearningRate(double rate)
{
    input_layer_.leaning_rate_ = rate;
    hidden_layer_.leaning_rate_ = rate;
    output_layer_.leaning_rate_ = rate;
}

void NeuralNetwork::SetLinearOutput(bool use_linear)
{
    input_layer_.linear_output_ = use_linear;
    hidden_layer_.linear_output_ = use_linear;
    output_layer_.linear_output_ = use_linear;
}

void NeuralNetwork::SetMomentum(bool use_momentum, double factor)
{
    input_layer_.use_momentum_ = use_momentum;
    hidden_layer_.use_momentum_ = use_momentum;
    output_layer_.use_momentum_ = use_momentum;
    
    input_layer_.momentum_factor_ = factor;
    hidden_layer_.momentum_factor_ = factor;
    output_layer_.momentum_factor_ = factor;
}

void NeuralNetwork::DumpData(const char *filename)
{
    std::ofstream f(filename);
    
    f << "--------------------------------------------------" << std::endl;
    f << "Input Layer" << std::endl;
    f << "--------------------------------------------------" << std::endl;
    
    f << "Node Values: " << std::endl;
    for (int i = 0; i < input_layer_.number_of_nodes_; i++) {
        f << "(" << i << ") = " << input_layer_.neuron_values_[i] << std::endl;
    }
    
    f << "Weights: " << std::endl;
    for (int i = 0; i < input_layer_.number_of_nodes_; i++) {
        for (int j = 0; j < input_layer_.number_of_child_nodes_; j++) {
            f << "(" << i << "," << j << ") = " << input_layer_.weights_[i][j] << std::endl;
        }
    }
    
    f << "Bias Weights: " << std::endl;
    for (int i = 0; i < input_layer_.number_of_child_nodes_; i++) {
        f << "(" << i << ") = " << input_layer_.bias_weights_[i] << std::endl;
    }
    
    f << "--------------------------------------------------" << std::endl;
    f << "Hidden Layer" << std::endl;
    f << "--------------------------------------------------" << std::endl;
    
    f << "Weights: " << std::endl;
    for (int i = 0; i < hidden_layer_.number_of_nodes_; i++) {
        for (int j = 0; j < hidden_layer_.number_of_child_nodes_; j++) {
            f << "(" << i << "," << j << ") = " << hidden_layer_.weights_[i][j] << std::endl;
        }
    }
    
    f << "Bias Weights: " << std::endl;
    for (int i = 0; i < hidden_layer_.number_of_child_nodes_; i++) {
        f << "(" << i << ") = " << hidden_layer_.bias_weights_[i] << std::endl;
    }
    
    f << "--------------------------------------------------" << std::endl;
    f << "Output Layer" << std::endl;
    f << "--------------------------------------------------" << std::endl;
    
    f << "Node Values: " << std::endl;
    for (int i = 0; i < output_layer_.number_of_nodes_; i++) {
        f << "(" << i << ") = " << output_layer_.neuron_values_[i] << std::endl;
    }
    
}
