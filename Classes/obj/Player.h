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

	void update(float frame);
	CREATE_FUNC(Player);

private:
	std::unique_ptr<OPRT_State> oprt_state;
	input_data data;
	bool reverseFlag;
};

