/*
 * Copyright (C) 2021  Yannick Jadoul and contributors
 *
 * This file is part of Parselmouth.
 *
 * Parselmouth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Parselmouth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Parselmouth.  If not, see <http://www.gnu.org/licenses/>
 */

#pragma once
#ifndef INC_PARSELMOUTH_SOUND_DOCSTRINGS_H
#define INC_PARSELMOUTH_SOUND_DOCSTRINGS_H

namespace parselmouth {

constexpr auto TO_POINT_PROCESS_EXTREMA_DOCSTRING =
	R"(Create a `PointProcess` by peak picking.

Returns a new `PointProcess` instance by peak-picking the acoustic sample
without pitch estimation.

Parameters
----------
channel : {"LEFT", "RIGHT"}, default "LEFT" (first channel)
    Sound channel to process.

include_maxima : bool, default True
    True to include the absolute maximum.

include_minima : bool, default False
    True to include the absolute minimum.

interpolation : {"NONE", "PARABOLIC", "CUBIC", "SINC70", "SINC700"},
                default: "SINC70"
    Peak-picking interpolation method.

See Also
--------
parselmouth.PointProcess
parselmouth.Sound.to_pitch_ac, parselmouth.Pitch.to_point_process_peaks
)";

constexpr auto TO_POINT_PROCESS_PERIODIC_DOCSTRING =
	R"(Create PointProcess by cross-correlation.

Returns a new PointProcess instance using the pitch estimation algorithm in
:func:`~parselmouth.Sound.to_pitch_cc` and the voice cycle detection
algorithm in :func:`~parselmouth.Pitch.to_point_process_cc`.

Parameters
----------
minimum_pitch : float, default 75.0
    Minimum fundamental frequency to be considered.

maximum_pitch : float, default 600.0
    Maximum fundamental frequency to be considered.

See Also
--------
:praat:`Sound: To PointProcess (periodic, cc)...`
parselmouth.PointProcess
parselmouth.Sound.to_pitch_cc, parselmouth.Pitch.to_point_process_peaks
)";

constexpr auto TO_POINT_PROCESS_PERIODIC_PEAKS_DOCSTRING =
	R"(Create a `PointProcess` by peak picking with pitch estimation.

Returns a new `PointProcess` instance using the pitch estimation algorithm
in `Sound.to_pitch_cc` and the voice cycle detection algorithm in
`Pitch.to_point_process_peaks`.

Parameters
----------
minimum_pitch : float, default 75.0
    Minimum fundamental frequency to be considered

maximum_pitch : float, default 600.0
    Maximum fundamental frequency to be considered

include_maxima : bool, default True
    True to include the absolute maximum

include_minima : bool, default False
    True to include the absolute minimum

See Also
--------
:praat:`Sound: To PointProcess (periodic, peaks)...`
parselmouth.PointProcess
parselmouth.Sound.to_pitch_cc, parselmouth.Pitch.to_point_process_peaks
)";

constexpr auto TO_POINT_PROCESS_ZEROS_DOCSTRING =
	R"(Create a `PointProcess` by zero-crossing detection.

Returns a new `PointProcess` instance by detecting rising or falling edges
in the sound waveform. Linear interpolation is used to refine the timing
of the crossing.

Parameters
----------
channel : {"LEFT", "RIGHT"}, default "LEFT" (first channel)
    Sound channel to process

include_raisers : bool, default True
    True to detect the rising edges

include_fallers : bool, default False
    True to detect the falling edges

See Also
--------
parselmouth.PointProcess
)";

constexpr auto TO_CEPSTRUM_DOCSTRING =
	R"(Create a new `Cepstrum` instance.

See Also
--------
:obj:`parselmouth.Cepstrum`
)";

constexpr auto TO_LTAS_DOCSTRING =
	R"(Create a new `Ltas` instance.

Parameter
---------
bandwidth : float, default 100.0
    Bandwidth of LTAS in Hz

See Also
--------
:obj:`parselmouth.Ltas`
:obj:`parselmouth.Sound.to_ltas_pitchcorrected`
)";

