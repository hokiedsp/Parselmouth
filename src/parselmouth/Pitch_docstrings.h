#pragma once

namespace parselmouth {

constexpr auto TO_POINT_PROCESS_DOCSTRING =
        R"(Create PointProcess from Pitch object.

Returns a new PointProcess instance which is generated from the specified 
Pitch object. The acoustic periodicity contour stored in the Pitch object 
is used as the frequency of an underlying point process (such as the 
sequence of glottal closures in vocal-fold vibration).

Parameters
----------
pitch : Parselmouth.Pitch
    Pitch object defining the periodicity contour

See Also
--------
:praat:`Pitch: To PointProcess`
)";

constexpr auto TO_POINT_PROCESS_SOUND_DOCSTRING = R"(Create PointProcess.

Returns a new PointProcess instance by interpreting the acoustic 
periodicity contour in the `Pitch` object as the frequency of an 
underlying point process (such as the sequence of glottal closures in 
vocal-fold vibration).

The unvoiced intervals in the `pitch` object is transferred to the point
process object, and the voiced intervals are further divided into each
phonation cycles.

Parameters
----------
sound : Parselmouth.Sound or None, default=None
    Sound object containing the target sound waveform. If omitted, 
    `PointProcess` is created only from the pitch contour. Analyzing the
    samples in `sound` object improves the accuracy of the resulting point
    process.

method : {"cc", "peaks"}, default="cc"
    Specify the Sound-assited generation method:

    "cc"    - Cross-correlation method. The fundamental periods of voice 
              are identified by cross-correlating the sound samples.

    "peaks" - Peak-picking method. The fundamental periods of voice are 
              identified by peak-picking the sound samples. Typically, less
              accurate than the cross-correlation method.

include_maxima : bool, default=True
    True to include the absolute maximum (for `method="peaks" only)

include_minima : bool, default=False
    True to include the absolute minimum (for `method="peaks" only)

See Also
--------
:praat:`Pitch: To PointProcess`
:praat:`Sound & Pitch: To PointProcess (cc)`
:praat:`Sound & Pitch: To PointProcess (peaks)...`
)";

constexpr auto TO_POINT_PROCESS_CC_DOCSTRING =
        R"(Create PointProcess from Sound and Pitch objects using crosscorrelation.

Returns a new PointProcess instance, generated from the specified Sound 
and Pitch instances using the cross-correlation method. The resulting 
instance contains voiced and unvoiced intervals according to `pitch` 
object, and the voiced intervals are further divided into fundamental 
periods of voice, identified by cross-correlating the sound samples.

Parameters
----------
sound : Parselmouth.Sound
    Sound object containing the target sound waveform

pitch : Parselmouth.Pitch
    Pitch object defining the periodicity contour of `sound`

See Also
--------
:praat:`Sound & Pitch: To PointProcess (cc)`
)";

constexpr auto TO_POINT_PROCESS_PEAKS_DOCSTRING =
        R"(Create PointProcess from Sound and Pitch objects using peak-picking.

Returns a new PointProcess instance, generated from the specified Sound 
and Pitch instances using the peak-picking method. The resulting 
instance contains voiced and unvoiced intervals according to `pitch` 
object, and the voiced intervals are further divided into fundamental 
periods of voice, identified by peak-picking the sound samples.

The periods that are found in this way are much more variable than those 
found by `from_sound_pitch_cc()` and therefore less useful for analysis 
and subsequent overlap-add synthesis.

Parameters
----------
sound : Parselmouth.Sound
    Sound object containing the target sound waveform

pitch : Parselmouth.Pitch
    Pitch object defining the periodicity contour of `sound`

See Also
--------
:praat:`Sound & Pitch: To PointProcess (peaks)...`
)";


constexpr auto GET_MEAN_STRENGTH_DOCSTRING = R"(Get mean pitch strength measure

Returns the value of user-selected measure of the periodicity strength.

Parameters
----------
type : {'ac', 'nhr', 'hnr_db'}, default="hnr_db"
    Type of strength measure to compute

from_time : double, default=0.0
    The start time of the compuation. Use 0.0 to start with the first 
    available frame

end_time : double, default=0.0
    The end time of the compuation. Use 0.0 to end with the last available
    frame

See Also
--------
:praat:`Voice report`
)";


constexpr auto GET_MEAN_DOCSTRING = R"(Get mean frequency

Returns the mean of periodicity frequency in the specified unit.

Parameters
----------
from_time : double, default=0.0
    The start time of the compuation. Use 0.0 to start with the first 
    available frame

