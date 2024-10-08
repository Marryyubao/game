#include<easyx.h>
#include"../inc/Message.h"

static MouseMessage  mouse;

void PeekMouseMessage()
{
	ExMessage msg;
	//…Ë÷√≥ı÷µŒ™false
	mouse.IsUp = false;
	mouse.IsDown = false;
	while (peekmessage(&msg, EX_MOUSE))
	{
		if (msg.message == WM_MOUSEMOVE)
		{
			mouse.position.givex(msg.x);
			mouse.position.givey(msg.y);
		}
		else if (msg.message == WM_LBUTTONUP)
		{
			mouse.IsUp = true;
			mouse.IsDown = false;
		}
		else if (msg.message == WM_LBUTTONDOWN)
		{
			mouse.IsUp = false;
			mouse.IsDown = true;
		}
	}
}

bool IsKeyDown(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

MouseMessage* GetMouseMessage()
{
	return &mouse;
}