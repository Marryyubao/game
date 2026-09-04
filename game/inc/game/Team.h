#pragma once

#ifndef _TEAM_H_
#define _TEAM_H_

#include"../game/Figure.h"
#include<memory>

enum Members
{
	MemberOne = 0,
    MemeberTwo,
	MemberNum
};


class Player
{
private:
	const std::wstring _name;
	
public:
	Player() : _TeamMemberOne(nullptr), _TeamMemberTwo(nullptr) {}
	Player(const std::wstring& name) :_name(name),_TeamMemberOne(nullptr), _TeamMemberTwo(nullptr){}
	~Player();

	Stats* _TeamMemberOne;
	Stats* _TeamMemberTwo;

};


#endif