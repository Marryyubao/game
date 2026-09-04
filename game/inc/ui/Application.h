#pragma once

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include"../../inc/ui/interface.h"
#include<unordered_map>

class Player;
class Stats;
class Interface;


class Application final
{
private:
	
	std::unordered_map<std::wstring, Interface*> _interfaces;
	Interface* _currentInterface;
	Interface* _nextInterface;
public:
	Application();
	~Application();

	Player* _Player[2];
	bool Figure1[4];
	bool Figure2[4];
	bool PickDown;
	bool _turn;			//右手玩家回合，置1
	bool _FirstDown;	//先手位是否已经完成攻击
	bool _DrawSkill = false;
	int round = 0;
	bool _Winner;
	bool _ShowActionText[4];	//攻击或技能信息文本显示

	Stats* _LeftPlayerTarget;
	Stats* _LeftOtherTarget;
	Stats* _RightPlayerTarget;
	Stats* _RightOtherTarget;

	Application* RegisterInterface(Interface* intf);

	//直接设置目标界面
	void SetInterface(const std::wstring& name);

	//在更新后再设置目标界面
	void ChangeInterface(const std::wstring& name);

	void Update();
	void Draw();

	void SetPlayer1TeamMember(Stats* p);
	void SetPlayer2TeamMember(Stats* p);
	void ClearTeamMember(Player* player);
	bool MemberNoFull(Player* player);
	void RenewActionText(int posi);
};


#endif