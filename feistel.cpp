#include <cstdint>
#include <functional>

class FeistelNetwork {
private:
    const size_t ROUNDS;
    std::function<std::uint8_t(std::uint8_t, std::uint8_t)> SBox; // substitution function

    // Returns the 8 MSBs of the 16 bit value.
    static constexpr std::uint8_t MSB8(const std::uint16_t val) noexcept {
        return static_cast<std::uint8_t>(val >> 8); 
    }

    // Returns the 8 LSBs of the 16-bit argument.
    static constexpr std::uint8_t LSB8(const std::uint16_t val) noexcept {
        return static_cast<std::uint8_t>(val & 0xFFu);
    }

    // Joins two 8-bit values into a 16-bit value.
    static constexpr std::uint16_t join(const std::uint8_t msb, const std::uint8_t lsb) noexcept {
        return (static_cast<std::uint16_t>(msb) << 8) | static_cast<uint16_t>(lsb);
    }

public:
    explicit FeistelNetwork(unsigned int rounds, std::function<std::uint8_t(std::uint8_t, std::uint8_t)> sbox) 
    : ROUNDS(rounds), SBox(sbox) {}

    // Encrypts the given plaintext with the given key. Returns the ciphertext.
    std::uint16_t encrypt(std::uint16_t plaintext, std::uint8_t key) const {
        std::uint8_t left = MSB8(plaintext);
        std::uint8_t right = LSB8(plaintext);

        for (size_t round = 0; round < ROUNDS; round++) {

            // Compute L_i+1 and R_i+1
            std::uint8_t left_next = right;
            std::uint8_t right_next = SBox(right, key) ^ left;

            // Assign new L and R
            left = left_next;
            right = right_next;
        }

        return join(left, right);
    }

    std::uint16_t decrypt(std::uint16_t ciphertext, std::uint8_t key) const {
        std::uint8_t left = MSB8(ciphertext);
        std::uint8_t right = LSB8(ciphertext);

        for (size_t round = 0; round < ROUNDS; round++) {

            // Compute L_i-1 and R_i-1 (starting with L_n and R_n)
            std::uint8_t right_prev = left;
            std::uint8_t left_prev = SBox(left, key) ^ right;
            
            // Assign new L and R
            left = left_prev;
            right = right_prev;
        }

        return join(left, right);
    }

};