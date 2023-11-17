import numpy as np
from math import sqrt

a = np.array([0.0, 0.0, -9.81])
v = np.array([0.0, 0.0, 0.0])
p = np.array([0.0, 0.0, 9.81])

t = sqrt(2)


def compute(t):
    global a, v, p
    v += a * t
    p += 1 / 2 * v * t
    return p


print(f"t=0s : {p}\nt={t}s : {compute(t)}")
