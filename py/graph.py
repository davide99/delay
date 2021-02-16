import csv
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict

with open('./cmake-build-release/out.csv', newline='') as f:
        data = [list(map(float, row)) for row in csv.reader(f)]

deltas_occ = defaultdict(int)

for e in data:
    deltas_occ[np.abs(e[0]-e[1])] += 1

deltas = list(delta for delta, occ in deltas_occ.items() if occ >= 5)

x = []
y = []
w = []
for e in data:
    delta = np.abs(e[0]-e[1])
    aggiungi = False

    for d in deltas:
        if np.abs(delta-d) < 0.01:
            aggiungi = True
            weight = deltas_occ[d]
            break

    if aggiungi:
        x.append(e[0])
        y.append(e[1])
        w.append(weight)

plt.scatter(x, y, s=10, c='g')

fit = np.polyfit(x, y, 1, w=w)
print(fit)
x1 = [0, np.max(x)]
y1 = [fit[1], fit[0]*x1[1]+fit[1]]
plt.plot(x1, y1)

plt.show()