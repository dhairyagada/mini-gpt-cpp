//
// Created by Dhairya Gada on 19.09.26.
//

#pragma once

#include <cstdint>

namespace gpt{
    // Initialize the parameters, to store the knowledge of the model
    constexpr static size_t N_LAYER = 1 ;                               //depth of the transformer neural network (number of layers)
    constexpr static size_t N_EMBD = 16;                                //width of the network (embedding dimension)
    constexpr static size_t BLOCK_SIZE = 16;                            //maximum context length of the attention window (note: the longest name is 15 characters)
    constexpr static size_t N_HEAD = 4;                                 //number of attention heads
    constexpr static size_t HEAD_DIM = N_EMBD / N_HEAD ;                //derived dimension of each head
}
