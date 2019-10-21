#pragma once
#include "cocos2d.h"

class Enemy :
	public cocos2d::Sprite
{
public:
	static Enemy* createPlayer();
	Enemy();
	~Enemy();
	void update(float frame);
	CREATE_FUNC(Enemy);
};

