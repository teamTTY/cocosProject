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
	DIR dir;			//左右上下判定
	INPUT_BTN button;		//nowとold情報
	cocos2d::Vec2 pos;	//座標
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
	input_data data;	//入力データ保存用
};

