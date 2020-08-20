from scipy.io.wavfile import write
import numpy as np


def main():
    samples = []

    with open("out.txt") as f:
        for line in f:
            samples.append(int(line))

    write("test_out.wav", 8000, np.array(samples, dtype=np.int16))


if __name__ == '__main__':
    main()
