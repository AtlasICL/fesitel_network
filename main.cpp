#include "feistel.cpp"

#include <cstdint>
#include <functional>
#include <iostream>

// Example substitution function. In this case, bitwise AND.
std::uint8_t substitutionFunction(const std::uint8_t block, const std::uint8_t key) {
    return block & key;
}

int main() {

    FeistelNetwork FeistelCodec = FeistelNetwork(16, substitutionFunction);

    const std::uint16_t plaintext = 12345;
    const std::uint8_t key = 92;

    const std::uint16_t ciphertext = FeistelCodec.encrypt(plaintext, key);
    std::cout << "-- Encrypting " << plaintext << " with key " << (int)key << " -- \n";
    std::cout << "Generated ciphertext: " << ciphertext << std::endl;

    const std::uint16_t retrieved_plaintext = FeistelCodec.decrypt(ciphertext, key);
    std::cout << "-- Decrypting " << ciphertext << " with key " << (int)key << " -- \n";
    std::cout << "Retrieved plaintext: " << retrieved_plaintext << std::endl;
}