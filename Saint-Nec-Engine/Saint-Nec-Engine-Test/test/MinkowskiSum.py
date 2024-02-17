#!/usr/bin/python3
from turtle import color
import numpy as np 
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D

_2D = True
TAILLE = 2

# 2D parameters
FIGURE_1 = (0,0)
FIGURE_2 = (4,0)

# 3D parameters
CENTER1 = (0, 0, 0)
CENTER2 = (4, 0, 0)

if _2D:    
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

    def Cube2D(center, size):
        delta = size / 2
        return [(center[0]-delta, center[1]-delta),
                (center[0]-delta, center[1]+delta),
                (center[0]+delta, center[1]-delta),
                (center[0]+delta, center[1]+delta)]

    CUBE_1 = Cube2D(FIGURE_1, TAILLE)
    CUBE_2 = Cube2D(FIGURE_2, TAILLE)
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
else:

    def MinkowskiSum(Shape1, Shape2):
        POINTS = []
        for point in Shape1:
            for point2 in Shape2:
                POINTS.append((point[0] + point2[0], point[1] + point2[1], point[2] + point2[2]))

        return POINTS

    def MinkowskiDifference(Shape1, Shape2):
        POINTS = []
        for point in Shape1:
            for point2 in Shape2:
                POINTS.append((point[0] - point2[0], point[1] - point2[1], point[2] - point2[2]))

        return POINTS

    def plot_shape(ax, shape, color):
        x, y, z = zip(*shape)
        ax.scatter(x, y, z, c=color, marker='o')

    def Cube3D(center, size):
        delta = size / 2
        return [
            (center[0] - delta, center[1] - delta, center[2] - delta),
            (center[0] - delta, center[1] - delta, center[2] + delta),
            (center[0] - delta, center[1] + delta, center[2] - delta),
            (center[0] - delta, center[1] + delta, center[2] + delta),
            (center[0] + delta, center[1] - delta, center[2] - delta),
            (center[0] + delta, center[1] - delta, center[2] + delta),
            (center[0] + delta, center[1] + delta, center[2] - delta),
            (center[0] + delta, center[1] + delta, center[2] + delta)
        ]

    CUBE_1 = Cube3D(CENTER1, TAILLE)
    CUBE_2 = Cube3D(CENTER2, TAILLE)

    POINTS_SUM = MinkowskiSum(CUBE_1, CUBE_2)
    POINTS_DIFF = MinkowskiDifference(CUBE_1, CUBE_2)

    fig = plt.figure()

    ax1 = fig.add_subplot(2, 2, 1, projection='3d')
    plot_shape(ax1, CUBE_1, 'b')
    plot_shape(ax1, CUBE_2, 'r')
    ax1.set_title("Figures")

    ax2 = fig.add_subplot(2, 2, 3, projection='3d')
    plot_shape(ax2, POINTS_SUM, 'g')
    ax2.set_title("Minkowski Sum")

    ax3 = fig.add_subplot(2, 2, 4, projection='3d')
    plot_shape(ax3, POINTS_DIFF, 'y')
    ax3.set_title("Minkowski Difference")

    plt.show()
