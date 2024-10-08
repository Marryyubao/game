#include<easyx.h>
#include"../inc/Defines.h"
#include <Windows.h>
#include"../inc/Message.h"
#include"../inc/Globals.h"


void Init();
void ClearUp();

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    //初始化
    Init();

    //Application* app = GetApplication();

    //主循环
    while (isRunning)
    {
        cleardevice();
        //Process input
        PeekMouseMessage();
        if (IsKeyDown(VK_Q))
        {
            break;
        }
        //update game
        //app->Update();

        //draw
        //app->Draw();

        FlushBatchDraw();
        Sleep(15);
    }
    ClearUp();
    return 0;
}

void Init()
{
    //init graph
    initgraph(1000, 560);    // 创建绘图窗口，大小为 1000x560 像素
    setbkcolor(WHITE);//设置背景白色
    settextcolor(BLACK);//设置文本黑色

    ////init sound
    //InitFmodSystem();

    ////load Image resource
    //LoadImageResource(&batImage, L"res/Image.png", 0, 0, 20, 100);
    //LoadImageResource(&ballImage, L"res/Image.png", 20, 0, 10, 10);

    ////load sound recource
    //LoadFmodSound(&bounceSound, "res/bounce.wav");
    //LoadFmodSound(&scoreSound, "res/score.wav");

    ////init application
    //Application* app = GetApplication();
    //app->RegisterInterface(new MainInterface())->RegisterInterface(new GameInterface());

    BeginBatchDraw();
}

void ClearUp()
{
    EndBatchDraw();
    closegraph(); // 关闭绘图窗口
}

