#pragma once
#include "input/OPRT_Key.h"
#include "input/OPRT_Touch.h"
#include "Animation/AnimCtl.h"
#include "CollisionCheck.h"
#include "cocos2d.h"
#include <memory>

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();			//�N���X�𐶐�
	Player();
	~Player();
	void update(float frame);				//���t���[���X�V�֐��i�����Ffloat�P�ʂ̃t���[�����j
	void PlCollision(cocos2d::Vec2 tmpPos);
	CREATE_FUNC(Player);

private:
	std::unique_ptr<OPRT_State> oprt_state;	//OPRT_State�N���X�̃����o�[���Ăԗp�̃|�C���^�[
	input_data data;						//���͂��ꂽ�f�[�^�����o���ϐ�
	bool reverseFlag;						//�摜�����E���]�����邩�t���O�itrue���]�Afalse�Ȃ��j
	cocos2d::Vec2 speed;					//�ړ����x
	CollisionCheck* col;					//�����蔻��Ăяo���|�C���^�[
	bool plColFlg;							//�����蔻��œ������Ă������ǂ�����ۑ�����ϐ�
	cocos2d::Vec2 offsetPos;				//�����蔻�肷����W�̃I�t�Z�b�g���w��i���x�����T�C�Y�j
};