#pragma once
#include "input/OPRT_Key.h"
#include "input/OPRT_Touch.h"
#include "Animation/AnimCtl.h"
#include "cocos2d.h"
#include <memory>

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();

	Player();
	~Player();

	void update(float frame);				//���t���[���X�V�֐��i�����Ffloat�P�ʂ̃t���[�����j
	bool PLCollision(cocos2d::Vec2 pos, cocos2d::TMXTiledMap* map, cocos2d::TMXLayer* lay);//���_�𔻒肵�ē������Ă�����true��Ԃ�
	CREATE_FUNC(Player);

private:
	std::unique_ptr<OPRT_State> oprt_state;
	input_data data;
	bool reverseFlag;						//�摜�����E���]�����邩�t���O�itrue���]�Afalse�Ȃ��j
	cocos2d::Vec2 speed;					//�v���C���[�̈ړ��X�s�[�h
};

