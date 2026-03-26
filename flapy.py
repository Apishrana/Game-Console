from time import sleep
from random import randint

# funcs


def spacePressed():
    global playerY
    playerY -= 2


def spawnPipe():
    pipe = pipes[randint(0, 4)]
    for n, i in enumerate(pipe):
        setMapPoint((15, n), i)


def pushPipe():
    global gameMap
    for n, i in enumerate(gameMap):
        newRow = i[1:]
        newRow.append(" ")
        gameMap[n] = newRow


def getMapPoint(x, y):
    return gameMap[y][x]


def setMapPoint(pos, val):
    global gameMap
    gameMap[pos[1]][pos[0]] = val


def playerCheck():
    global gameOver
    if playerY > 7 or getMapPoint(playerX, playerY) == "|":
        gameOver = True


def printMap():
    for y, i in enumerate(gameMap):
        for x, j in enumerate(i):
            if (x, y) == (playerX, playerY):
                print(0, end=" ")
            else:
                print(j, end=" ")
        print("")
    for i in range(6):
        print()


gameMap = [[" " for i in range(16)] for i in range(8)]
pipes = [
    [
        "|",
        " ",
        " ",
        "|",
        "|",
        "|",
        "|",
        "|",
    ],
    [
        "|",
        "|",
        " ",
        " ",
        "|",
        "|",
        "|",
        "|",
    ],
    [
        "|",
        "|",
        "|",
        " ",
        " ",
        "|",
        "|",
        "|",
    ],
    [
        "|",
        "|",
        "|",
        "|",
        " ",
        " ",
        "|",
        "|",
    ],
    [
        "|",
        "|",
        "|",
        "|",
        "|",
        " ",
        " ",
        "|",
    ],
]
gameOver = False
frameCounter = 0
playerX = 2
playerY = 4


while not gameOver:
    pushPipe()

    if frameCounter == 0:
        spawnPipe()
        frameCounter = 4

    printMap()
    sleep(0.7)

    frameCounter -= 1
    playerY += 1

    playerCheck()
    if input() == " ":
        spacePressed()
