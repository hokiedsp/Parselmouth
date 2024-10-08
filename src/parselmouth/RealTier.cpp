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
// #include "RealTier_docstrings.h" # TBD

#include "TimeClassAspects.h"
#include "utils/SignatureCast.h"
#include "utils/pybind11/ImplicitStringToEnumConversion.h"
#include "utils/pybind11/NumericPredicates.h"

#include <praat/fon/RealTier.h>

#include <algorithm>
#include <tuple>
#include <vector>

#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace py::literals;
using namespace std::string_literals;

namespace parselmouth {

PRAAT_CLASS_BINDING(RealTier) {

	using signature_cast_placeholder::_;

	addTimeFunctionMixin(*this);

	// doc() = CREATE_CLASS_DOCSTRING;

	def(py::init([](double startTime, double endTime) {
		    Melder_require(endTime >= startTime, U"Your end time (", endTime, U") should not be less than your start time (", startTime, U").");
		    return RealTier_create(startTime, endTime);
	    }),
	    "start_time"_a, "end_time"_a);

	def("__len__", [](RealTier self) { return self->points.size; });

	def("__getitem__", [](RealTier self, long i) { 
		
		auto val = RealTier_getValueAtIndex(self, i + 1);
		if (isnan(val))
			throw py::index_error();
		return val;
		
		 }, "i"_a);

	def("__setitem__", [](RealTier self, long i, double v) { 

		if (i<0 || i >= self->points.size)
			throw py::index_error();

		self->points.at [i+1] -> value = v; }, "i"_a, "v"_a);

	def("__delitem__", [](RealTier self, long i) { AnyTier_removePoint(self->asAnyTier(), i + 1); }, "i"_a);

	// def("as_array", [](RealTier self) { return py::array(self->nt, &self->t[1], py::cast(self)); });

	def("ts",
	    [](RealTier self) { // TODO This or rather use Python call to numpy?
			const auto size = self->points.size;
		    py::array_t<double> xs(static_cast<size_t>(size));
		    auto unchecked = xs.mutable_unchecked<1>();
		    for (auto i = 0; i < size; ++i) {
			    unchecked(i) = self->points.at [i+1]->number;
		    }
		    return xs;
	    });

	def("values",
	    [](RealTier self) { // TODO This or rather use Python call to numpy?
			const auto size = self->points.size;
		    py::array_t<double> xs(static_cast<size_t>(size));
		    auto unchecked = xs.mutable_unchecked<1>();
		    for (auto i = 0; i < size; ++i) {
			    unchecked(i) = self->points.at [i+1]->value;
		    }
		    return xs;
	    });


	// double RealTier_getValueAtIndex (constRealTier me, integer point);
	def("get_value_at_index", RealTier_getValueAtIndex, "point"_a);

	// todo
	def("get_time_at_index", [](RealTier self, long point) {
		point++;
		return point > self->points.size ? undefined : self->points.at [point] -> number; }, "point"_a);

	// double RealTier_getValueAtTime (constRealTier me, double t);
	def("get_value_at_time", RealTier_getValueAtTime, "t"_a);

	// double RealTier_getMinimumValue (constRealTier me);
	def("get_minimum_value", RealTier_getMinimumValue);

	// double RealTier_getMaximumValue (constRealTier me);
	def("get_maximum_value", RealTier_getMaximumValue);

	// double RealTier_getArea (constRealTier me, double tmin, double tmax);
	def("get_area", RealTier_getArea, "tmin"_a, "tmax"_a);

	// double RealTier_getMean_curve (constRealTier me, double tmin, double tmax);
	def("get_mean_curve", RealTier_getMean_curve, "tmin"_a, "tmax"_a);

	// double RealTier_getMean_points (constRealTier me, double tmin, double tmax);
	def("get_mean_points", RealTier_getMean_points, "tmin"_a, "tmax"_a);

	// double RealTier_getStandardDeviation_curve (constRealTier me, double tmin, double tmax);
	def("get_standard_deviation_curve", RealTier_getStandardDeviation_curve, "tmin"_a, "tmax"_a);

	// double RealTier_getStandardDeviation_points (constRealTier me, double tmin, double tmax);
	def("get_standard_deviation_points", RealTier_getStandardDeviation_points, "tmin"_a, "tmax"_a);

	// void RealTier_interpolateQuadratically (RealTier me, integer numberOfPointsPerParabola, bool logarithmically);
	def("interpolate_quadratically", RealTier_interpolateQuadratically, "number_of_points_per_parabola"_a, "logarithmically"_a);

	// void RealTier_addPoint (RealTier me, double t, double value);
	def("add_point", RealTier_addPoint, "t"_a, "value"_a);

	// void RealTier_multiplyPart (RealTier me, double tmin, double tmax, double factor);
	def("multiply_part", RealTier_multiplyPart, "tmin"_a, "tmax"_a, "factor"_a);

	// void RealTier_removePointsBelow (RealTier me, double level);
	def("remove_points_below", RealTier_removePointsBelow, "level"_a);

	// autoTableOfReal RealTier_downto_TableOfReal (constRealTier me, conststring32 timeLabel, conststring32 valueLabel);
	// autoTable RealTier_downto_Table (RealTier me, conststring32 indexText, conststring32 timeText, conststring32 valueText);
	// autoRealTier Vector_to_RealTier (Vector me, integer channel, ClassInfo klas);
	// autoRealTier Vector_to_RealTier_peaks (Vector me, integer channel, ClassInfo klas);
	// autoRealTier Vector_to_RealTier_valleys (Vector me, integer channel, ClassInfo klas);
	// autoRealTier PointProcess_upto_RealTier (PointProcess me, double value, ClassInfo klas);

	// void RealTier_formula (RealTier me, conststring32 expression, Interpreter interpreter, RealTier thee);

	// void RealTier_PointProcess_into_RealTier (RealTier me, PointProcess pp, RealTier thee);
	// autoRealTier RealTier_PointProcess_to_RealTier (RealTier me, PointProcess pp);
	// autoRealTier AnyRealTier_downto_RealTier (RealTier me);

	// autoRealTier Table_to_RealTier (Table me, integer timeColumn, integer valueColumn, double tmin, double tmax);
	// autoRealTier Matrix_to_RealTier (Matrix me, integer timeColumn, integer valueColumn, double tmin, double tmax);
}

} // namespace parselmouth
