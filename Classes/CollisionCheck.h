#pragma once
#include "cocos2d.h"

struct CollisionCheck
{
	//�^�C���`�b�v�Ƃ̓����蔻��
	bool operator()(cocos2d::Vec2 pos)const;
};

