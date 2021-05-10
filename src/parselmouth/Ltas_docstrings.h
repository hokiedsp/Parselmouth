namespace parselmouth
{

    constexpr auto CREATE_CLASS_DOCSTRING = R"(Praat Ltas.

A sequence object containing long-term average spectrum (LTAS) which
represents the logarithmic power spectral density as a function of
frequency, expressed in dB/Hz relative to :math:`2 \times 10^{-5}` Pa.



See Also
--------
:praat:`Ltas`
:func:`parselmouth.Sound.to_ltas`
:func:`parselmouth.Sound.to_ltas_pitch_corrected`
:func:`parselmouth.Spectrum.to_ltas`
:func:`parselmouth.PointProcess.to_ltas`
:func:`parselmouth.PointProcess.to_ltas_harmonics`
)";

    constexpr auto COMPUTE_TREND_LINE_DOCSTRING =
R"(Compute a fitted linear LTAS.

Returns a new Ltas instance, which is a linearized version of the calling
Ltas object. Over the specified frequency range, the original LTAS samples
are replaced by a line, which is estimated from the original samples.

Parameters
----------
from_frequency : float, default 600.0
    Starting frequency in Hz to peform the linearization
to_frequency : float, default 4000.0
    Ending frequency in Hz to perform the linearization

See Also
--------
:obj:`parselmouth.Ltas`
)";

    constexpr auto GET_LOWEST_FREQUENCY_DOCSTRING =
        R"(Returns the lowest frequency in Hz.

See Also
--------
:praat:`Ltas: Get lowest frequency`
)";

    constexpr auto GET_HIGHEST_FREQUENCY_DOCSTRING =
        R"(Returns the highest frequency in Hz.

See Also
--------
:praat:`Ltas: Get highest frequency`
)";

    constexpr auto GET_BIN_WIDTH_DOCSTRING =
R"(Returns the the with of a bin in Hz.

See Also
--------
:praat:`Ltas: Get bin width`
)";

    constexpr auto GET_FREQUENCY_FROM_BIN_NUMBER_DOCSTRING =
        R"(Get the frequency associated with the specified bin number.

    :math:`f_1 + (bin_number - 1) \Delta f`

where :math:`f_1` is the frequency associated with the centre of the first
bin, and :math:`\Delta f` is the bin width.

Parameters
----------
bin_number : int
    Index (1-based) of the requested frequency bin.

See Also
--------
:praat:`Ltas: Get frequency from bin number...`
)";

    constexpr auto GET_BAND_FROM_FREQUENCY_DOCSTRING =
R"(Get the fractional bin number of the specified frequency.

Parameters
----------
frequency : float
    Queried frequency in Hz

Returns
-------
float
    Fractional bin number.

See Also
--------
:praat:`Ltas: Get bin number from frequency...`
)";

    constexpr auto GET_FREQUENCY_OF_MINIMUM_DOCSTRING =
R"(Get the frequency in Hz associated with the minimum energy density.

Parameters
----------

from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC"}, default "NONE"
    Interpolation method of the vector peak interpolation.

See Also
--------
:praat:`Ltas: Get frequency of minimum...`
)";

    constexpr auto GET_FREQUENCY_OF_MAXIMUM_DOCSTRING =
R"(Get the frequency in Hz associated with the maximum energy density.

Parameters
----------

from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC"}, default "NONE"
    Interpolation method of the vector peak interpolation.

See Also
--------
:praat:`Ltas: Get frequency of maximum...`
)";

    constexpr auto GET_LOCAL_PEAK_HEIGHT_DOCSTRING =
        R"(Get the intensity of a local peak in specified units.

Parameters
----------
from_frequency, to_frequency : float
    Frequency range (from_frequency, to_frequency).

left_peak, right_peak : float
    TBD

intensity_units : {"ENERGY", "SONES", "DB"}, default "ENERGY"
    Units of the return value

)";

    constexpr auto GET_MAXIMUM_DOCSTRING =
R"(Get the maximum value in dB within a specified frequency range.

Parameters
----------
from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC"}, default "NONE"
    Interpolation method of the vector peak interpolation.

See Also
--------
:praat:`Ltas: Get maximum...`
)";

    constexpr auto GET_MINIMUM_DOCSTRING =
R"(Get the minimum value in dB within a specified frequency range.

Parameters
----------
from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC"}, default "NONE"
    Interpolation method of the vector peak interpolation.

See Also
--------
:praat:`Ltas: Get minimum...`
)";

    constexpr auto GET_MEAN_DOCSTRING =
        R"(Get the mean value in dB within a specified frequency range.

Parameters
----------
from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

intensity_units : {"ENERGY", "SONES", "DB"}, default "ENERGY"
    Units of the return value

See Also
--------
:praat:`Ltas: Get mean...`
)";

    constexpr auto GET_NUMBER_OF_BINS_DOCSTRING =
        R"(Get the total number of frequency bins.

See Also
--------
:praat:`Ltas: Get number of bins`
)";

    constexpr auto GET_SLOPE_DOCSTRING =
        R"(Get the spectral slope.

TBD

Parameters
----------
left_low_band, right_low_band : float
    Lower frequency range (left_low_band, right_low_band)? TBD

left_high_band, right_high_band : float
    Upper frequency range (left_low_band, right_low_band)? TBD

intensity_units : {"ENERGY", "SONES", "DB"}, default "ENERGY"
    Units of the return value

)";

    constexpr auto GET_STANDARD_DEVIATION_DOCSTRING =
R"(Get the standard deviation in dB within a specified frequency range.

Parameters
----------
from_frequency, to_frequency : float, default 0.0
    Frequency range (from_frequency, to_frequency). Values outside this
    range are ignored. If from_frequency is not less than to_frequency, the
    entire frequency domain of the LTAS is considered.

intensity_units : {"ENERGY", "SONES", "DB"}, default "ENERGY"
    Units of the return value

See Also
--------
:praat:`Ltas: Get standard deviation...`
)";

    constexpr auto GET_VALUE_DOCSTRING =
        R"(Get 5-point APQ.

Returns the five-point Amplitude Perturbation Quotient, the average
absolute difference between the amplitude of a period and the average of
the amplitudes of it and its four closest neighbours, divided by the
average amplitude.

Parameters
----------
frequency : float
    Frequency in Hz at which the value is to be evaluated.

Interpolation : {"NEAREST", "LINEAR", "CUBIC", "SINC70", "SINC700"},
                default "NEAREST"
    Interpolation method.

See Also
--------
:praat:`Ltas: Get value at frequency...`
:praat:`vector value interpolation`
)";

    constexpr auto GET_VALUE_IN_BIN_DOCSTRING =
        R"(Get the LTAS value in dB in a specified bin. If the bin number
is less than 1 or greater than the number of bin, the result is 0.

Parameters
----------
bin_number : int
    1-based index of the bin to be looked up

See Also
--------
:praat:`Ltas: Get value in bin...`
)";

    constexpr auto SUBTRACT_TREND_LINE_DOCSTRING =
        R"(Subtract trendline over specified frequency range.

Parameters
----------
from_frequency, to_frequency : float
    Frequency range (from_frequency, to_frequency).

Returns
`parselmouth.Ltas`
    A copy of Ltas object with the trendline subtracted over the specified
    frequency range

)";

} // namespace parselmouth
