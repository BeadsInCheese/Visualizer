#include "SpectrumAnalyzer.hpp"

const float pi = 3.14f;

void FFT( std::vector<std::complex<float>>& samples) {

    int n = samples.size();

    // Bit reversal permutation: rearrange the input array.
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1; // The highest bit
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) {
            std::swap(samples[i], samples[j]);
        }
    }

    // Main FFT loop
    for (int len = 2; len <= n; len <<= 1) {
        // Compute the "twiddle factor" for this segment length
        float angle = -2.0f * pi / len;
        std::complex<float> wLen(cos(angle), sin(angle));

        // Process each segment of length 'len'
        for (int i = 0; i < n; i += len) {
            std::complex<float> w(1.0f, 0.0f);
            for (int j = 0; j < len / 2; j++) {
                std::complex<float> u = samples[i + j];
                std::complex<float> v = samples[i + j + len / 2] * w;
                samples[i + j] = u + v;
                samples[i + j + len / 2] = u - v;
                w *= wLen;
            }
        }
    }
}