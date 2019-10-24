#include "OPRT_Key.h"


OPRT_Key::OPRT_Key()
{
    data.dir = DIR::MAX;
	data.button = { 0, 0 };
	onceFlag = true;
}


OPRT_Key::~OPRT_Key()
{
}

void OPRT_Key::Update(cocos2d::Node * sp)
{
	listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
								if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
								{
									data.dir = DIR::LEFT;
								}
								else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
								{
									data.dir = DIR::RIGHT;
								}
								if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
								{
									data.dir = DIR::UP;
								}
								else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
								{
									data.dir = DIR::DOWN;
								}
								data.button[static_cast<int>(ST::OLD)] = data.button[static_cast<int>(ST::NOW)];
								data.button[static_cast<int>(ST::NOW)] = static_cast<int>(keyCode);
	};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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

