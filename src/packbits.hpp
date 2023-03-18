#include <vector>

namespace packbits {
    /**
     * Packs a vector of bytes using the PackBits algorithm.
     */
    extern std::vector<uint8_t> pack(const std::vector<uint8_t> &bytes) {
        std::vector<uint8_t> packedBytes (0);

        unsigned int runLength = 0u;
        unsigned int nonRunLength = 0u;

        for (unsigned int i = 1u; i < bytes.size(); ++i) {
            const uint8_t prev = bytes[i - 1];
            const uint8_t curr = bytes[i];
            if (prev == curr) {
                if (nonRunLength != 0u) {
                    // first repeat of a character, so write out the non-run data
                    packedBytes.push_back(nonRunLength - 1u);
                    packedBytes.insert(packedBytes.end(), bytes.begin() + i - nonRunLength - 1u, bytes.begin() + i - 1u);
                    nonRunLength = 0u;
                }
                ++runLength;
                if (runLength == 128u) {
                    // run is full, so write it out
                    packedBytes.push_back(257u - runLength);
                    packedBytes.push_back(curr);
                    runLength = 0u;
                }
            }
            else {
                if (runLength != 0u) {
                    // first non-repeat of a character, so write out the run data
                    packedBytes.push_back( 256u - runLength);
                    packedBytes.push_back(prev);
                    runLength = 0u;
                } else {
                    ++nonRunLength;
                }
                if (nonRunLength == 128u) {
                    // non-run is full, so write it out
                    packedBytes.push_back(nonRunLength - 1u);
                    packedBytes.insert(packedBytes.end(), bytes.begin() + i - nonRunLength, bytes.begin() + i);
                    nonRunLength = 0u;
                }
            }
        }


        // write out any remaining data
        if (runLength != 0u) { // should just be one byte left
            packedBytes.push_back(256u - runLength);
            packedBytes.push_back(bytes.back());
        } else {
            ++nonRunLength;
            packedBytes.push_back(nonRunLength - 1u);
            packedBytes.insert(packedBytes.end(), bytes.end() - nonRunLength, bytes.end());
        }
        return packedBytes;
    }



    /**
     * Unpacks a vector of bytes using the PackBits algorithm.
     */
    extern std::vector<uint8_t> unpack(const std::vector<uint8_t> &bytes) {
        std::vector<uint8_t> unpackedBytes (0);
        unsigned int index = 0;

        while (index < bytes.size()) {
            uint8_t byte = bytes[index++];
            if (byte >= 0u && byte <= 127u) {
                uint8_t literalCount = byte + 1;
                for (uint8_t i = 0; i < literalCount; i++) {
                    unpackedBytes.push_back(bytes[index++]);
                }
            } else if (byte >= 129u && byte <= 255 ) {
                uint8_t byteToRepeat = bytes[index++];
                uint8_t repeatCount = 257u - byte;
                for (uint8_t i = 0; i < repeatCount; i++) {
                    unpackedBytes.push_back(byteToRepeat);
                }
            }
        }
        return unpackedBytes;
    }
}