#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CollisionCheck.h"

class Enemy :
	public cocos2d::Sprite
{
public:
	static Enemy* createEnemy();		//Enemy�N���X�𐶐�
	Enemy();
	~Enemy();
	void update(float frame);
	CREATE_FUNC(Enemy);

private:
	CollisionCheck* col;
};

