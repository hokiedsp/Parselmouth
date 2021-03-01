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
#ifndef INC_PARSELMOUTH_SPECTRUM_DOCSTRINGS_H
#define INC_PARSELMOUTH_SPECTRUM_DOCSTRINGS_H

namespace parselmouth {

constexpr auto TO_CEPSTRUM_DOCSTRING =
	R"(Create a new `Cepstrum` instance.

See Also
--------
:obj:`parselmouth.Cepstrum`
:func:`parselmouth.Spectrum.to_cepstrum_hillenbrand`
)";

constexpr auto TO_CEPSTRUM_HILLENBRAND_DOCSTRING =
	R"(Create a new `Cepstrum` instance using Hillenbrand algorithm.

See Also
--------
:obj:`parselmouth.Cepstrum`
:func:`parselmouth.Spectrum.to_cepstrum`
)";

const auto TO_POWER_CEPSTRUM_DOCSTRING =
R"(Create a new `PowerCepstrum` instance.)";

constexpr auto TO_LTAS_DOCSTRING = R"(Create a new `Ltas` instance.

Parameter
---------
bandwidth : float, default 1000.0
)";

constexpr auto TO_LTAS_1TO1_DOCSTRING = R"(Create a new `Ltas` instance without loss of frequency resolution.

Each band :math:`b_i` in the Ltas is computed from a single frequency
sample :math:`s_i` in the Spectrum as follows:

:math:`b_i = 2 \frac{(re(s_i))^2 + (im(s_i))^2}{4.0 \times 10^{-10}}`

If the original Spectrum is expressible in Pa / Hz (sound pressure in air),
the Ltas values are in dB/Hz relative to the auditory threshold at 1000 Hz
(2x10^{-5} Pa).

See also
--------
:praat:`Spectrum: To Ltas (1-to-1)`
)";

} // namespace parselmouth

#endif // INC_PARSELMOUTH_SPECTRUM_DOCSTRINGS_H
