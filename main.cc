#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>

// Write little-endian integer helper
void writeInt(std::ofstream &stream, uint32_t value, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        stream.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

int main() {
    const int sampleRate = 44100;   // 44.1kHz
    const int duration = 2;         // 2 seconds
    const int numSamples = sampleRate * duration;
    int frequency = 440;      // A4

    std::ofstream file("sine_raw.wav", std::ios::binary);

    // --- WAV HEADER (44 bytes) ---
    file << "RIFF";                                    // ChunkID
    writeInt(file, 36 + numSamples * 2, 4);            // ChunkSize
    file << "WAVE";                                    // Format

    file << "fmt ";                                    // Subchunk1ID
    writeInt(file, 16, 4);                             // Subchunk1Size (16 for PCM)
    writeInt(file, 1, 2);                              // AudioFormat (1 = PCM)
    writeInt(file, 1, 2);                              // NumChannels
    writeInt(file, sampleRate, 4);                     // SampleRate
    writeInt(file, sampleRate * 2, 4);                 // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
    writeInt(file, 2, 2);                              // BlockAlign (NumChannels * BitsPerSample/8)
    writeInt(file, 16, 2);                             // BitsPerSample

    file << "data";                                    // Subchunk2ID
    writeInt(file, numSamples * 2, 4);                 // Subchunk2Size (NumSamples * NumChannels * BitsPerSample/8)

    // --- AUDIO DATA ---
    for (int t = 0; t < numSamples/2; ++t) {
        double sample = std::sin(2 * M_PI * frequency * t / sampleRate);
        std::cout << frequency<<'\n';
        int16_t intSample = static_cast<int16_t>(sample * 32767);
        writeInt(file, intSample, 2);
    }
frequency = 560;
    for (int t = 0; t < numSamples/2; ++t) {
        double sample = std::sin(2 * M_PI * frequency * t / sampleRate);
        std::cout << frequency<<'\n';
        int16_t intSample = static_cast<int16_t>(sample * 32767);
        writeInt(file, intSample, 2);
    }
    file.close();
    std::cout << "Wrote sine_raw.wav\n";
    return 0;
}

