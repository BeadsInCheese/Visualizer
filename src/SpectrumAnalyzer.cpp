#include "SpectrumAnalyzer.hpp"


const  float pi=3.14;
static std::vector<std::complex<float>> FFT(std::vector<std::complex<float>> &samples){
    int N=samples.size();
    if(N=1){return samples;}
    int M=N/2;
    std::vector<std::complex<float>> Xeven(M,0);
    std::vector<std::complex<float>> Xodd(M,0);
    for(int i=0; i<M; i++){
        Xeven[i]=samples[2*i];
        Xodd[i]=samples[2*i+1];
    }
    std::vector<std::complex<float>> FFTeven(M,0);
    FFTeven=FFT(Xeven);
    std::vector<std::complex<float>> FFTodd(M,0);
    FFTodd=FFT(Xodd);
    std::vector<std::complex<float>> freqBins(N,0);
    for(int k=0; k<N/2;k++){
        std::complex<float> exponential=std::polar(1.0f,-2.0f*pi*k/N)*FFTodd[k];
        freqBins[k]=FFTeven[k]+exponential;
        freqBins[k+N/2]=FFTeven[k]-exponential;
    }
    return freqBins;
}
