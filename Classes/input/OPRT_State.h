#pragma once
#include "cocos2d.h"
#include <array>

enum class TYPE {
	KEY,
	TOUCH,
	MAX
};

enum class ST {
	NOW,
	OLD,
	MAX
};

enum class DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX
};

using INPUT_BTN = std::array<int, static_cast<int>(ST::MAX)>;

struct input_data {
	DIR dir;			//���E�㉺����
	INPUT_BTN button;		//now��old���
	cocos2d::Vec2 pos;	//���W
};

struct OPRT_State
{
	~OPRT_State();
	void oprator(cocos2d::Node* sp) {
		Update(sp);
	}

	virtual TYPE GetType() = 0;
	virtual void Update(cocos2d::Node* sp) = 0;
	input_data GetData();

protected:
	input_data data;	//���̓f�[�^�ۑ��p
};

