//
//  neural_network.hpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#ifndef neural_network_hpp
#define neural_network_hpp

#include "neural_network_layer.hpp"

class NeuralNetwork {
public:
    NeuralNetworkLayer input_layer_;
    NeuralNetworkLayer hidden_layer_;
    NeuralNetworkLayer output_layer_;

    NeuralNetwork();
    void Initialize(int nodes_input, int nodes_hidden, int nodes_output);
    void ClearnUp();
    void SetInput(int i, double value);
    double GetOutput(int i);
    void SetDesiredOutput(int i, double value);
    void FeedForward();
    void BackPropagate();
    int GetMaxOutputId();
    double CaluculateError();
    void SetLearningRate(double rate);
    void SetLinearOutput(bool use_linear);
    void SetMomentum(bool use_momentum, double factor);
    void DumpData(const char *filename);
};

#endif /* neural_network_hpp */
