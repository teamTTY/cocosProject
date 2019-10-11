#include "Player.h"


Player * Player::createPlayer()
{
	/*Player* player = new(std::nothrow)Player();
	if (player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return player;*/
	return Player::create();
}

Player::Player()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	lpAnimCtl.Init(this);
	setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	runAction(lpAnimCtl.GetAct());
	reverseFlag = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key());
#else
	oprt_state.reset(new OPRT_Touch());
	setScale(3);
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

//move processing
	if (data.button[static_cast<int>(ST::NOW)])
	{
		if (data.dir == DIR::LEFT)
		{
			setPositionX(getPositionX() - 1);
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = true;
		}
		else if (data.dir == DIR::RIGHT)
		{
			setPositionX(getPositionX() + 1);
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = false;
		}
		else if (data.dir == DIR::UP)
		{
			setPositionY(getPositionY() + 1);
			lpAnimCtl.SetAnimSt(this, ANIM_ST::JUMP);
			reverseFlag = false;
		}
		else if (data.dir == DIR::DOWN)
		{
			setPositionY(getPositionY() - 1);
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN_SHOT);
			reverseFlag = false;
		}	
	}
	else
	{
		//If nothing is done Å® state is IDLE
		lpAnimCtl.SetAnimSt(this, ANIM_ST::IDLE);
	}

	if (numberOfRunningActions() == 0)
	{
		//if reverseFlag is true Å®Å@reverse
		runAction(cocos2d::FlipX::create(reverseFlag));
		runAction(lpAnimCtl.GetAct());
	}

}