end_time : double, default=0.0
    The end time of the compuation. Use 0.0 to end with the last available
    frame

unit : {'HERTZ','HERTZ_LOGARITHMIC','MEL','LOG_HERTZ','SEMITONES_1',
        'SEMITONES_100','SEMITONES_200','SEMITONES_440','ERB'},
       default=HERTZ
    Frequency unit

See Also
--------
:praat:`Voice report`
)";

constexpr auto GET_MAXIMUM_DOCSTRING = R"(Get maximum frequency

Returns the maximum frequency in the specified unit

Parameters
----------
from_time : double=0.0
    The starting time of the analysis time domain.

to_time : double=0.0
    The ending time of the analysis time domain. Values outside this domain
    are ignored. If `to_time` is not greater than `from_time`, the entire
    time domain of the Pitch object is considered. 

unit : {'HERTZ','HERTZ_LOGARITHMIC','MEL','LOG_HERTZ','SEMITONES_1',
        'SEMITONES_100','SEMITONES_200','SEMITONES_440','ERB'},
       default=HERTZ
    Frequency unit

interpolate : bool, default=True
    True to evalaute parabolically interpolated pitch peaks; False to 
    select the raw frequency samples.

See Also
--------
:praat:`Voice report`
)";

constexpr auto GET_MINIMUM_DOCSTRING = R"(Get minimum frequency

Returns the minimum frequency in the specified unit

Parameters
----------
from_time : double=0.0
    The starting time of the analysis time domain.

to_time : double=0.0
    The ending time of the analysis time domain. Values outside this domain
    are ignored. If `to_time` is not greater than `from_time`, the entire
    time domain of the Pitch object is considered. 

unit : {'HERTZ','HERTZ_LOGARITHMIC','MEL','LOG_HERTZ','SEMITONES_1',
        'SEMITONES_100','SEMITONES_200','SEMITONES_440','ERB'},
       default=HERTZ
    Frequency unit

interpolate : bool, default=True
    True to evalaute parabolically interpolated pitch peaks; False to 
    select the raw frequency samples.

See Also
--------
:praat:`Voice report`
)";

constexpr auto GET_STANDARD_DEVIATION_DOCSTRING = R"(Get standard deviation of frequency

Returns the standard deviation of frequency samples in the specified unit

Parameters
----------
from_time : double=0.0
    The starting time of the analysis time domain.

to_time : double=0.0
    The ending time of the analysis time domain. Values outside this domain
    are ignored. If `to_time` is not greater than `from_time`, the entire
    time domain of the Pitch object is considered. 

unit : {'HERTZ','HERTZ_LOGARITHMIC','MEL','LOG_HERTZ','SEMITONES_1',
        'SEMITONES_100','SEMITONES_200','SEMITONES_440','ERB'},
       default=HERTZ
    Frequency unit

See Also
--------
:praat:`Voice report`
)";


constexpr auto GET_QUANTILE_DOCSTRING = R"(Get quantile of frequency samples

Returns the quantile of the frequency samples in the specified unit

Parameters
----------
quantile : double
    Quantile to compute, which must be between 0 and 1 inclusive.

from_time : double=0.0
    The starting time of the analysis time domain.

to_time : double=0.0
    The ending time of the analysis time domain. Values outside this domain
    are ignored. If `to_time` is not greater than `from_time`, the entire
    time domain of the Pitch object is considered. 

unit : {'HERTZ','HERTZ_LOGARITHMIC','MEL','LOG_HERTZ','SEMITONES_1',
        'SEMITONES_100','SEMITONES_200','SEMITONES_440','ERB'},
       default=HERTZ
    Frequency unit

See Also
--------
:praat:`Voice report`
)";

constexpr auto GET_FRACTION_OF_LOCALLY_UNVOICED_FRAMES_DOCSTRING = R"(Get unvoiced statistics

Returns the statistics related to the unvoiced periods

Parameters
----------
from_time : double=0.0
    The starting time of the analysis time domain.

to_time : double=0.0
    The ending time of the analysis time domain. Values outside this domain
    are ignored. If `to_time` is not greater than `from_time`, the entire
    time domain of the Pitch object is considered. 

to_pitch : double=600.0
    The maximum voice frequency

silence_threshold : double=0.03
    The upper pitch strength limit of silent period

voicing_threshold : double 0.45
    The lower pitch strength limit of voicing period

See Also
--------
:praat:`Voice report`
)";

}// namespace parselmouth
