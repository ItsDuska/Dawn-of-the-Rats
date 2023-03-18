import math


def Distance(pos1, pos2):
    return math.sqrt((pos2[0]-pos1[0])*(pos2[0]-pos1[0])+(pos2[1]-pos1[1])*(pos2[1]-pos1[1]))
