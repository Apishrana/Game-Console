from math import fabs
from time import sleep
from random import randint


def getMapPoint(x, y):
    return gameMap[y][x]


def setMapPoint(pos, val):
    global gameMap
    gameMap[pos[1]][pos[0]] = val


def printMap():
    for y, i in enumerate(gameMap):
        for x, j in enumerate(i):
            print(j, end=" ")
        print("")
    for i in range(6):
        print()


def playerSetup():
    for i in pl1:
        setMapPoint(i, "|")
    for i in pl2:
        setMapPoint(i, "|")


def updateBall():
    global gameOver
    if [ballPos[0] + ballVelocity[0], ballPos[1] + ballVelocity[1]] in pl1:
        ballVelocity[0] = 1
    if [ballPos[0] + ballVelocity[0], ballPos[1] + ballVelocity[1]] in pl2:
        ballVelocity[0] = -1
    setMapPoint(ballPos, "0")
    ballPos[0] += ballVelocity[0]
    ballPos[1] += ballVelocity[1]
    setMapPoint(ballPos, "X")
    if ballPos[0] == 15 or ballPos[0] == 0:
        gameOver = True
    if ballPos[1] == 7:
        ballVelocity[1] = -1
    if ballPos[1] == 0:
        ballVelocity[1] = 1


def movePl1(dir):
    for i in pl1:
        setMapPoint(i, "0")
    if dir == 0 and pl1[2][1] != 7:
        for i in range(3):
            pl1[i][1] += 1
    elif dir == 1 and pl1[2][1] != 0:
        for i in range(3):
            pl1[i][1] -= 1


def movePl2(dir):
    for i in pl2:
        setMapPoint(i, "0")
    if dir == 0 and pl2[2][1] != 7:
        for i in range(3):
            pl2[i][1] += 1
    elif dir == 1 and pl2[2][1] != 0:
        for i in range(3):
            pl2[i][1] -= 1


gameMap = [["0" for i in range(16)] for i in range(8)]
gameOver = False
pl1 = [[1, 3], [1, 4], [1, 5]]
pl2 = [[14, 2], [14, 3], [14, 4]]
ballPosList = [[8, 4], [7, 4], [8, 3], [7, 3]]
ballVelDic = [[1, 1], [-1, 1], [1, -1], [-1, -1]]
ballPos = ballPosList[randint(0, 3)]
ballVelocity = ballVelDic[ballPosList.index(ballPos)]

setMapPoint(ballPos, "X")
print(ballPos)

while not gameOver:
    playerSetup()
    updateBall()
    printMap()
    # sleep(0.7)

    inp = input()
    if inp == "w":
        movePl1(1)
    elif inp == "s":
        movePl1(0)
    elif inp == "e":
        movePl2(1)
    elif inp == "d":
        movePl2(0)
