#pragma once

namespace parselmouth {


constexpr auto CLASS_DOCSTRING = R"(Praat Cepstrum.

A sequence object contain samples of a cepstrum, which is the log spectrum
of the log power spectrum.

This class is not intended to be user intantiatable. Use `to_cepstrum`
methods of :obj:`parselmouth.Sound` and :obj:`parselmouth.Spectrum` objects
to create one.

See Also
--------
:praat:`Cepstrum`
:func:`parselmouth.Sound.to_cepstrum`
:func:`parselmouth.Spectrum.to_cepstrum`
)";

constexpr auto TO_SPECTRUM_DOCSTRING = R"(Compute :obj:`parselmouth.Spectrum` object from this Cepstrum.)";

constexpr auto TO_SOUND_DOCSTRING = R"(Compute :obj:`parselmouth.Sound` object from this Cepstrum.)";

constexpr auto TO_POWER_CEPSTRUM_DOCSTRING = R"(Compute :obj:`parselmouth.PowerCepstrum` object from this Cepstrum.)";

}// namespace parselmouth