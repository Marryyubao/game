#pragma once

#ifndef _GLOBALS_H_
#define _GLOBALS_H_
//#include"../inc/ui/Application.h"
//#include"../inc/Sound.h"

class Application;
Application* GetApplication();

extern bool isRunning;

const int SINGLE_PLAYER = 0;
const int DOUBLE_PLAYER = 1;

extern int gameMode;

////image resource
//extern IMAGE batImage;
//extern IMAGE ballImage;

////sound resource
//extern FmodSound bounceSound;
//extern FmodSound scoreSound;

#endif