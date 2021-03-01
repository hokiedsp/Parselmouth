#pragma once

namespace parselmouth {


constexpr auto CLASS_DOCSTRING = R"(Praat PowerCepstrum.

A `parselmouth.Matrix` object contain samples of the power spectrum of the
log power spectrum. When drawn the vertical scale will show the amplitude
expressed in dB. The horizontal scale shows quefrency in units of seconds.
It is calculated from the Spectrum by the method
:func:`parselmouth.Spectrum.to_power_cepstrum`.

See Also
--------
:func:`parselmouth.Spectrum.to_power_cepstrum`
:func:`parselmouth.PowerCepstrogram.to_power_cepstrum`
:func:`parselmouth.Cepstrum.to_power_cepstrum`
)";

constexpr auto GET_PEAK_DOCSTRING =
R"(Get the amplitude of the peak of the power cepstrum over specified range.

Parameters
----------
from_pitch : float, default 60.0
to_pitch : float, default 333.3
    The limits of the quefrency range where a peak is searched for. The
    lower quefrency is determined as 1 / to_pitch and this value is in
    general more critical than the value of the upper quefrency which
    equals 1 / from_pitch. A to_pitch of 300 Hz will correspond to a
    lower quefrency of 1/300≈0.0033 seconds.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC70", "SINC700"},
                default "PARABOLIC"
    Determines how the amplitude and position of a peak are determined.

See also
--------
:praat:`vector peak interpolation`
)";

constexpr auto GET_QUEFRENCY_OF_PEAK_DOCSTRING =
R"(Get the quefrency of the peak of the power cepstrum over specified range.

Parameters
----------
from_pitch : float, default 60.0
to_pitch : float, default 333.3
    The limits of the quefrency range where a peak is searched for. The
    lower quefrency is determined as 1 / to_pitch and this value is in
    general more critical than the value of the upper quefrency which
    equals 1 / from_pitch. A to_pitch of 300 Hz will correspond to a
    lower quefrency of 1/300≈0.0033 seconds.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC70", "SINC700"},
                default "PARABOLIC"
    Determines how the amplitude and position of a peak are determined.

See also
--------
:praat:`vector peak interpolation`
)";

constexpr auto GET_PEAK_PROMINENCE_HILLENBRAND_DOCSTRING =
R"(Compute cepstrum peak prominence measure by Hillenbrand.

The CPP measure is the difference in amplitude between the cepstral peak
and the corresponding value on the trend line that is directly below the
peak (i.e., the predicted magnitude for the quefrency at the cepstral
peak). The CPP measure represents how far the cepstral peak emerges from
the cepstrum background.

Parameters
----------
from_pitch : float, default 60.0
to_pitch : float, default 333.3
    The limits of the quefrency range where a peak is searched for. The
    lower quefrency is determined as 1 / to_pitch and this value is in
    general more critical than the value of the upper quefrency which
    equals 1 / from_pitch. A to_pitch of 300 Hz will correspond to a
    lower quefrency of 1/300≈0.0033 seconds.

See also
--------
:praat:`PowerCepstrum: Get peak prominence...`
:func:`parselmouth.PowerCepstrum.get_peak_prominence` for more customizable
    interface
)";

constexpr auto GET_PEAK_PROMINENCE_DOCSTRING =
R"(Compute cepstrum peak prominence measure.

The CPP measure is the difference in amplitude between the cepstral peak
and the corresponding value on the trend line that is directly below the
peak (i.e., the predicted magnitude for the quefrency at the cepstral
peak). The CPP measure represents how far the cepstral peak emerges from
the cepstrum background.

Parameters
----------
from_pitch : float, default 60.0
to_pitch : float, default 333.3
    The limits of the quefrency range where a peak is searched for. The
    lower quefrency is determined as 1 / to_pitch and this value is in
    general more critical than the value of the upper quefrency which
    equals 1 / from_pitch. A to_pitch of 300 Hz will correspond to a
    lower quefrency of 1/300≈0.0033 seconds.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC70", "SINC700"},
                default "PARABOLIC"
    Determines how the amplitude and position of a peak are determined.

left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

See also
--------
:praat:`PowerCepstrum: Get peak prominence...`
:praat:`vector peak interpolation`
:praat:`theil regression`
:func:`parselmouth.PowerCepstrum.get_peak_prominence_hillenbrand` for the
    original Hillenbrand's algorithm
)";

constexpr auto GET_RHAMONICS_TO_NOISE_RATIO_DOCSTRING =
R"(Get Rhamonics-to-Noise Ratio measure.

from_pitch : float, default 60.0
to_pitch : float, default 333.3
    The limits of the quefrency range where a peak is searched for. The
    lower quefrency is determined as 1 / to_pitch and this value is in
    general more critical than the value of the upper quefrency which
    equals 1 / from_pitch. A to_pitch of 300 Hz will correspond to a
    lower quefrency of 1/300≈0.0033 seconds.

