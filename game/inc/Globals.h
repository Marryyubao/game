#pragma once

#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include"../inc/ui/Application.h"
#include"../inc/utils/ImageShow.h"
//#include"../inc/Sound.h"

class Application;
Application* GetApplication();

extern bool isRunning;


const int SINGLE_PLAYER = 0;
const int DOUBLE_PLAYER = 1;

extern int gameMode;

//image resource
extern IMAGE I0;
extern IMAGE I1;
extern IMAGE I2;
extern IMAGE I3;

////sound resource
//extern FmodSound bounceSound;
//extern FmodSound scoreSound;

#endif