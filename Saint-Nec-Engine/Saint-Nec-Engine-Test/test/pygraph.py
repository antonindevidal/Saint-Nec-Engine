import numpy as np
from math import sqrt
import matplotlib.pyplot as plt

PATH = "./data/"
FILENAME = "points.txt"
PRINT_LIKE_POINT = True

X = []
Y = []
Z = []
T = []

with open(PATH + FILENAME, "r", encoding="utf-8") as f:
    dt = float(next(f))
    i = 0
    for line in f:
        line = line[1:-2]
        x, y, z = [float(elt) for elt in line.split(',')]
        X.append(x)
        Y.append(y)
        Z.append(z)
        T.append(dt *i)
        i+=1

if PRINT_LIKE_POINT:
    plt.scatter(T, Z, color='red', marker='o', label='Z variations other time')
else:
    plt.plot(T, Z, color='red', linestyle=':', label='Z variations other time')
    
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.legend()

plt.show()
