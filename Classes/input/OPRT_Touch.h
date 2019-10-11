#pragma once
#include "OPRT_State.h"
struct OPRT_Touch : OPRT_State
{
	OPRT_Touch();
	~OPRT_Touch();

	TYPE GetType() {
		return TYPE::TOUCH;
	}
	void Update(cocos2d::Node* sp);

private:
	cocos2d::Vec2 loc;
	cocos2d::Vec2 centerPos;
	cocos2d::Size windowSize;
	cocos2d::EventListenerTouchOneByOne* listener;

	int offset;
	int frameCnt;
	bool onceFlag;
};

