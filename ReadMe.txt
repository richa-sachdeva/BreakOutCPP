Read Me -> BreakOut

BreakOut game is coded in C++, using Visual Studio, and Sfml library to support graphic features.

This folder contains -

 - Source Code  - This folder contains the only the source code
		Main folder is BreakOut, which contains all the source files. 
 - Sfml Library - You need Sfml library to run this project, and it's not included in the current project, but you can download
 - Executable    - BreakOut.Exe
 - ReadMe 
 - ScreenShot


Game Description -

Classic BreakOut -

Data is read from the blocklayout file, initially. As in the game, block move down with time (much like Tetris), so 
those block are randomly generated on fly.

4 type of blocks -

Pink -  that disappears after 2 hits and changes the colour of the ball when colliding, and it's color is changed to yellow
Green - It fires a bullet on being hit, and if player collides with fire, it size decreases (and if size is alaready decreased, game is over),
	and if size is decreased, speed of ball increases
Red -   It increases the size if small, and decreases the speed. if size is original, then nothing happens
Yellow - Disappears after being hit

On starting the game, game asks for debug ('d') mode, or normal mode
	- Debug mode, is more for testing in which even if player has died, game will continue, so that game can be tested for it's features
	- Normal mode, player will die.