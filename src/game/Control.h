#pragma once
enum class Control{
/*
	Essentially this file will be used to access the state of each key 
	For the Controller class as well as a way to reference them in 
	the other classes
*/
	UP,
	DOWN,
	QUIT,
	PAUSE,

	NUM_ITEMS // PLEASE LEAVE THIS LAST
};