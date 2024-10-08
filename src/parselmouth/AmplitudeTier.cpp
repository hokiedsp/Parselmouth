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

#include "Parselmouth.h"
// #include "AmplitudeTier_docstrings.h" // TBD

#include "TimeClassAspects.h"
#include "utils/SignatureCast.h"
#include "utils/pybind11/ImplicitStringToEnumConversion.h"
#include "utils/pybind11/NumericPredicates.h"

#include <praat/fon/AmplitudeTier.h>
#include <praat/fon/RealTier.h>
#include <praat/fon/AnyTier.h>

#include <algorithm>
#include <tuple>
#include <vector>

#include <pybind11/numpy.h>
#include <pybind11/stl.h>


namespace py = pybind11;
using namespace py::literals;
using namespace std::string_literals;

namespace parselmouth {

PRAAT_CLASS_BINDING(AmplitudeTier) {

	using signature_cast_placeholder::_;

	// doc() = CREATE_CLASS_DOCSTRING;

	// autoAmplitudeTier AmplitudeTier_create (double tmin, double tmax);
	def(py::init([](double startTime, double endTime) {
		    Melder_require(endTime >= startTime, U"Your end time (", endTime, U") should not be less than your start time (", startTime, U").");
		    return AmplitudeTier_create(startTime, endTime);
	    }),
	    "start_time"_a, "end_time"_a);

	// autoAmplitudeTier PointProcess_upto_AmplitudeTier (PointProcess me, double soundPressure);
	def(py::init([](PointProcess me, double soundPressure) {
		    return PointProcess_upto_AmplitudeTier(me, soundPressure);
	    }),
	    "point_process"_a, "sound_pressure"_a);

	// autoAmplitudeTier RealTier_to_AmplitudeTier (RealTier me);
	// autoAmplitudeTier IntensityTier_to_AmplitudeTier (IntensityTier me);

	// autoAmplitudeTier PointProcess_Sound_to_AmplitudeTier_point (PointProcess me, Sound thee);
	def_static("from_point_process_point",
	           PointProcess_Sound_to_AmplitudeTier_point,
	           "point_process"_a, "sound"_a);

	// autoAmplitudeTier PointProcess_Sound_to_AmplitudeTier_period (PointProcess me, Sound thee,
	// 	double tmin, double tmax, double shortestPeriod, double longestPeriod, double maximumPeriodFactor);
	def_static("from_point_process_period",
	           args_cast<_, _, _, _, _, _, Positive<_>>(PointProcess_Sound_to_AmplitudeTier_period),
	           "point_process"_a, "sound"_a, "tmin"_a = 0.0, "tmax"_a = 0.0, "short_period"_a = 0.0001, "longest_period"_a = 0.02, "maximum_period_factor"_a = 1.3);
	// REAL (fromTime, U"left Time range (s)", U"0.0") \
	// REAL (toTime, U"right Time range (s)", U"0.0 (= all)")
	// REAL (shortestPeriod, U"Shortest period (s)", U"0.0001") \
	// REAL (longestPeriod, U"Longest period (s)", U"0.02") \
	// POSITIVE (maximumPeriodFactor, U"Maximum period factor", U"1.3")

	// praat_TimeFunction_modify_init (klas);
	// praat_addAction1 (klas, 0, U"Remove point...", nullptr, 1, MODIFY_TimeTier_removePoint);
	// praat_addAction1 (klas, 0, U"Remove point near...", nullptr, 1, MODIFY_TimeTier_removePointNear);
	// praat_addAction1 (klas, 0, U"Remove points between...", nullptr, 1, MODIFY_TimeTier_removePointsBetween);


#define RANGE_ARGS \
	"period_floor"_a = 0.0001, "period_ceiling"_a = 0.02, "maximum_amplitude_factor"_a = 1.6

	// double AmplitudeTier_getShimmer_local (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_local",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_local),
	    RANGE_ARGS);

	// double AmplitudeTier_getShimmer_local_dB (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_local_db",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_local_dB),
	    RANGE_ARGS);

	// double AmplitudeTier_getShimmer_apq3 (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_apq3",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_apq3),
	    RANGE_ARGS);

	// double AmplitudeTier_getShimmer_apq5 (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_apq5",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_apq5),
	    RANGE_ARGS);

	// double AmplitudeTier_getShimmer_apq11 (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_apq11",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_apq11),
	    RANGE_ARGS);

	// double AmplitudeTier_getShimmer_dda (AmplitudeTier me, double shortestPeriod, double longestPeriod, double maximumAmplitudeFactor);
	def("get_shimmer_dda",
	    args_cast<_, _, _, Positive<_>>(AmplitudeTier_getShimmer_dda),
	    RANGE_ARGS);
}
} // namespace parselmouth
