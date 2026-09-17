//
// Created by Dhairya Gada on 17.09.26.
//

#ifndef MINI_GPT_TOKENIZER_H
#define MINI_GPT_TOKENIZER_H
#include <algorithm>
#include <cstdint>
#include <vector>

namespace mini_gpt {

    template <typename ENCODED_TYPE, typename DECODED_TYPE>
    struct Token {

        using encodedType = ENCODED_TYPE;
        using decodedType = DECODED_TYPE;

        ENCODED_TYPE encoded;
        DECODED_TYPE decoded;
    };

    using denseToken = Token<std::uint8_t, char>;


   struct DenseTokenizer {
       using ENCODED_TYPE = denseToken::encodedType;

       std::vector<denseToken> tokens = std::vector<denseToken>();
       static constexpr denseToken::encodedType ENCODED_VALUE_DEFAULT = 0;
       static constexpr denseToken::decodedType DECODED_VALUE_DEFAULT = '\0';

       DenseTokenizer() {
           tokens.emplace_back(ENCODED_VALUE_DEFAULT,DECODED_VALUE_DEFAULT);
       }

       void createToken(const denseToken::decodedType decoded) {
           const auto it = std::ranges::find_if(tokens, [&decoded](denseToken& a) {
               return a.decoded == decoded;
           });

           if (it == tokens.end()) {
               tokens.emplace_back(tokens.size(),decoded);
           }
       }

       // Encoded Value is the Model Friendly Value
       denseToken::encodedType getEncodedValue(denseToken::decodedType decoded) {

           const auto it = std::ranges::find_if(tokens, [&decoded](denseToken& a) {
               return a.decoded == decoded;
           });

           if (it != tokens.end()) {
               return it->encoded;
           }

           return ENCODED_VALUE_DEFAULT;
       }

       // Decoded Value is the Human Friendly Value
       denseToken::decodedType getDecodedValue(denseToken::encodedType encoded) {

           const auto it = std::ranges::find_if(tokens, [&encoded](denseToken& a) {
               return a.encoded == encoded;
           });

           if (it != tokens.end()) {
               return it->decoded;
           }

           return DECODED_VALUE_DEFAULT;
       }

       static DenseTokenizer createDenseTokenFromString(const std::string_view str) {
           DenseTokenizer tokenizer{};
            for (const auto c : str) {
                tokenizer.createToken(c);
            }
            return tokenizer;
       }
   };

    struct DenseTokeniserVocabulary {
        DenseTokenizer tokenizer;
        DenseTokenizer::ENCODED_TYPE bosToken;
        size_t vocabularySize{0};

        explicit DenseTokeniserVocabulary(DenseTokenizer&& _tokenizer) : tokenizer(_tokenizer) {
            bosToken = tokenizer.tokens.size() + 1;
            vocabularySize = tokenizer.tokens.size() + 1;
        }
    };

}

#endif //MINI_GPT_TOKENIZER_H
