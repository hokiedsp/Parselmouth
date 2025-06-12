/*
 * Copyright (C) 2017-2023  Yannick Jadoul
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
#include "TimeClassAspects.h"

#include "utils/SignatureCast.h"
#include "utils/pybind11/ImplicitStringToEnumConversion.h"
#include "utils/pybind11/NumericPredicates.h"

#include <praat/fon/Formant.h>

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth {

PRAAT_ENUM_BINDING(FormantUnit) {
	value("HERTZ", kFormant_unit::HERTZ);
	value("BARK", kFormant_unit::BARK);

	make_implicitly_convertible_from_string(*this);
}

PRAAT_CLASS_BINDING(Formant) {
	addTimeFrameSampledMixin(*this);

	using signature_cast_placeholder::_;

	def("get_value_at_time", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _>(Formant_getValueAtTime),
	    "formant_number"_a, "time"_a, "unit"_a = kFormant_unit::HERTZ);

	def("get_bandwidth_at_time",
	    args_cast<_, Positive<_>, _, _>(Formant_getBandwidthAtTime),
	    "formant_number"_a, "time"_a, "unit"_a = kFormant_unit::HERTZ);

	def("get_min_num_formants", &Formant_getMinNumFormants);
	def("get_max_num_formants", &Formant_getMaxNumFormants);

	def("get_extrema",
	    [](Formant me, Positive<integer> formantNumber, double tmin, double tmax) {
			double fmin, fmax;
			Formant_getExtrema(me, formantNumber, tmin, tmax, &fmin, &fmax);

			return py::make_tuple(fmin, fmax);
	    },
	    "formant_number"_a, "tmin"_a, "tmax"_a);

	// not part of Praat API?
	// void Formant_getMinimumAndTime (Formant me, integer formantNumber, double tmin, double tmax, kFormant_unit unit, int interpolate,
	// 	double *return_minimum, double *return_timeOfMinimum);
	// void Formant_getMaximumAndTime (Formant me, integer formantNumber, double tmin, double tmax, kFormant_unit unit, int interpolate,
	// 	double *return_maximum, double *return_timeOfMaximum);

	def("get_minimum", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getMinimum),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ, "interpolate"_a);
	def("get_maximum", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getMaximum),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ, "interpolate"_a);
	def("get_time_of_maximum", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getTimeOfMaximum),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ, "interpolate"_a);
	def("get_time_of_minimum", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getTimeOfMinimum),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ, "interpolate"_a);
	def("get_quantile", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getQuantile),
	    "formant_number"_a, "quantile"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ);
	def("get_quantile_of_bandwidth", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _, _>(Formant_getQuantileOfBandwidth),
	    "formant_number"_a, "quantile"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ);
	def("get_mean", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _>(Formant_getMean),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ);
	def("get_standard_deviation", // TODO Enum for Hertz vs. Bark?
	    args_cast<_, Positive<_>, _, _, _>(Formant_getStandardDeviation),
	    "formant_number"_a, "tmin"_a, "tmax"_a, "unit"_a = kFormant_unit::HERTZ);

	// void Formant_sort (Formant me);

	// autoMatrix Formant_to_Matrix (Formant me, integer iformant);
	// autoMatrix Formant_to_Matrix_bandwidths (Formant me, integer iformant);

	// autoFormant Formant_tracker (Formant me, integer numberOfTracks,
	// 	double refF1, double refF2, double refF3, double refF4, double refF5,
	// 	double dfCost,   // per kHz
	// 	double bfCost, double octaveJumpCost);

	// autoTable Formant_downto_Table (Formant me, bool includeFrameNumbers,
	// 	bool includeTimes, integer timeDecimals,
	// 	bool includeIntensity, integer intensityDecimals,
	// 	bool includeNumberOfFormants, integer frequencyDecimals,
	// 	bool includeBandwidths);
	// void Formant_list (Formant me, bool includeFrameNumbers,
	// 	bool includeTimes, integer timeDecimals,
	// 	bool includeIntensity, integer intensityDecimals,
	// 	bool includeNumberOfFormants, integer frequencyDecimals,
	// 	bool includeBandwidths);

	}

} // namespace parselmouth
