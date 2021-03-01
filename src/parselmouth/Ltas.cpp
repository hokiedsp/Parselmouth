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

#include <praat/fon/Ltas.h>
#include <praat/fon/Sampled.h>

#include "Intensity_enums.h"
#include "Ltas_docstrings.h"

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth
{

	PRAAT_CLASS_BINDING(Ltas)
	{ // based on Vector class

		doc() = CREATE_CLASS_DOCSTRING;

		// DIRECT (NEW1_Ltases_average) {
		// 	CONVERT_TYPED_LIST (Ltas, LtasBag)
		// 		autoLtas result = Ltases_average (list.get());
		// 	CONVERT_TYPED_LIST_END (U"averaged")
		// }

		def("compute_trend_line", &Ltas_computeTrendLine,
			"from_frequency"_a = 600.0, "to_frequency"_a = 4000.0,
			COMPUTE_TREND_LINE_DOCSTRING);

		def(
			"get_lowest_frequency", [](Ltas self) { return self->xmin; }, GET_LOWEST_FREQUENCY_DOCSTRING);
		def(
			"get_highest_frequency", [](Ltas self) { return self->xmax; }, GET_HIGHEST_FREQUENCY_DOCSTRING);
		def(
			"get_bin_width", [](Ltas self) { return self->dx; }, GET_BIN_WIDTH_DOCSTRING);
		def("get_frequency_from_bin_number", &Sampled_indexToX<int>, "bin_number"_a, GET_FREQUENCY_FROM_BIN_NUMBER_DOCSTRING);
		def("get_band_from_frequency", &Sampled_xToIndex, "frequency"_a, GET_BAND_FROM_FREQUENCY_DOCSTRING);
		def("get_frequency_of_minimum", &Vector_getXOfMinimum,
			"from_frequency"_a = 0.0, "to_frequency"_a = 0.0, "interpolation"_a = kVector_peakInterpolation::NONE, GET_FREQUENCY_OF_MINIMUM_DOCSTRING);
		def("get_frequency_of_maximum", &Vector_getXOfMaximum,
			"from_frequency"_a = 0.0, "to_frequency"_a = 0.0, "interpolation"_a = kVector_peakInterpolation::NONE, GET_FREQUENCY_OF_MAXIMUM_DOCSTRING);
		def(
			"get_local_peak_height", [](Ltas self, double environmentMin, double environmentMax, double peakMin, double peakMax, IntensityUnits averagingUnits) {
				if (environmentMin >= peakMin)
					Melder_throw(U"The beginning of the environment must lie before the peak.");
				if (peakMin >= peakMax)
					Melder_throw(U"The end of the peak must lie after its beginning.");
				if (environmentMax <= peakMax)
					Melder_throw(U"The end of the environment must lie after the peak.");
				return Ltas_getLocalPeakHeight(self, environmentMin, environmentMax, peakMin, peakMax, static_cast<int>(averagingUnits));
			},
			"from_frequency"_a, "to_frequency"_a, "left_peak"_a, "right_peak"_a, "intensity_units"_a = IntensityUnits::ENERGY, GET_LOCAL_PEAK_HEIGHT_DOCSTRING);

		def("get_maximum", &Vector_getMaximum, "from_frequency"_a = 0.0, "to_frequency"_a = 0.0,
			"interpolation"_a = kVector_peakInterpolation::NONE, GET_MAXIMUM_DOCSTRING);

		def("get_minimum", Vector_getMinimum, "from_frequency"_a = 0.0, "to_frequency"_a = 0.0, "interpolation"_a = kVector_peakInterpolation::NONE, GET_MINIMUM_DOCSTRING);

		def(
			"get_mean", [](Ltas self, double fromFrequency, double toFrequency, IntensityUnits averagingUnits) {
				return Sampled_getMean_standardUnit(self, fromFrequency, toFrequency,
													0, static_cast<int>(averagingUnits), false);
			},
			"from_frequency"_a = 0.0, "to_frequency"_a = 0.0, "intensity_units"_a = IntensityUnits::ENERGY, GET_MEAN_DOCSTRING);

		def(
			"get_number_of_bins", [](Ltas self) { return self->nx; }, GET_NUMBER_OF_BINS_DOCSTRING);

		def(
			"get_slope", [](Ltas self, double f1min, double f1max, double f2min, double f2max, IntensityUnits averagingUnits) {
				return Ltas_getSlope(self, f1min, f1max, f2min, f2max, static_cast<int>(averagingUnits));
			},
			"left_low_band"_a, "right_low_band"_a, "left_high_band"_a, "right_high_band"_a, "intensity_units"_a = IntensityUnits::ENERGY, GET_SLOPE_DOCSTRING);

		def(
			"get_standard_deviation",
			[](Ltas self, double fromFrequency, double toFrequency, IntensityUnits averagingMethod) { return Sampled_getStandardDeviation_standardUnit(self, fromFrequency, toFrequency, 0, // level (irrelevant)
																																					   static_cast<int>(averagingMethod),
																																					   false // interpolate (don't)
																									  ); },
			"from_frequency"_a = 0.0, "to_frequency"_a = 0.0, "intensity_units"_a = IntensityUnits::ENERGY, GET_STANDARD_DEVIATION_DOCSTRING);

		def(
			"get_value", [](Ltas self, double frequency, kVector_valueInterpolation valueInterpolationType) {
				return Vector_getValueAtX(self, frequency,
										  1, // level
										  valueInterpolationType);
			},
			"frequency"_a, "interpolation"_a = kVector_valueInterpolation ::NEAREST, GET_VALUE_DOCSTRING);

		def(
			"get_value_in_bin", [](Ltas self, int binNumber) {
				return binNumber < 1 || binNumber > self->nx ? undefined : self->z[1][binNumber];
			},
			"bin_number"_a, GET_VALUE_IN_BIN_DOCSTRING);

		// DIRECT (NEW1_Ltases_merge) {
		// 	CONVERT_TYPED_LIST (Ltas, LtasBag)
		// 		autoLtas result = Ltases_merge (list.get());
		// 	CONVERT_TYPED_LIST_END (U"merged")
		// }

		def("subtract_trend_line", &Ltas_subtractTrendLine, "from_frequency"_a, "to_frequency"_a, SUBTRACT_TREND_LINE_DOCSTRING);

		// DIRECT (NEW_Ltas_to_Matrix) {
		// 	CONVERT_EACH (Ltas)
		// 		autoMatrix result = Ltas_to_Matrix (self);
		// 	CONVERT_EACH_END (self->name.get())
		// }

		// DIRECT (NEW_Ltas_to_SpectrumTier_peaks) {
		// 	CONVERT_EACH (Ltas)
		// 		autoSpectrumTier result = Ltas_to_SpectrumTier_peaks (self);
		// 	CONVERT_EACH_END (self->name.get())
		// }
	}
} // namespace parselmouth