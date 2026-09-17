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
        using decodedType = ENCODED_TYPE;

        ENCODED_TYPE encoded;
        DECODED_TYPE decoded;
    };

    using asciiToken = Token<std::uint8_t, char>;


   struct AsciiTokenizer {
       std::vector<asciiToken> tokens = std::vector<asciiToken>();

       void createToken(const asciiToken::decodedType decoded) {
           const auto it = std::ranges::find_if(tokens, [&decoded](asciiToken& a) {
               return a.decoded == decoded;
           });

           if (it == tokens.end()) {
               tokens.emplace_back(static_cast<asciiToken::encodedType>(decoded),decoded);
           }
       }

       // Encoded Value is the Model Friendly Value
       asciiToken::encodedType getEncodedValue(asciiToken::decodedType decoded) {

           const auto it = std::ranges::find_if(tokens, [&decoded](asciiToken& a) {
               return a.decoded == decoded;
           });

           if (it != tokens.end()) {
               return it->encoded;
           }

           return 0;
       }

       // Decoded Value is the Human Friendly Value
       asciiToken::decodedType getDecodedValue(asciiToken::encodedType encoded) {

           const auto it = std::ranges::find_if(tokens, [&encoded](asciiToken& a) {
               return a.encoded == encoded;
           });

           if (it != tokens.end()) {
               return it->decoded;
           }

           return '\0';
       }

       static AsciiTokenizer createAsciiTokenizerFromString(const std::string_view str) {
           AsciiTokenizer tokenizer{};
            for (const auto c : str) {
                tokenizer.createToken(c);
            }
            return tokenizer;
       }
   };

}

#endif //MINI_GPT_TOKENIZER_H
