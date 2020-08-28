#include <fftw3.h>
#include "Spectrogram.h"
#include "Vector.h"
#include "Window.h"

static constexpr std::uint16_t FFTOutSize = Consts::WinSize / 2 + 1;

Math::Spectrogram::Spectrogram(const std::vector<float> &data) {
    //Calculation of the winFFT size
    std::size_t winFFTsize = ((std::size_t) ((data.size() - Consts::WinSize) / Consts::StepSize)) * Consts::StepSize;
    this->fftWindows.reserve(winFFTsize);

    FFTWindow fftWindow;
    float timeWindow[Consts::WinSize];
    fftwf_complex fftOut[FFTOutSize];

    fftwf_plan p = fftwf_plan_dft_r2c_1d(Consts::WinSize, timeWindow, fftOut, FFTW_ESTIMATE);

    for (std::size_t i = 0; i + Consts::WinSize < data.size(); i += Consts::StepSize) {
        //Multiply the sliding window by the hamming window
        Math::Vector::mul(Window::get().data(), data.data() + i, timeWindow, Consts::WinSize);
        fftwf_execute(p);

        //The first bin in the FFT output is the DC component, get rid of it by starting at fftOut+1
        std::transform(fftOut + 1, fftOut + FFTOutSize, fftWindow.magnitudes.data(),
                       [](const fftwf_complex &i) -> float {
                           return std::sqrt(i[0] * i[0] + i[1] * i[1]);
                       });

        fftWindow.time = (float) i / Consts::SampleRate;
        this->fftWindows.push_back(fftWindow);
    }

    fftwf_destroy_plan(p);
}

Math::FFTWindow Math::Spectrogram::operator[](std::size_t pos) const {
    return this->fftWindows[pos];
}

std::size_t Math::Spectrogram::size() const {
    return this->fftWindows.size();
}