fractional_width : float, default 0.05
    TBD
)";

constexpr auto GET_TREND_LINE_SLOPE_DOCSTRING =
R"(Calculate the slope of the line that models the cepstrum background.

Parameters
----------
left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

See also
--------
:praat:`PowerCepstrum: Get trend line slope...`
:praat:`theil regression`
:func:`PowerCepstrum.get_trend_line_intercept`
)";

constexpr auto GET_TREND_LINE_INTERCEPT_DOCSTRING =
R"(Calculate the intercept  of the line that models the cepstrum background.

Parameters
----------
left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

See also
--------
:praat:`PowerCepstrum: Get trend line intercept...`
:praat:`theil regression`
:func:`PowerCepstrum.get_trend_line_slope`
)";

constexpr auto GET_TREND_LINE_DOCSTRING =
R"(Calculate both the slope and intercept of the line that models the
cepstrum background.

This function combines `get_trend_line_slope` and
`get_trend_line_intercept` methods for convenience and efficiency.

Parameters
----------
left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

Returns
-------
(slope, intercept) : tuple of float


See also
--------
:praat:`PowerCepstrum: Get trend line slope...`
:praat:`PowerCepstrum: Get trend line intercept...`
:praat:`theil regression`
:func:`PowerCepstrum.get_trend_line_slope`
:func:`PowerCepstrum.get_trend_line_intercept`)";

constexpr auto SUBTRACT_TREND_DOCSTRING =
R"(Create a new PowerCepstrum object, which is a copy of the current after
subtraction of the cepstrum trend.

Parameters
----------
left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

Returns
-------
parselmouth.PowerCepstrum


See also
--------
:praat:`PowerCepstrum: Subtract trend...`
:praat:`theil regression`
)";

constexpr auto SUBTRACT_TREND_INPLACE_DOCSTRING =
R"(Subtract the cepstrum trend.

This operation modifies the calling PowerCepstrum object.

Parameters
----------
left_trend_line_quefrency_range : float, default 0.001
right_trend_line_quefrency_range : float, default 0.05
    Quefrency range for which the amplitudes (in dB) will be modelled by a
    straight line.

line_type : {"STRAIGHT", "EXPONENTIAL_DECAY"}, default "EXPONENTIAL_DECAY"
    How to model the cepstrum background. "STRAIGHT" models it with a
    straight line as was done in Hillenbrand et al. (1994). The slope of
    this line will generally be negative because the background amplitudes
    get weaker for higher quefrencies. "EXPONENTIAL_DECAY" model allows the
    background cepstral amplitudes decay in a non-linear fashion.

fit_method : {"ROBUST", "LEAST_SQUARES", "ROBUST_SLOW"},
             default "ROBUST_SLOW"
    How the line that models the cepstrum background is calculated.
    "ROBUST_SLOW" uses Theil's robust line fit. "ROBUST" method uses the
    incomplete Theil regression and is computationally faster but somewhat
    less precise. "LEAST_SQUARES" is a standard least squares line fit but
    it is much less precise than the other two because a least squares fit
    is much more influenced by the peak cepstral values than the other two.

See also
--------
:praat:`PowerCepstrum: Subtract trend...`
:praat:`theil regression`
)";

constexpr auto SMOOTH_DOCSTRING =
R"(Create a smooth version of the PowerCepstrum object by averaging values at
successive quefrencies.

Parameters
----------
quefrency_averaging_window : float, default 0.0005
    Width of the averaging window in the quefrency domain. By chosing a
    value smaller than the quefrency distance, you can prevent any
    smoothing in the quefrency dimension.

number_of_iterations : int, default 1
    How often the averaging will take place. If chosen 2, for example, the
    output PowerCepstrum after the first averaging will be averaged once
    again.

Returns
-------
parselmouth.PowerCepstrum

See also
--------
:praat:`PowerCepstrum: Smooth...`
:func:`PowerCepstrum.smooth_inplace`
)";

constexpr auto SMOOTH_INPLACE_DOCSTRING =
R"(Smooth the PowerCepstrum object by averaging values at successive
quefrencies.

This operation modifies the calling PowerCepstrum object.

Parameters
----------
quefrency_averaging_window : float, default 0.0005
    Width of the averaging window in the quefrency domain. By chosing a
    value smaller than the quefrency distance, you can prevent any
    smoothing in the quefrency dimension.

number_of_iterations : int, default 1
    How often the averaging will take place. If chosen 2, for example, the
    output PowerCepstrum after the first averaging will be averaged once
    again.

See also
--------
:praat:`PowerCepstrum: Smooth...`
:func:`PowerCepstrum.smooth`
)";


}// namespace parselmouth