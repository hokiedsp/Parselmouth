add_praat_subdir(SOURCES
	flac_bitmath.c
	flac_bitreader.c
	flac_bitwriter.c
	flac_cpu.c
	flac_crc.c
	flac_fixed.c
	# flac_float.c
	flac_format.c
	flac_lpc.c
	flac_md5.c
	flac_memory.c
	flac_metadata_iterators.c
	flac_metadata_object.c
	flac_stream_decoder.c
	flac_stream_encoder.c
	flac_stream_encoder_framing.c
	flac_window.c
INCLUDE_DIRS
	melder
)
if (WIN32)
	add_praat_subdir(SOURCES flac_windows_unicode_filenames.c INCLUDE_DIRS melder)
endif ()
