#pragma once

#include <praat/fon/Intensity.h>

#include "utils/pybind11/ImplicitStringToEnumConversion.h"

namespace parselmouth {


enum class IntensityUnits {
	ENERGY = Intensity_units_ENERGY,
	SONES = Intensity_units_SONES,
	DB = Intensity_units_DB
};

enum class AveragingMethod {
	MEDIAN = Intensity_averaging_MEDIAN,
	ENERGY = Intensity_averaging_ENERGY,
	SONES = Intensity_averaging_SONES,
	DB = Intensity_averaging_DB
};

}// namespace parselmouth
