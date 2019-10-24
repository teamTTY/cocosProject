#include "Player.h"
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOut.h"


Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player() : offsetPos(25, 120)
{
	//��ʃT�C�Y�ƌ��_���擾
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	//�A�j���[�V�����̏�����
	lpAnimCtl.Init(this);
	setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width / 6, visibleSize.height / 2 + origin.y));
	runAction(lpAnimCtl.GetAct());
	reverseFlag = false;
	plColFlg = false;
	speed = cocos2d::Vec2(3, 3);
	//�v���b�g�t�H�[���ʂɓ��̓N���X�i����̎d���j��؂�ւ���
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key());
#else
	oprt_state.reset(new OPRT_Touch());
#endif
	scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float frame)
{
	oprt_state->Update(this);
	data = oprt_state->GetData();

	//�����W������
	cocos2d::Vec2 tmpPos = getPosition();


	//����������͂�����Γ���
	if (data.button[static_cast<int>(ST::NOW)])
	{
		//�ړ�����
		auto sp = cocos2d::Vec2(0, 0);
		if (data.dir == DIR::LEFT)
		{
			tmpPos.x -= speed.x;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = true;
		}
		else if (data.dir == DIR::RIGHT)
		{
			tmpPos.x += speed.x;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = false;
		}
		if (data.dir == DIR::UP)
		{
			tmpPos.y += speed.y;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::JUMP);
			reverseFlag = false;
		}
		else if (data.dir == DIR::DOWN)
		{
			tmpPos.y -= speed.y;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN_SHOT);
			reverseFlag = false;
		}
	}
	else
	{
		//�ړ����Ă��Ȃ���΃A�j���[�V������IDLE�ɂ���
		lpAnimCtl.SetAnimSt(this, ANIM_ST::IDLE);
	}

	//�^�C���Ƃ̓����蔻��
	PlCollision(tmpPos);

	//�A�j���[�V�������Ă��Ȃ���Ύ��̃A�j���[�V�������J�n������
	if (numberOfRunningActions() == 0)
	{
		//reverseFlag��true�������甽�]����
		runAction(cocos2d::FlipX::create(reverseFlag));
		runAction(lpAnimCtl.GetAct());
	}
}

void Player::PlCollision(cocos2d::Vec2 tmpPos)
{
	//�󒆂ɂ������ɗ���������
	tmpPos.y--;
	//���Ƀu���b�N������΂���ȏ㗎�Ƃ��Ȃ�
	if (col->operator()(cocos2d::Vec2(tmpPos.x + offsetPos.x, tmpPos.y - offsetPos.y))
		|| col->operator()(cocos2d::Vec2(tmpPos.x - offsetPos.x, tmpPos.y - offsetPos.y)))
	{
		//������++���Ă�̂͂߂荞�݂�����邽��
		tmpPos.y++;
	}

	//����A�E��A�����A�E��
	cocos2d::Vec2 leftUp = { tmpPos.x - offsetPos.x, tmpPos.y };
	cocos2d::Vec2 rightUp = { tmpPos.x + offsetPos.x, tmpPos.y };
	cocos2d::Vec2 leftDown = { tmpPos.x - offsetPos.x, tmpPos.y - offsetPos.y };
	cocos2d::Vec2 rightDown = { tmpPos.x + offsetPos.x, tmpPos.y - offsetPos.y };

	if (data.dir == DIR::LEFT)
	{
		//��2�_�ǂ��炩���������Ă��遨true
		plColFlg = (col->operator()(leftUp) || col->operator()(leftDown));
	}
	else if (data.dir == DIR::RIGHT)
	{
		//�E2�_�ǂ��炩���������Ă��遨true
		plColFlg = (col->operator()(rightUp) || col->operator()(rightDown));
	}
	if (data.dir == DIR::UP)
	{
		//��2�_�ǂ��炩���������Ă��遨true
		plColFlg = (col->operator()(leftUp) || col->operator()(rightUp));
	}
	else if (data.dir == DIR::DOWN)
	{
		//��2�_�ǂ��炩���������Ă��遨true
		plColFlg = (col->operator()(leftDown) || col->operator()(rightDown));
	}

	//��Q���ɓ������Ă��Ȃ�������ړ�����
	if (!plColFlg)
	{
		setPosition(tmpPos);
	}
}
