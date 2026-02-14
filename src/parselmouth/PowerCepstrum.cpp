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

#include "utils/SignatureCast.h"
#include "utils/pybind11/NumericPredicates.h"

#include <praat/LPC/PowerCepstrum.h>

#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth {

PRAAT_CLASS_BINDING(PowerCepstrum) {
	using signature_cast_placeholder::_;

	def(py::init([](py::array_t<double, 0> values, Positive<double> qmax) {
		    auto ndim = values.ndim();
		    if (ndim > 2) {
			    throw py::value_error("Cannot create PowerCepstrum from an array with more than 2 dimensions");
		    }
		    if (ndim == 2 && values.shape(0) > 2) {
			    throw py::value_error("Cannot create PowerCepstrum from 2-dimensional array where the first dimension is greater than 2");
		    }

		    auto n = values.shape(ndim - 1);
		    auto result = PowerCepstrum_create(qmax, n);

		    if (ndim == 2) {
			    auto unchecked = values.unchecked<2>();
			    for (py::ssize_t i = 0; i < n; ++i) {
				    result->z[1][i + 1] = unchecked(0, i);
				    result->z[2][i + 1] = values.shape(1) == 2 ? unchecked(1, i) : 0.0;
			    }
		    }
		    else {
			    auto unchecked = values.unchecked<1>();
			    for (py::ssize_t i = 0; i < n; ++i) {
				    result->z[1][i + 1] = unchecked(i);
				    result->z[2][i + 1] = 0;
			    }
		    }

		    return result;
	    }),
	    "values"_a, "maximum_quefrency"_a);

	def(py::init([](py::array_t<std::complex<double>, 0> values, Positive<double> qmax) {
		    auto ndim = values.ndim();
		    if (ndim > 1) {
			    throw py::value_error("Cannot create PowerCepstrum from a complex array with more than 1 dimension");
		    }

		    auto n = values.shape(0);
		    auto result = PowerCepstrum_create(qmax, n);

		    auto unchecked = values.unchecked<1>();
		    for (py::ssize_t i = 0; i < n; ++i) {
			    result->z[1][i + 1] = unchecked(i).real();
			    result->z[2][i + 1] = unchecked(i).imag();
		    }

		    return result;
	    }),
	    "values"_a, "maximum_quefrency"_a);

	def("__getitem__",
	    [](PowerCepstrum self, integer index) {
		    if (index < 0 || index >= self->nx)
			    throw py::index_error("bin index out of range");
		    return std::complex<double>(self->z[1][index + 1], self->z[2][index + 1]);
	    },
	    "index"_a);

	def("__setitem__",
	    [](PowerCepstrum self, integer index, std::complex<double> value) {
		    if (index < 0 || index >= self->nx)
			    throw py::index_error("bin index out of range");
		    self->z[1][index + 1] = value.real();
		    self->z[2][index + 1] = value.imag();
	    },
	    "index"_a, "value"_a);
}

} // namespace parselmouth
