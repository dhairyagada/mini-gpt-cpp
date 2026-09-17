//
// Created by Dhairya Gada on 14.09.26.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

#include "Tokenizer.h"


static constexpr std::string_view PROPERTIES_FILE = "../conf.properties";
static constexpr std::string DATA_FILE = "../data.txt";

static std::string getTrainingData() {
    std::ifstream ifs(DATA_FILE);

    if (!ifs) {
        return "";
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    return buffer.str();
}

namespace {
    template <typename ENCODED_TYPE, typename DECODED_TYPE>
    struct Token {
        ENCODED_TYPE encoded;
        DECODED_TYPE decoded;
    };
}

int main() {

    const std::string content{getTrainingData()};
    mini_gpt::AsciiTokenizer x = mini_gpt::AsciiTokenizer::createAsciiTokenizerFromString(content);

    return 0;
}