class Link:
    def __init__(self, _hash, time):
        self._hash = _hash
        self.time = time

    def __eq__(self, other):
        return self._hash == other._hash and self.time == other.time

    def __hash__(self):
        return hash((self._hash, self.time))


def main():
    links = []

    with open("../links.txt") as f:
        for line in f:
            temp = line.strip().split(";")
            links.append(Link(int(temp[0]), int(temp[1])))

    print(len(links))
    links = list(set(links))
    print(len(links))


if __name__ == '__main__':
    main()
