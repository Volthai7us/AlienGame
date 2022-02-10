# Alien Game
## _Simple Alien Shooting Game Coding with C++ and glut_

## Features

- There are rotating starts on background.
- If you kill a good alien(colored in light green body, blue eyes and with smile) screen is shaking and appearing a red effect as a warning.
- If you kill a evil alien(colored in dar green body, red eyes and with angry mouth) a green effect is appearing as a good sign.
- After you kill last evil alien as a finishing effect last animations on game running in slow motion.
- Score doesn't increase or decrease immediteally. It's changing step by step.
- After you kill a alien as a explosion effect there is simple particle system.
- Small adding on alien and bomb looking.
- When aliens is placing screen is virtually spliting into squeares and place aliens on these squares randomly and chaning with avoid overlap placement. 

## Languages

Written using C++ and freeglut

## Running

For compile in ubuntu

```
g++ Game.cpp -lGL -lGLU -lglut -o AlienGame
```

To run

```
./AlienGame
```
