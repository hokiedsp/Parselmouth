#pragma once

namespace parselmouth {


constexpr auto CLASS_DOCSTRING = R"(Praat PowerCepstrogram.

A `parselmouth.Matrix` object contain a cepstrogram, which represents a
time-quefrency representation of a sound. The class object are created via
`paselmouth.Sound` object with the method
:func:`parselmouth.Spectrum.to_power_cepstrogram`.

See Also
--------
:praat:`PowerCepstrogram`
:praat:`Sound: To PowerCepstrogram...`
:func:`parselmouth.Sound.to_power_cepstrogram`
)";

constexpr auto SMOOTH_DOCSTRING =
R"(Smoothes the PowerCepstrogram by averaging with a rectangular window.

The smoothed PowerCepstrogram is the result of two separate steps. In the
first step, cepstra are averaged across time. In the second step, cepstra
are averaged across quefrency.

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
parselmouth.PowerCepstrogram :
    Modified PowerCepstrogram

See also
--------
:praat:`PowerCepstrogram: Smooth...`
)";

constexpr auto GET_START_QUEFRENCY_DOCSTRING =
R"(Returns the starting quefrency in seconds)";

constexpr auto GET_END_QUEFRENCY_DOCSTRING =
R"(Returns the ending quefrency in seconds)";

constexpr auto GET_NUMBER_OF_QUEFRENCY_BINS_DOCSTRING =
R"(Returns the number of quefrency bins)";

constexpr auto GET_QUEFRENCY_STEP_DOCSTRING =
R"(Returns the separation between two successive quefrency bins)";

constexpr auto SUBTRACT_TREND_DOCSTRING =
R"(Create a new PowerCepstrogram object, which is a copy of the current after
subtraction of the cepstrum trend of each frame.

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
parselmouth.PowerCepstrogram


See also
--------
:praat:`PowerCepstrum: Subtract trend...`
:praat:`theil regression`
)";

constexpr auto SUBTRACT_TREND_INPLACE_DOCSTRING =
R"(Subtract the cepstrum trend.

This operation modifies the calling PowerCepstrogram object.

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

constexpr auto GET_CPPS_HILLENBRAND_DOCSTRING =
R"(Compute cepstrum peak prominence measures by Hillenbrand.

The CPP measure is the difference in amplitude between the cepstral peak
and the corresponding value on the trend line that is directly below the
peak (i.e., the predicted magnitude for the quefrency at the cepstral
peak). The CPP measure represents how far the cepstral peak emerges from
the cepstrum background.

Parameters
----------
subtract_trend_before_smoothing : bool, default True
    True to remove the trend before computing CPPs

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
)";

constexpr auto GET_CPPS_DOCSTRING =
R"(Compute cepstrum peak prominence measures on all the frames.

The CPP measure is the difference in amplitude between the cepstral peak
and the corresponding value on the trend line that is directly below the
peak (i.e., the predicted magnitude for the quefrency at the cepstral
peak). The CPP measure represents how far the cepstral peak emerges from
the cepstrum background.

Parameters
----------
subtract_trend_before_smoothing : bool, default True
    True to remove the trend before computing CPPs

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
)";

constexpr auto TO_POWER_CEPSTRUM_DOCSTRING =
R"(Return a `PowerCepstrum` slice at specified time

time : float
    Time at which to create the slice

Returns
-------
`parselmouth.PowerCepstrum`
)";

}// namespace parselmouth