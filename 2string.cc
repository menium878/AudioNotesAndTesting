#include <cstdint>
#include <fstream>
#include <vector>
void writeInt(std::ofstream &stream, uint32_t value, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        stream.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

int main() {
    const int sampleRate = 44100;
    const double durationPerNote = 1.0;
    const int bitsPerSample = 16; // <- bitdepth
    const int numChannels = 1;

    std::vector<double> noteFrequencies = {261.63, 293.66, 329.63, 349.23,
                                           392.00, 440.00, 493.88, 523.25};


}
