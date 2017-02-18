Pong
======

A simple SDL2 Pong game

With help of the SDL2 Tutorial 

Setup
------

make pong

./pong


Package Structure
------------------

src/
	Contains all of the source files placed in their individual subdirs
build/
	All of the compiled objects

Bugs
----

 - Ball is "hollow" -> doesn't stop paddle from colliding (vertical movement, doesn't stop paddle movement if wall and padle and ball collide)
 - Segfault on long pause - `top` shows incremental memory during pause
