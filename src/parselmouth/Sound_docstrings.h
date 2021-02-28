#pragma once

namespace parselmouth {

constexpr auto TO_POINT_PROCESS_EXTREMA_DOCSTRING = 
R"(Create PointProcess by peak picking.

Returns a new PointProcess instance by peak-picking the acoustic sample
without pitch estimation.

Parameters
----------
channel : {"LEFT", "RIGHT"}, default="LEFT" (first channel)
    Sound channel to process

include_maxima : bool, default=True
    True to include the absolute maximum

include_minima : bool, default=False
    True to include the absolute minimum

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC70", "SINC700"}, 
                default="SINC70"
    Peak-picking interpolation method

See Also
--------
:object:`parselmouth.PointProcess`
:func:`parselmouth.Sound.to_pitch_ac`
:func:`parselmouth.Pitch.to_point_process_peaks`
)";

constexpr auto TO_POINT_PROCESS_PERIODIC_DOCSTRING = 
R"(Create PointProcess by cross-correlation.

Returns a new PointProcess instance using the pitch estimation algorithm in
:func:`~parselmouth.Sound.to_pitch_cc` and the voice cycle detection
algorithm in :func:`~parselmouth.Pitch.to_point_process_cc`.

Parameters
----------
minimum_pitch : float, default=75.0
    Minimum fundamental frequency to be considered

maximum_pitch : float, default=600.0
    Maximum fundamental frequency to be considered

See Also
--------
:praat:`To PointProcess (periodic, cc)...`
:object:`parselmouth.PointProcess`
:func:`parselmouth.Sound.to_pitch_cc`
:func:`parselmouth.Pitch.to_point_process_peaks`
)";

constexpr auto TO_POINT_PROCESS_PERIODIC_PEAKS_DOCSTRING = 
R"(Create PointProcess by peak picking with pitch estimation.

Returns a new PointProcess instance using the pitch estimation algorithm in
:func:`~parselmouth.Sound.to_pitch_cc` and the voice cycle detection
algorithm in :func:`~parselmouth.Pitch._to_point_process_peaks`.

Parameters
----------
minimum_pitch : float, default=75.0
    Minimum fundamental frequency to be considered

maximum_pitch : float, default=600.0
    Maximum fundamental frequency to be considered

include_maxima : bool, default=True
    True to include the absolute maximum

include_minima : bool, default=False
    True to include the absolute minimum

See Also
--------
:praat:`To PointProcess (periodic, peaks)...`
:object:`parselmouth.PointProcess`
:func:`parselmouth.Sound.to_pitch_cc`
:func:`parselmouth.Pitch.to_point_process_peaks`
)";

constexpr auto TO_POINT_PROCESS_ZEROS_DOCSTRING = 
R"(Create PointProcess by zero-crossing detection.

Returns a new PointProcess instance by detecting rising or falling edges
in the sound waveform. Linear interpolation is used to refine the timing
of the crossing.

Parameters
----------
channel : {"LEFT", "RIGHT"}, default="LEFT" (first channel)
    Sound channel to process

include_raisers : bool, default=True
    True to detect the rising edges

include_fallers : bool, default=False
    True to detect the falling edges

See Also
--------
:object:`parselmouth.PointProcess`
)";

}// namespace parselmouth
