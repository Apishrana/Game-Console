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
    for i in plPos:
        setMapPoint(i, "_")


def movePl(dir):
    for i in plPos:
        setMapPoint(i, " ")
    if dir == 0 and plPos[3][0] != 15:
        for i in range(4):
            plPos[i][0] += 1
    elif dir == 1 and plPos[0][0] != 0:
        for i in range(4):
            plPos[i][0] -= 1
    if not ballLaunched:
        setMapPoint(ballPos, " ")
        if dir == 0 and plPos[3][0] != 15:
            ballPos[0] += 1
        elif dir == 1 and plPos[0][0] != 0:
            ballPos[0] -= 1


def updateBall():
    global gameOver
    nextX = ballPos[0] + ballVelocity[0]
    nextY = ballPos[1] + ballVelocity[1]

    if getMapPoint(nextX, nextY) == "_":
        ballVelocity[1] = -1
    if getMapPoint(nextX, nextY) == "0":
        ballVelocity[1] = 1
        if getMapPoint(ballPos[0], nextY) == "0":
            setMapPoint([ballPos[0], nextY], " ")
        else:
            setMapPoint([nextX, nextY], " ")
    setMapPoint(ballPos, " ")
    if ballLaunched:
        ballPos[0] += ballVelocity[0]
        ballPos[1] += ballVelocity[1]
    if ballPos[0] >= 15:
        ballVelocity[0] = -1
    if ballPos[0] <= 0:
        ballVelocity[0] = 1
    if ballPos[1] == 0:
        ballVelocity[1] = 1
    setMapPoint(ballPos, "X")
    if ballPos[1] == 7:
        gameOver = True


gameMap = [[" " for i in range(16)] for i in range(8)]
gameOver = False
ballLaunched = False
plPos = [[6, 7], [7, 7], [8, 7], [9, 7]]
ballPosList = [[8, 6], [7, 6]]
ballVelList = [[1, -1], [-1, -1]]
ballPos = ballPosList[randint(0, 1)].copy()
ballVelocity = ballVelList[ballPosList.index(ballPos)]

gameMap[0] = ["0" for i in range(16)]
gameMap[1] = ["0" for i in range(16)]
gameMap[2] = ["0" for i in range(16)]


while not gameOver:

    inp = input()
    if inp == "a":
        movePl(1)
    if inp == "d":
        movePl(0)
    if inp == "l":
        ballLaunched = True
    playerSetup()
    updateBall()
    printMap()
    # sleep(0.7)
