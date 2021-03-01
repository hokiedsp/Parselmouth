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
#include "PowerCepstrum_docstrings.h"

#include <tuple>

#include <praat/LPC/PowerCepstrum.h>

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth {

PRAAT_CLASS_BINDING(PowerCepstrum) {// based on Spectrum class

	doc() = CLASS_DOCSTRING;

	def(
	        "get_peak",
	        [](PowerCepstrum self, double pitchFloor, double pitchCeiling, kVector_peakInterpolation peakInterpolationType) {
		        double maximum;
		        PowerCepstrum_getMaximumAndQuefrency(self, pitchFloor, pitchCeiling,
		                                             peakInterpolationType, &maximum, nullptr);
		        return maximum;
	        },
	        "from_pitch"_a = 60.0, "to_pitch"_a = 333.3, "interpolation"_a = kVector_peakInterpolation ::PARABOLIC,
			GET_PEAK_DOCSTRING);

	def(
	        "get_quefrency_of_peak",
	        [](PowerCepstrum self, double pitchFloor, double pitchCeiling, kVector_peakInterpolation peakInterpolationType) {
		        double quefrency;
		        PowerCepstrum_getMaximumAndQuefrency(self, pitchFloor, pitchCeiling,
		                                             peakInterpolationType, nullptr, &quefrency);
		        return 1.0 / quefrency;
	        },
	        "from_pitch"_a = 60.0, "to_pitch"_a = 333.3, "interpolation"_a = kVector_peakInterpolation ::PARABOLIC,
			GET_QUEFRENCY_OF_PEAK_DOCSTRING);

	def(
	        "get_peak_prominence_hillenbrand", [](PowerCepstrum self, double pitchFloor, double pitchCeiling) {
		        double qpeak;
		        return std::tuple(PowerCepstrum_getPeakProminence_hillenbrand(self, pitchFloor, pitchCeiling, &qpeak), 1.0 / qpeak);
	        },
	        "from_pitch"_a = 60.0, "to_pitch"_a = 333.3, GET_PEAK_PROMINENCE_HILLENBRAND_DOCSTRING);

	def("get_rhamonics_to_noise_ratio", &PowerCepstrum_getRNR,
	    "from_pitch"_a = 60.0, "to_pitch"_a = 333.3, "fractional_width"_a = 0.05, GET_RHAMONICS_TO_NOISE_RATIO_DOCSTRING);

	def(
	        "get_peak_prominence", [](PowerCepstrum self, double pitchFloor, double pitchCeiling, kVector_peakInterpolation peakInterpolationType, double qmin, double qmax, kCepstrumTrendType lineType, kCepstrumTrendFit method) {
		        double qpeak;
		        return std::tuple(PowerCepstrum_getPeakProminence(self, pitchFloor, pitchCeiling,
		                                                          peakInterpolationType,
		                                                          qmin, qmax, lineType, method, &qpeak),
		                          1.0 / qpeak);
	        },
	        "from_pitch"_a = 60.0, "to_pitch"_a = 333.3, "interpolation"_a = kVector_peakInterpolation ::PARABOLIC, 
			"left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05, 
			"line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT,
			GET_PEAK_PROMINENCE_DOCSTRING);

	def(
	        "get_trend_line_slope",
	        [](PowerCepstrum self, double qmin, double qmax, kCepstrumTrendType lineType, kCepstrumTrendFit method) {
		        double result;
		        PowerCepstrum_fitTrendLine(self, qmin, qmax, &result, nullptr, lineType, method);
		        return result;
	        },
	        "left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05,
	        "line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT,
			GET_TREND_LINE_SLOPE_DOCSTRING);

	def(
	        "get_trend_line_intercept",
	        [](PowerCepstrum self, double qmin, double qmax, kCepstrumTrendType lineType, kCepstrumTrendFit method) {
		        double result;
		        PowerCepstrum_fitTrendLine(self, qmin, qmax, nullptr, &result, lineType, method);
		        return result;
	        },
	        "left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05,
	        "line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT,
			GET_TREND_LINE_INTERCEPT_DOCSTRING);

	def(
	        "get_trend_line",
	        [](PowerCepstrum self, double qmin, double qmax, kCepstrumTrendType lineType, kCepstrumTrendFit method) {
		        double slope, intercept;
		        PowerCepstrum_fitTrendLine(self, qmin, qmax, &slope, &intercept, lineType, method);
		        return std::tuple(slope, intercept);
	        },
	        "left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05,
	        "line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT);

	def("subtract_trend", &PowerCepstrum_subtractTrend,
	    "left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05,
	    "line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT,
		SUBTRACT_TREND_DOCSTRING);

	def("subtract_trend_inplace", &PowerCepstrum_subtractTrend_inplace,
	    "left_trend_line_quefrency_range"_a = 0.001, "right_trend_line_quefrency_range"_a = 0.05,
	    "line_type"_a = kCepstrumTrendType::DEFAULT, "fit_method"_a = kCepstrumTrendFit::DEFAULT,
		SUBTRACT_TREND_INPLACE_DOCSTRING);

	def("smooth_inplace", &PowerCepstrum_smooth_inplace,
	    "quefrency_averaging_window"_a = 0.0005, "number_of_iterations"_a = 1,
		SMOOTH_INPLACE_DOCSTRING);

	def("smooth", &PowerCepstrum_smooth,
	    "quefrency_averaging_window"_a = 0.0005, "number_of_iterations"_a = 1,
		SMOOTH_DOCSTRING);

	// autoMatrix PowerCepstrum_to_Matrix(PowerCepstrum me);

	// autoPowerCepstrum Matrix_to_PowerCepstrum(Matrix me);

	// autoPowerCepstrum Matrix_to_PowerCepstrum_row(Matrix me, integer row);

	// autoPowerCepstrum Matrix_to_PowerCepstrum_column(Matrix me, integer col);
}
}// namespace parselmouth
