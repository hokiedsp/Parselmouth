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

#include <praat/LPC/PowerCepstrogram.h>

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth {

PRAAT_CLASS_BINDING(PowerCepstrogram) {// based on Spectrum class

	def("smooth", &PowerCepstrogram_smooth,
	    "time_averaging_window"_a = 0.02, "quefrency_averaging_window"_a = 0.0005);

	def("get_start_quefrency", [](PowerCepstrogram self) { return self->ymin; });

	def("get_end_quefrency", [](PowerCepstrogram self) { return self->ymax; });

	def("get_number_of_quefrency_bins", [](PowerCepstrogram self) { self->ny; });

	def("get_quefrency_step", [](PowerCepstrogram self) { self->dy; });

	def("subtract_trend", &PowerCepstrogram_subtractTrend,
	    "left_trend_line_quefrency_range"_a = 0.001,
	    "right_trend_line_quefrency_range"_a = 0.05,
	    "trend_type"_a = kCepstrumTrendType::DEFAULT,
	    "fit_method"_a = kCepstrumTrendFit::DEFAULT);

	def("subtract_trend_inplace", &PowerCepstrogram_subtractTrend_inplace,
	    "left_trend_line_quefrency_range"_a = 0.001,
	    "right_trend_line_quefrency_range"_a = 0.05,
	    "trend_type"_a = kCepstrumTrendType::DEFAULT,
	    "fit_method"_a = kCepstrumTrendFit::DEFAULT);

	def("get_cpps_hillenbrand", &PowerCepstrogram_getCPPS_hillenbrand,
	    "subtract_trend_before_smoothing"_a = true,
	    "time_averaging_window"_a = 0.001, "quefrency_averaging_window"_a = 0.00005,
	    "left_peak_search_pitch_range"_a = 60.0,
	    "right_peak_search_pitch_range"_a = 330.0);

	def("get_cpps", &PowerCepstrogram_getCPPS,
	    "subtract_trend_before_smoothing"_a = true,
	    "time_averaging_window"_a = 0.02, "quefrency_averaging_window"_a = 0.0005,
	    "left_peak_search_pitch_range"_a = 60.0,
	    "right_peak_search_pitch_range"_a = 330.0, "tolerance"_a = 0.05,
	    "interpolation"_a = kVector_peakInterpolation ::PARABOLIC,
	    "left_trend_line_quefrency_range"_a = 0.001,
	    "right_trend_line_quefrency_range"_a = 0.05,
	    "trend_type"_a = kCepstrumTrendType::DEFAULT,
	    "fit_method"_a = kCepstrumTrendFit::DEFAULT);

	// FORM (MODIFY_PowerCepstrogram_formula, U"PowerCepstrogram: Formula", nullptr) {
	// 	TEXTFIELD (formula, U"   Replace all values with:", U"sqrt(self)")

	def("to_power_cepstrum", &PowerCepstrogram_to_PowerCepstrum_slice,
	    "time"_a = 0.1);

	// FORM(NEW_PowerCepstrogram_to_Table_cpp, U"PowerCepstrogram: To Table (peak prominence)", U"PowerCepstrogram: To Table (peak prominence)...") {
	// 	REAL(fromPitch, U"left Peak search pitch range (Hz)", U"60.0")
	// 	REAL(toPitch, U"right Peak search pitch range (Hz)", U"330.0")
	// 	POSITIVE(tolerance, U"Tolerance (0-1)", U"0.05")
	// 	RADIO_ENUM(kVector_peakInterpolation, peakInterpolationType,
	// 	           U"Interpolation", kVector_peakInterpolation ::PARABOLIC)
	// 	REAL(fromQuefrency_trendLine, U"left Trend line quefrency range (s)", U"0.001")
	// 	REAL(toQuefrency_trendLine, U"right Trend line quefrency range (s)", U"0.05)")
	// 	OPTIONMENU_ENUM(kCepstrumTrendType, lineType, U"Trend type", kCepstrumTrendType::DEFAULT)
	// 	OPTIONMENU_ENUM(kCepstrumTrendFit, fitMethod, U"Fit method", kCepstrumTrendFit::DEFAULT)
	// 	autoTable result = PowerCepstrogram_to_Table_cpp(me, fromPitch, toPitch, tolerance, peakInterpolationType, fromQuefrency_trendLine, toQuefrency_trendLine, lineType, fitMethod);
	// }

	// FORM(NEW_PowerCepstrogram_to_Table_hillenbrand, U"PowerCepstrogram: To Table (hillenbrand)", U"PowerCepstrogram: To Table (peak prominence...") {
	// 	REAL(fromPitch, U"left Peak search pitch range (Hz)", U"60.0")
	// 	REAL(toPitch, U"right Peak search pitch range (Hz)", U"330.0")
	// 	autoTable result = PowerCepstrogram_to_Table_hillenbrand(me, fromPitch, toPitch);
	// }

	// DIRECT(NEW_PowerCepstrogram_to_Matrix) {
	// 	CONVERT_EACH(PowerCepstrogram)
	// 	autoMatrix result = PowerCepstrogram_to_Matrix(me);
	// 	CONVERT_EACH_END(my name.get())
	// }
}
}// namespace parselmouth
