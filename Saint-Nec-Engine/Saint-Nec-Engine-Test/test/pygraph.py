import numpy as np
from math import sqrt
import matplotlib.pyplot as plt

PATH = "./data/"
FILENAME = "testInteraction.txt"
PRINT_LIKE_POINT = True

X = []
Y = []
Z = []
T = []
dt = 0

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


plt.subplot(3, 2, 1)
plt.scatter(T, X, color='red', marker= 'o' if PRINT_LIKE_POINT else':')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title('Current X')
plt.subplot(3, 2, 3)
plt.scatter(T, Y, color='red', marker='o' if PRINT_LIKE_POINT else':')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title('Current Y')
plt.subplot(3, 2, 5)
plt.scatter(T, Z, color='red', marker='o' if PRINT_LIKE_POINT else':')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title('Current Z')


a = np.array([0.0, 0.0, -9.81])
v = np.array([0.0, 0.0, 0.0])
p = np.array([0.0, 0.0, 0.0])

# t = sqrt(2)
# t = dt

print(dt)

def compute(t):
    global a, v, p
    p += v * t + 0.5 * a * t * t
    v += a * t
    return p

Expected = [[0.0, 0.0, 0.0]] + [list(compute(dt)) for _ in range(len(T)-1)]

plt.subplot(3, 2, 2)
plt.scatter(T, [x for x,y,z in Expected], color='red', marker='o', label='Z variations other time')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title("Expected X")
plt.subplot(3, 2, 4)
plt.scatter(T, [y for x,y,z in Expected], color='red', marker='o', label='Z variations other time')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title("Expected Y")
plt.subplot(3, 2, 6)
plt.scatter(T, [z for x,y,z in Expected], color='red', marker='o', label='Z variations other time')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (m)')
plt.title("Expected Z")

plt.subplots_adjust(hspace=1, wspace=0.5)
plt.show()

