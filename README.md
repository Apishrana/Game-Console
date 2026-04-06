# Simple 16x8 game console

## What This Project Is

This is a simple 16x8 game console built using a [WS2812 64 Bit RGB LED Matrix](https://robocraze.com/products/ws2812-64-bit-rgb-led-matrix?variant=40193033044121) and an Arduino Uno using 4 buttons in D-pad configuration and a joystick to take input and 2 8x8 LED Matrix as display output using [FastLED](https://fastled.io/) library

The current repository includes:

- Arduino cpp code for the [Console](./src/main.cpp), [Game Menu screen](./src/mainMenu.cpp), [Game Over screen](./src/gameover.cpp) and 4 games
    - [Flappy Bird](./src/flapy.cpp)
    - [Snake](./src/sneak.cpp)
    - [Pong](./src/pong.cpp)
    - [BreakOut](./src/breakout.cpp)

- The games in python
    - [Flappy Bird](./python%20test%20code/flapy.py)
    - [Snake](./python%20test%20code/snake.py)
    - [Pong](./python%20test%20code/pong.py)
    - [BreakOut](./python%20test%20code/breakout.py)

- Game menu in python
    - [Game Menu screen](./python%20test%20code/main%20menu.py)
    - [Game Over screen](./python%20test%20code/gameover%20screen.py)

- A [Fritzing](https://fritzing.org/) design for wiring in `design.fzz`
- A Fusion360 design of Console

## Why I Made It

The main goal was to learn how to use led matrix as a display, learning how to make games without a game engine

## Features

- 16x8 display
- Joystick-based input along with buttons
- Passive buzzer for sound output
- 4 games

## How It Works

### Input

Takes input in each game as needed in game according to the game code

### Output

used FastLED library to display the output in the led matrix

## Wiring

The current wiring diagram is stored as [design.fzz](design.fzz).

Main control connections used in code right now:

Output

- DIN : 11
- Buzzer I/O: 10

Input

- Joystick Y: A4
- Joystick X: A5
- Joystick Button: A3
- Button UP: 7
- Button DOWN: 4
- Button LEFT: 2
- Button RIGHT: 8

### Circuit

- Breadboard

![img](https://stasis.hackclub-assets.com/images/1775311460432-72qy7x.png)

- Schematic

![img](https://stasis.hackclub-assets.com/images/1774862623770-bw32l1.png)

## Build Photos

to be added latter

## 3D Model

the car 3d model can be found in [cad/](cad/)

also on fusion [here]()

## PCB

This project currently uses wiring-based electronics using a breadboard, not a PCB design.

## Repository Structure

```text
.
├── README.md
├── cad
├── design.fzz
├── include
│   ├── README
│   └── connsol_utils.h
├── lib
│   └── README
├── platformio.ini
├── python test code
│   ├── breakout.py
│   ├── flapy.py
│   ├── gameover screen.py
│   ├── main menu.py
│   ├── pong.py
│   └── snake.py
├── src
│   ├── breakout.cpp
│   ├── flapy.cpp
│   ├── gameover.cpp
│   ├── main.cpp
│   ├── mainMenu.cpp
│   ├── pong.cpp
│   └── sneak.cpp
└── test
    └── README

7 directories, 20 files
```

## How to setup your own Console

- Connect your Uno to your device and upload the code in [main](./sec/main.cpp)
- Replicate the wiring in [design.fzz](design.fzz)
- 3D print the CAD design
- Assemble your console

## BOM

The full CSV BOM is in [BOM.csv](BOM.csv). Current estimated total: **₹ 1,000**.

| Name                                                                     | Purpose                             | Quantity | Total Cost (USD) | Link                                                                                                      | Distributor |
| ------------------------------------------------------------------------ | ----------------------------------- | -------- | ---------------- | --------------------------------------------------------------------------------------------------------- | ----------- |
| PCB Mounted Passive Buzzer Module                                        | for sound output                    | 1        | 0.25             | [link](https://robu.in/product/pcb-mounted-passive-buzzer-module/)                                        | robu.in     |
| 18650 x 2 battery holder with cover and On/Off Switch                    | battery holder for battery          | 1        | 0.54             | [link](https://robu.in/product/18650-x-2-battery-holder-with-cover-and-on-off-switch/)                    | robu.in     |
| CJMCU 64 Bit 8×8 RGB LED Driver Development Board                        | 2 8X8 led matrix for a 16X8 display | 2        | 3.04             | [link](https://robu.in/product/cjmcu-64-bit-8x8-rgb-led-driver-development-board/)                        | robu.in     |
| Uno R3 Board without Cable compatible with Arduino                       | Arduino to controlle the console    | 1        | 5.02             | [link](https://robu.in/product/arduino-uno-r3-without-cable/)                                             | robu.in     |
| 6 x 8 cm Universal PCB Prototype Board Single-Sided 2.54mm Hole Pitch    | soldering togather the components   | 1        | 0.35             | [link](https://robu.in/product/6-x-8-cm-universal-pcb-prototype-board-single-sided-2-54mm-hole-pitch/)    | robu.in     |
| Green Electronic Building Blocks Big Key Button Module High Level Output | Button for user input               | 4        | 1.44             | [link](https://robu.in/product/green-electronic-building-blocks-big-key-button-module-high-level-output/) | robu.in     |