constexpr auto TO_LTAS_PITCHCORRECTED_DOCSTRING =
	R"(Create a new `Ltas` instance.

It tries to compute an LTAS of the spectral envelope of the voiced parts,
correcting away the influence of F0 in a way that does not sacrifice
frequency selectivity. The resulting LTAS is meant to reflect only the
resonances (formants) in the vocal tract and the envelope of the glottal
source spectrum.

The analysis method is described in Boersma & Kovacic (2006).

Parameters
----------
minimum_pitch : float, default 75.0
maximum_pitch : float, default 600.0
maximum_frequency : float, default 5000.0
bandwidth : float, default 100.0
shortest_period : float, default 0.0001
longest_period : float, default 0.02
maximum_period_factor : float, default 1.3

See Also
--------
:praat:`Sound: To Ltas (pitch-corrected)...`
:obj:`parselmouth.Ltas`
:obj:`parselmouth.Sound.to_ltas`
)";

constexpr auto TO_POWER_CEPSTROGRAM_DOCSTRING =
	R"(Create a new `PowerCepstrum` instance.

The sound will first be resampled to twice the value of `maximum_frequency`
with the algorithm described at :func:`resample`. After this, pre-emphasis
is applied with the algorithm described at :func:`pre_emphasize`. For each
analysis window a Gaussian window is applied and the spectrum is
calculated. The spectrum is then transformed to a PowerCepstrum with the
procedure described at :func:`parselmouth.Spectrum.to_powercepstrum`.
Finally, the values from the PowerCepstrum are stored in the vertical slice
of the PowerCepstrogram.

Parameters
----------
pitch_floor : float, default 60.0
time_step : float, default 0.002
maximum_frequency : float, default 5000.0
pre_emphasis_from : float, default 50.0

See Also
--------
:praat:`Sound: To PowerCepstrogram...`
:obj:`parselmouth.Power Cepstrogram`
)";

constexpr auto TO_POWER_CEPSTROGRAM_HILLENBRAND_DOCSTRING =
	R"(Create a new `PowerCepstrum` instance.

Parameters
----------
pitch_floor : float, default 60.0
time_step : float, default 0.002

See Also
--------
:obj:`parselmouth.PowerCepstrogram`
)";

constexpr auto TO_LPC_AUTOCORRELATION_DOCSTRING = R"(Create LPC using autocorrelation method.

Run linear predictive coding (LPC) analysis with the autocorrelation
method and returns a new :obj:`~parselmouth.LPC` object containing the
analysis outcomes.

The autocorrelation algorithm is decribed in Markel & Gray (1976).

Warning
-------
You are advised not to use this command for formant analysis. For formant
analysis, instead use :func:`~parselmouth.Sound.to_formant_burg`, which
also works via LPC.

Parameters
----------
prediction_order : int, default=16
    Number of linear prediction coefficients, also called the number of
    poles. Choose this number at least twice as large as the number of
    spectral peaks that you want to detect.

window_length : float, default=0.025
    Effective duration of each analysis frame in seconds.

time_step : float, default=0.005
    Time step between two consecutive analysis frames in seconds.

preemphasis_frequency : float, default=50.0
    +6dB / octave filtering will be applied above this frequency. If you do
    not want pre-emphasis, choose a frequency greater than the Nyquist
    frequency.

See Also
--------
:praat:`Sound: To LPC (autocorrelation)...`
:obj:`~parselmouth.LPC`
:func:`~parselmouth.Sound.to_lpc_covariance`
:func:`~parselmouth.Sound.to_lpc_burg`
:func:`~parselmouth.Sound.to_lpc_marple`
)";

constexpr auto TO_LPC_COVARIANCE_DOCSTRING = R"(Create LPC using covariance method.

Run linear predictive coding (LPC) analysis with the covariance method and
returns a new :obj:`~parselmouth.LPC` object containing the analysis
outcomes.

The covariance algorithm is decribed in Markel & Gray (1976).

