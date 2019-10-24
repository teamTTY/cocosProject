#pragma once
#include "cocos2d.h"

struct CollisionCheck
{
	//タイルチップとの当たり判定
	bool operator()(cocos2d::Vec2 pos)const;
};

