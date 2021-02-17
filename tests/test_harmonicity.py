import pytest
import numpy as np

import parselmouth


@pytest.fixture
def rand_data():
    return np.random.rand(10)


@pytest.fixture
def rand_harmonicity(rand_data):
    return parselmouth.Harmonicity(rand_data, 0.1)


def test_sequence(rand_data, rand_harmonicity):
    """test compatibility with various sequence operations"""
    N = len(rand_harmonicity)
    assert N == rand_data.size
    for i in range(N):
        assert rand_harmonicity[i] == rand_data[i]
    assert np.allclose(rand_harmonicity, rand_data)


def test_constructor(rand_data):
    data = rand_data
    T = 0.1
    start_time = 1.2
    end_time = 10.0
    t1 = 1.3
    h = parselmouth.Harmonicity(data, T, start_time, end_time, t1)
    assert np.allclose(h, data)
    assert h.xmin == start_time
    assert h.xmax == end_time
    assert h.dx == T
    assert h.t1 == t1

    h = parselmouth.Harmonicity(data, T, start_time, end_time)
    assert h.t1 == start_time

    h = parselmouth.Harmonicity(data, T, start_time)
    assert h.xmax == start_time + T * data.size

    h = parselmouth.Harmonicity(data, T)
    assert h.xmin == 0.0
    assert h.xmax == T * data.size

    h = parselmouth.Harmonicity(data, start_time=start_time, end_time=end_time)
    assert h.dx == (end_time - start_time) / data.size

    h = parselmouth.Harmonicity(data, end_time=end_time)
    assert h.dx == end_time / data.size


def test_get_value(harmonicity):
    t = (harmonicity.tmin + harmonicity.tmax) / 2.0
    harmonicity.get_value(t)


def test_get_value_in_frame(harmonicity):
    harmonicity.get_value_in_frame(len(harmonicity) // 2 + 1)


# def test_formula(harmonicity):
#     harmonicity.formula("")


def test_get_maximum(harmonicity):

    harmonicity.get_maximum()
    # from_time=0.0, to_time=0.0, interpolation"PARABOLIC"


def test_get_mean(harmonicity):
    harmonicity.get_mean()
    # from_time=0.0, to_time=0.0


def test_get_minimum(harmonicity):
    harmonicity.get_minimum()
    # from_time=0.0, to_time=0.0,interpolation="PARABOLIC"


def test_get_standard_deviation(harmonicity):
    harmonicity.get_standard_deviation()
    # from_time=0.0, to_time=0.0


def test_get_time_of_maximum(harmonicity):
    harmonicity.get_time_of_maximum()
    # from_time=0.0, to_time=0.0,interpolation="PARABOLIC"


def test_get_time_of_minimum(harmonicity):
    harmonicity.get_time_of_minimum()
    # from_time=0.0,to_time=0.0,interpolation="PARABOLIC"

def test_get_quantile(harmonicity):
    harmonicity.get_quantile(0.5)

def test_pitch_harmonicity(resources):
    sound = parselmouth.Sound(resources["the_north_wind_and_the_sun.wav"])
    vowel = sound.extract_part(1.086, 1.136)
    print(vowel)

    # get pitch data
    pitch = vowel.to_pitch_ac()
    print(f"Mean autocorrelation={pitch.get_mean_strength(type='ac')}")
    print(f"Mean noise-to-harmonics ratio={pitch.get_mean_strength(type='nhr')}")
    print(f"Mean harmonics-to-noise ratio={pitch.get_mean_strength(type='hnr_db')} dB")
    print(f"default={pitch.get_mean_strength()}")


if __name__ == "__main__":
    from os import path
    import sys

    rootdir = path.dirname(path.dirname(__file__))
    sys.path.append(path.join(rootdir, "build", "src"))
    resources = {
        "the_north_wind_and_the_sun.wav": "tests/data/the_north_wind_and_the_sun.wav"
    }
