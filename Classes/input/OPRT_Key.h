#pragma once
#include "OPRT_State.h"
struct OPRT_Key : OPRT_State
{
	OPRT_Key();
	~OPRT_Key();

	TYPE GetType() {
		return TYPE::KEY;
	}
	void Update(cocos2d::Node* sp);
private:
	cocos2d::EventListenerKeyboard* listener;
	bool onceFlag;
};

