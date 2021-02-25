/*
 * Copyright (C) 2017-2021  Yannick Jadoul
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

#include "Parselmouth.h"

#include <praat/LPC/Cepstrum.h>
#include <praat/LPC/Cepstrum_and_Spectrum.h>
#include <praat/LPC/Sound_and_Cepstrum.h>
#include <praat/LPC/PowerCepstrogram.h>

#include "../utils/pybind11/ImplicitStringToEnumConversion.h"

namespace parselmouth {

PRAAT_ENUM_BINDING(CepstrumTrendType) {
	value("STRAIGHT", kCepstrumTrendType::LINEAR);
	value("EXPONENTIAL_DECAY", kCepstrumTrendType::EXPONENTIAL_DECAY);
	make_implicitly_convertible_from_string(*this);
}


PRAAT_ENUM_BINDING(CepstrumTrendFit) {
	value("ROBUST", kCepstrumTrendFit::ROBUST_FAST);
	value("LEAST_SQUARES", kCepstrumTrendFit::LEAST_SQUARES);
	value("ROBUST_SLOW", kCepstrumTrendFit::ROBUST_SLOW);
	make_implicitly_convertible_from_string(*this);
}

PRAAT_CLASS_BINDING(Cepstrum) {// based on Spectrum class
	def("to_spectrum", &Cepstrum_to_Spectrum);
	def("to_sound", &Cepstrum_to_Sound);
	def("to_power_cepstrum", &Cepstrum_downto_PowerCepstrum);
}

}// namespace parselmouth
