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


def updatePlayer():
    # del last block
    setMapPoint(playerPoints[0], "0")
    playerPoints.pop(0)

    # move
    headPos = list(playerPoints[-1])

    match playerDirection:
        case 1:
            # up
            headPos[1] -= 1
        case 2:
            # down
            headPos[1] += 1
        case 3:
            # left
            headPos[0] -= 1
        case 4:
            # right
            headPos[0] += 1

    x, y = headPos
    if x > 15:
        headPos[0] -= 16
    elif x < 0:
        headPos[0] += 16
    if y > 7:
        headPos[1] -= 8
    elif y < 0:
        headPos[1] += 8
    playerPoints.append(headPos)

    headPos = list(playerPoints[-1])
    if applePos in playerPoints:
        match playerDirection:
            case 1:
                # up
                headPos[1] -= 1
            case 2:
                # down
                headPos[1] += 1
            case 3:
                # left
                headPos[0] -= 1
            case 4:
                # right
                headPos[0] += 1

        x, y = headPos
        if x > 15:
            headPos[0] -= 16
        elif x < 0:
            headPos[0] += 16
        if y > 7:
            headPos[1] -= 8
        elif y < 0:
            headPos[1] += 8
        playerPoints.append(headPos)

        spawnApple()

    for i in playerPoints:
        # print(i)
        setMapPoint(i, "_")


def checkDeath():
    global gameOver
    for i in playerPoints:
        gameOver = playerPoints.count(i) > 1


def spawnApple():
    applePos[0] = randint(0, 15)
    applePos[1] = randint(0, 7)

    if applePos in playerPoints:
        spawnApple()

    setMapPoint(applePos, "A")


gameMap = [["0" for i in range(16)] for i in range(8)]

gameOver = False
playerPoints = [[2, 4], [3, 4]]
playerDirection = 4
applePos = [7, 4]

for i in playerPoints:
    setMapPoint(i, "_")

spawnApple()

while not gameOver:
    updatePlayer()
    printMap()
    # sleep(0.7)
    inp = input()
    if inp == "w":
        playerDirection = 1
    if inp == "s":
        playerDirection = 2
    if inp == "a":
        playerDirection = 3
    if inp == "d":
        playerDirection = 4

    checkDeath()
