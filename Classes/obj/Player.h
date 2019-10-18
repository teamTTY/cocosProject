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

	void update(float frame);				//毎フレーム更新関数（引数：float単位のフレーム数）
	bool PLCollision(cocos2d::Vec2 pos, cocos2d::TMXTiledMap* map, cocos2d::TMXLayer* lay);//頂点を判定して当たっていたらtrueを返す
	CREATE_FUNC(Player);

private:
	std::unique_ptr<OPRT_State> oprt_state;
	input_data data;
	bool reverseFlag;						//画像を左右反転させるかフラグ（true反転、falseなし）
	cocos2d::Vec2 speed;					//プレイヤーの移動スピード
};

