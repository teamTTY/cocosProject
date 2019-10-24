#pragma once
#include "input/OPRT_Key.h"
#include "input/OPRT_Touch.h"
#include "Animation/AnimCtl.h"
#include "CollisionCheck.h"
#include "cocos2d.h"
#include <memory>

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();			//クラスを生成
	Player();
	~Player();
	void update(float frame);				//毎フレーム更新関数（引数：float単位のフレーム数）
	void PlCollision(cocos2d::Vec2 tmpPos);
	CREATE_FUNC(Player);

private:
	std::unique_ptr<OPRT_State> oprt_state;	//OPRT_Stateクラスのメンバーを呼ぶ用のポインター
	input_data data;						//入力されたデータを取り出す変数
	bool reverseFlag;						//画像を左右反転させるかフラグ（true反転、falseなし）
	cocos2d::Vec2 speed;					//移動速度
	CollisionCheck* col;					//当たり判定呼び出しポインター
	bool plColFlg;							//当たり判定で当たっていたかどうかを保存する変数
	cocos2d::Vec2 offsetPos;				//当たり判定する座標のオフセットを指定（丁度いいサイズ）
};