#include"../inc/Globals.h"


static Application application;

Application* GetApplication()
{
	return &application;
}

bool isRunning = true;
extern bool isMainInterface=true;
extern bool isPickface=false;
extern bool isGameInterface=false;

int gameMode = 0;

//image resource
IMAGE I0;
IMAGE I1;
IMAGE I2;
IMAGE I3;
//
//FmodSound bounceSound;
//FmodSound scoreSound;