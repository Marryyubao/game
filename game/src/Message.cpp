#include<easyx.h>
#include"../inc/Message.h"

static MouseMessage  mouse;

void PeekMouseMessage()
{
	ExMessage msg;
	//设置初值为false
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

//键盘按键信息
bool IsKeyDown(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

//鼠标信息
MouseMessage* GetMouseMessage()
{
	return &mouse;
}