from turtle import color
import numpy as np 
import matplotlib.pyplot as plt 


FIGURE_1 = [(0,-1), (0,1), (1.5,0)]
FIGURE_2 = [(0.5,0), (2,-1), (2,1)]
POINTS = set()


def MinkowskiSum(Shape1, Shape2):
    POINTS = []
    for point in Shape1:
        for point2 in Shape2:
            POINTS.append( (point[0] + point2[0], point[1] + point2[1]) )
    
    return POINTS

def MinkowskiDifference(Shape1, Shape2):
    POINTS = []
    for point in Shape1:
        for point2 in Shape2:
            POINTS.append( (point[0] - point2[0], point[1] - point2[1]) )
    
    return POINTS

plt.subplot(2,2,1)
plt.plot([x for x,y in FIGURE_1] + [FIGURE_1[0][0]] , [y for x,y in FIGURE_1]+ [FIGURE_1[0][1]], marker='o')
plt.plot([x for x,y in FIGURE_2] + [FIGURE_2[0][0]], [y for x,y in FIGURE_2]+ [FIGURE_2[0][1]], marker='o', color='red')
plt.title("Figures")
# plt.subplot(2,2 ,2)
# plt.plot([x for x,y in FIGURE_2] + [FIGURE_2[0][0]], [y for x,y in FIGURE_2]+ [FIGURE_2[0][1]], marker='o')
plt.subplot(2,2,3)
POINTS = MinkowskiSum(FIGURE_1, FIGURE_2)
plt.plot([x for x,y in POINTS], [y for x,y in POINTS], marker='o')
plt.title("MinkowskiSum")
plt.subplot(2,2,4)
POINTS = MinkowskiDifference(FIGURE_1, FIGURE_2)
plt.plot([x for x,y in POINTS], [y for x,y in POINTS], marker='o')
plt.title("MinkowskiDifference")
plt.show()
# print(POINTS)




def Cube2D(center, size):
    delta = size / 2
    return [(center[0]-delta, center[1]-delta),
            (center[0]-delta, center[1]+delta),
            (center[0]+delta, center[1]-delta),
            (center[0]+delta, center[1]+delta)]

CUBE_1 = Cube2D((0, 0), 2)
CUBE_2 = Cube2D((1.3, 0.3), 2)
POINTS = set()

def MinkowskiSum(Shape1, Shape2):
    POINTS = []
    for point in Shape1:
        for point2 in Shape2:
            POINTS.append( (point[0] + point2[0], point[1] + point2[1]) )
    
    return POINTS

def MinkowskiDifference(Shape1, Shape2):
    POINTS = []
    for point in Shape1:
        for point2 in Shape2:
            POINTS.append( (point[0] - point2[0], point[1] - point2[1]) )
    
    return POINTS

plt.subplot(2,2,1)
plt.plot([x for x,y in CUBE_1] + [CUBE_1[0][0]] , [y for x,y in CUBE_1]+ [CUBE_1[0][1]], marker='o')
plt.plot([x for x,y in CUBE_2] + [CUBE_2[0][0]], [y for x,y in CUBE_2]+ [CUBE_2[0][1]], marker='o', color='red')
plt.title("Figures")
# plt.subplot(2,2 ,2)
# plt.plot([x for x,y in CUBE_2] + [CUBE_2[0][0]], [y for x,y in CUBE_2]+ [CUBE_2[0][1]], marker='o')
plt.subplot(2,2,3)
POINTS = MinkowskiSum(CUBE_1, CUBE_2)
plt.plot([x for x,y in POINTS], [y for x,y in POINTS], marker='o')
plt.title("MinkowskiSum")
plt.subplot(2,2,4)
POINTS = MinkowskiDifference(CUBE_1, CUBE_2)
plt.plot([x for x,y in POINTS], [y for x,y in POINTS], marker='o')
plt.title("MinkowskiDifference")
plt.show()