Warning
-------
You are advised not to use this command for formant analysis. For formant
analysis, instead use :func:`~parselmouth.Sound.to_formant_burg`, which
also works via LPC.

Parameters
----------
prediction_order : int, default=16
    Number of linear prediction coefficients, also called the number of
    poles. Choose this number at least twice as large as the number of
    spectral peaks that you want to detect.

window_length : float, default=0.025
    Effective duration of each analysis frame in seconds.

time_step : float, default=0.005
    Time step between two consecutive analysis frames in seconds.

preemphasis_frequency : float, default=50.0
    +6dB / octave filtering will be applied above this frequency.
    If you do not want pre-emphasis, choose a frequency greater than the
    Nyquist frequency.

See Also
--------
:praat:`Sound: To LPC (covariance)...`
:obj:`~parselmouth.LPC`
:func:`~parselmouth.Sound.to_lpc_autocorrelation`
:func:`~parselmouth.Sound.to_lpc_burg`
:func:`~parselmouth.Sound.to_lpc_marple`
)";

constexpr auto TO_LPC_BURG_DOCSTRING = R"(Create LPC using Burg's method.

Run linear predictive coding (LPC) analysis with the Burg's method and
returns a new :obj:`~parselmouth.LPC` object containing the analysis
outcomes.

Burg's algorithm is described in Anderson (1978)

Warning
-------
You are advised not to use this command for formant analysis. For formant
analysis, instead use :func:`~parselmouth.Sound.to_formant_burg`, which
also works via LPC.

Parameters
----------
prediction_order : int, default=16
    Number of linear prediction coefficients, also called the number of
    poles. Choose this number at least twice as large as the number of
    spectral peaks that you want to detect.

window_length : float, default=0.025
    Effective duration of each analysis frame in seconds.

time_step : float, default=0.005
    Time step between two consecutive analysis frames in seconds.

preemphasis_frequency : float, default=50.0
    +6dB / octave filtering will be applied above this frequency. If you do
    not want pre-emphasis, choose a frequency greater than the Nyquist
    frequency.

See Also
--------
:praat:`Sound: To LPC (burg)...`
:obj:`~parselmouth.LPC`
:func:`~parselmouth.Sound.to_lpc_autocorrelation`
:func:`~parselmouth.Sound.to_lpc_covariance`
:func:`~parselmouth.Sound.to_lpc_marple`
)";

constexpr auto TO_LPC_MARPLE_DOCSTRING = R"(Create LPC using Marple's method.

Run linear predictive coding (LPC) analysis with the Marple's method and
returns a new :obj:`~parselmouth.LPC` object containing the analysis
outcomes.

The algorithm is described in Marple (1980).

Warning
-------
You are advised not to use this command for formant analysis. For formant
analysis, instead use :func:`~parselmouth.Sound.to_formant_burg`, which
also works via LPC.

Parameters
----------
prediction_order : int, default=16
    Number of linear prediction coefficients, also called the number of
    poles. Choose this number at least twice as large as the number of
    spectral peaks that you want to detect.

window_length : float, default=0.025
    Effective duration of each analysis frame in seconds.

time_step : float, default=0.005
    Time step between two consecutive analysis frames in seconds.

preemphasis_frequency : float, default=50.0
    +6dB / octave filtering will be applied above this frequency. If you do
    not want pre-emphasis, choose a frequency greater than the Nyquist
    frequency.

tolerance1 : float, default=1e-6
    Stop the iteration when E(m) / E(0) < tolerance1, where E(m) is the
    prediction error for order m.

tolerance 2 : float, default=1e-6
    Stop the iteration when (E(m) - E(m-1)) / E(m-1) < tolerance2.

See Also
--------
:praat:`Sound: To LPC (marple)...`
:obj:`~parselmouth.LPC`
:func:`~parselmouth.Sound.to_lpc_autocorrelation`
:func:`~parselmouth.Sound.to_lpc_covariance`
:func:`~parselmouth.Sound.to_lpc_burg`
)";

} // namespace parselmouth

#endif // INC_PARSELMOUTH_SOUND_DOCSTRINGS_H
