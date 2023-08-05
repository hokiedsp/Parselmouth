/*
 * Copyright (C) 2019-2023  Yannick Jadoul
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
#include "TextGridTools.h"

#include <praat/fon/TextGrid.h>

#include <pybind11/stl.h>

#include <set>
#include <vector>

namespace py = pybind11;
using namespace py::literals;
using namespace std::string_literals;

using u32ostringstream = std::basic_ostringstream<char32_t>;


namespace parselmouth {

PRAAT_STRUCT_BINDING(TextPoint) {
	def_readonly("mark", &structTextPoint::mark);
	def_readonly("x", &structTextPoint::number);

	def("to_list",
	    [](TextGrid self) { 
			auto l = py::list();
			l.append(self->mark);
			l.append(self->number);
			return l; });
}

PRAAT_STRUCT_BINDING(TextInterval) {
	def_readonly("text", &structTextInterval::text);
	// def_readonly("xmin", &structTextInterval::xmin); inherits from Function
	// def_readonly("xmin", &structTextInterval::xmax); inherits from Function

	def("to_list",
	    [](TextGrid self) { 
			auto l = py::list();
			l.append(self->text);
			l.append(self->xmin);
			l.append(self->xmax);
			return l; });
}

PRAAT_STRUCT_BINDING(TextTier) {

	def(
	        "__getitem__",
	        [](TextGrid self, long i) {
		        try return TextGrid_checkSpecifiedTierIsIntervalTier(self, i + 1);
		        catch try return TextGrid_checkSpecifiedTierIsPointTier(self, i + 1);
		        catch throw py::index_error("TextGrid index out of range");
	        },
	        "i"_a);

	def("__len__",
	    [](TextGrid self) { return self->tiers->size; });
}

PRAAT_STRUCT_BINDING(IntervalTier) {

	def(
	        "__getitem__",
	        [](TextGrid self, long i) {
		        try return TextGrid_checkSpecifiedTierIsIntervalTier(self, i + 1);
		        catch try return TextGrid_checkSpecifiedTierIsPointTier(self, i + 1);
		        catch throw py::index_error("TextGrid index out of range");
	        },
	        "i"_a);

	def("__len__",
	    [](TextGrid self) { return self->tiers->size; });
}

/* NOTES on Praat assumptions:
 *
 * 1) Praat's UI does not allow TextGrids without tiers, but when programming, it seems nice to allow a programmer to have empty TextGrids.
 * 2) Normally, tier names should be a single-ink words (see _kUiField_type::WORD_, STRVECtokenize, Melder_findEndOfInk) and cannot contain a space.
 *
 * We are ignoring both assumptions here, here. I'm not expecting things to break (especially not for 2), so let's see what happens and fix this if necessary.
 */

PRAAT_CLASS_BINDING(TextGrid) {
	// Note: this overload should come before the `std::vector` overload, since strings can be converted into vectors of characters
	def(py::init([](double startTime, double endTime, const std::u32string &allTierNames, const std::u32string &pointTierNames) {
		    if (endTime <= startTime) Melder_throw(U"The end time should be greater than the start time.");
		    return TextGrid_create(startTime, endTime, allTierNames.c_str(), pointTierNames.c_str());
	    }),
	    "start_time"_a, "end_time"_a, "tier_names"_a, "point_tier_names"_a);

	def(py::init([](double startTime, double endTime, const std::vector<std::u32string> &allTierNames, const std::vector<std::u32string> &pointTierNames) {
		    if (endTime <= startTime) Melder_throw(U"The end time should be greater than the start time.");

		    std::unordered_set<std::u32string> allTierNamesSet(allTierNames.begin(), allTierNames.end());
		    for (auto &pointTierName : pointTierNames) {
			    if (!allTierNamesSet.count(pointTierName))
				    Melder_throw(U"Point tier name '", pointTierName.c_str(), U"' is not in list of all tier names.");
		    }

		    std::unordered_set<std::u32string> pointTierNamesSet(pointTierNames.begin(), pointTierNames.end());
		    auto textGrid = TextGrid_createWithoutTiers(startTime, endTime);
		    for (auto &tierName : allTierNames) {
			    autoFunction tier;
			    if (pointTierNamesSet.count(tierName))
				    tier = TextTier_create(startTime, endTime);
			    else
				    tier = IntervalTier_create(startTime, endTime);
			    Thing_setName(tier.get(), tierName.c_str());
			    textGrid->tiers->addItem_move(tier.move());
		    }
		    return textGrid;
	    }),
	    "start_time"_a, "end_time"_a, "tier_names"_a = py::list(), "point_tier_names"_a = py::list());

	def(py::init(&fromTgtTextGrid),
	    "tgt_text_grid"_a);

	def("to_tgt",
	    toTgtTextGrid,
	    py::kw_only(), "include_empty_intervals"_a = false);

	def_static("from_tgt",
	           fromTgtTextGrid,
	           "tgt_text_grid"_a);

	def("__getitem__",
	    [](TextGrid self, long i) {
		        try return TextGrid_checkSpecifiedTierIsIntervalTier(self, i + 1);
		        catch try return TextGrid_checkSpecifiedTierIsPointTier(self, i + 1);
		        catch throw py::index_error("TextGrid index out of range");
	        },
	        "i"_a);

	def("__len__",
	    [](TextGrid self) { return self->tiers->size; });
}

} // namespace parselmouth
