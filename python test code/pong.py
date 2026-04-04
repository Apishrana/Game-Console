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
    nextX = ballPos[0] + ballVelocity[0]
    nextY = ballPos[1] + ballVelocity[1]

    if nextX == 1 and any(p[1] == nextY for p in pl1):
        ballVelocity[0] = 1
    if nextX == 14 and any(p[1] == nextY for p in pl2):
        ballVelocity[0] = -1
    setMapPoint(ballPos, " ")
    ballPos[0] += ballVelocity[0]
    ballPos[1] += ballVelocity[1]
    if ballPos[0] >= 15:
        playerScore(1)
        return
    if ballPos[0] <= 0:
        playerScore(2)
        return

    if ballPos[1] == 7:
        ballVelocity[1] = -1
    if ballPos[1] == 1:
        ballVelocity[1] = 1
    setMapPoint(ballPos, "X")


def movePl1(dir):
    for i in pl1:
        setMapPoint(i, " ")
    if dir == 0 and pl1[2][1] != 7:
        for i in range(3):
            pl1[i][1] += 1
    elif dir == 1 and pl1[0][1] != 1:
        for i in range(3):
            pl1[i][1] -= 1


def movePl2(dir):
    for i in pl2:
        setMapPoint(i, " ")
    if dir == 0 and pl2[2][1] != 7:
        for i in range(3):
            pl2[i][1] += 1
    elif dir == 1 and pl2[0][1] != 1:
        for i in range(3):
            pl2[i][1] -= 1


def setupBall():
    global ballPos, ballVelocity
    setMapPoint(ballPos, " ")
    ballPos = ballPosList[randint(0, 1)].copy()
    ballVelocity = ballVelDic[ballPosList.index(ballPos)]
    print(ballPos)
    setMapPoint(ballPos, "X")


def playerScore(player):
    global pl2Score, pl1Score, gameOver
    if player == 1:
        pl1Score += 1
    if player == 2:
        pl2Score += 1
    setupBall()
    displayScore()
    if pl1Score == 9:
        gameOver = True
    if pl2Score == 9:
        gameOver = True


def displayScore():
    for i in range(pl1Score):
        setMapPoint([i, 0], "9")
    for i in range(pl2Score):
        setMapPoint([15 - i, 0], "9")


gameMap = [[" " for i in range(16)] for i in range(8)]
gameOver = False
pl1 = [[1, 3], [1, 4], [1, 5]]
pl2 = [[14, 3], [14, 4], [14, 5]]
ballPosList = [[8, 4], [7, 4]]
ballVelDic = [[1, 1], [-1, 1]]
ballPos = ballPosList[randint(0, 1)].copy()
ballVelocity = ballVelDic[ballPosList.index(ballPos)]
pl1Score = 0
pl2Score = 0

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
