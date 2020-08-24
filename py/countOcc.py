import sys


def main():
    values = []
    occ = []

    if len(sys.argv) != 2:
        quit()

    with open(sys.argv[1]) as f:
        for line in f:
            val = int(line.strip())

            if val in values:
                index = values.index(val)
                occ[index] += 1
            else:
                values.append(val)
                occ.append(1)

    for i in range(len(values)):
        print(values[i], occ[i])


if __name__ == '__main__':
    main()
