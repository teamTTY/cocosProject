#include "OPRT_Touch.h"
#include "base/CCDirector.h"


OPRT_Touch::OPRT_Touch()
{
	windowSize = cocos2d::Director::getInstance()->getVisibleSize();
	centerPos = cocos2d::Vec2(windowSize.width - 50, 50);
	offset = 15;
	onceFlag = true;
}


OPRT_Touch::~OPRT_Touch()
{
}

void OPRT_Touch::Update(cocos2d::Node * sp)
{
	data.button[static_cast<int>(ST::OLD)] = data.button[static_cast<int>(ST::NOW)];

	listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
		data.button[static_cast<int>(ST::OLD)] = data.button[static_cast<int>(ST::NOW)];
		data.button[static_cast<int>(ST::NOW)] = 1;
		return true;
	};
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
	    loc = touch->getLocation();
	    if(loc.x < centerPos.x - offset) {
			data.dir = DIR::LEFT;
		}
		else if(loc.x > centerPos.x + offset) {
			data.dir = DIR::RIGHT;
		}
		else if(loc.y < centerPos.y - offset) {
			data.dir = DIR::DOWN;
		}
		else if(loc.y > centerPos.y + offset) {
			data.dir = DIR::UP;
		}
	};
	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
		data.button[static_cast<int>(ST::OLD)] = data.button[static_cast<int>(ST::NOW)];
		data.button[static_cast<int>(ST::NOW)] = 0;
        data.dir = DIR::MAX;
	};

	if (onceFlag)
	{
		sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
		onceFlag = false;
	}
}
