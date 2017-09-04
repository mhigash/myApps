//
//  neural_network_layer.hpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#ifndef neural_network_layer_hpp
#define neural_network_layer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <vector>
#include <limits>
#include <numeric>
#include <fstream>

class NeuralNetworkLayer {
public:
    
    int number_of_nodes_;
    int number_of_child_nodes_;
    int number_of_parent_nodes_;
    std::vector<std::vector<double>> weights_;
    std::vector<std::vector<double>> weight_changes_;
    std::vector<double> neuron_values_;
    std::vector<double> desired_values_;
    std::vector<double> errors_;
    std::vector<double> bias_weights_;
    std::vector<double> bias_values_;
    double leaning_rate_;
    
    bool linear_output_;
    bool use_momentum_;
    double momentum_factor_;
    
    NeuralNetworkLayer *parent_layer_;
    NeuralNetworkLayer *child_layer_;
    
    NeuralNetworkLayer();
    
    void Initialize(int num_nodes, NeuralNetworkLayer *parent, NeuralNetworkLayer *child);
    void CleanUp();
    void RandomizeWeights();
    void CalculatesErrors();
    void AdjustWeights();
    void CalculateNeuronValues();
};


#endif /* neural_network_layer_hpp */
