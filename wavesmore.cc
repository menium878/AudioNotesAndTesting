#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <vector>

// Write little-endian integer helper
void writeInt(std::ofstream &stream, uint32_t value, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        stream.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

int main() {
    const int sampleRate = 44100;
    const double durationPerNote = 1.0; // 1 second per note
    const int bitsPerSample = 16;
    const int numChannels = 1;

    // C major scale frequencies (C4 -> C5)
    std::vector<double> noteFrequencies = {261.63, 293.66, 329.63, 349.23,
                                           392.00, 440.00, 493.88, 523.25};

    int samplesPerNote = static_cast<int>(durationPerNote * sampleRate);
    int totalSamples = samplesPerNote * noteFrequencies.size();

    std::ofstream file("scale_sweep.wav", std::ios::binary);

    // --- WAV HEADER ---
    file << "RIFF";
    writeInt(file, 36 + totalSamples * 2, 4);  // ChunkSize
    file << "WAVE";

    file << "fmt ";
    writeInt(file, 16, 4);                      // Subchunk1Size
    writeInt(file, 1, 2);                       // AudioFormat = PCM
    writeInt(file, numChannels, 2);             // NumChannels
    writeInt(file, sampleRate, 4);              // SampleRate
    writeInt(file, sampleRate * numChannels * bitsPerSample / 8, 4); // ByteRate
    writeInt(file, numChannels * bitsPerSample / 8, 2);              // BlockAlign
    writeInt(file, bitsPerSample, 2);          // BitsPerSample

    file << "data";
    writeInt(file, totalSamples * 2, 4);        // Subchunk2Size

    // --- AUDIO DATA ---
    double phase = 0.0;

    for (size_t n = 0; n < noteFrequencies.size(); ++n) {
        double startFreq = noteFrequencies[n];
        double endFreq = (n + 1 < noteFrequencies.size()) ? noteFrequencies[n + 1] : startFreq;

        for (int t = 0; t < samplesPerNote; ++t) {
            // linear sweep from startFreq -> endFreq
            double freq = startFreq + (endFreq - startFreq) * t / samplesPerNote;
            double sample = sin(phase);
            phase += 2 * M_PI * freq / sampleRate;
            if (phase >= 2 * M_PI) phase -= 2 * M_PI;

            int16_t intSample = static_cast<int16_t>(sample * 32767);
            writeInt(file, intSample, 2);
        }
    }

    file.close();
    std::cout << "Wrote scale_sweep.wav\n";
    return 0;
}

