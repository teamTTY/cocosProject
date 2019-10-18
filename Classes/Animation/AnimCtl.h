#pragma once
#include "cocos2d.h"
#include "../2d/CCNode.h"
#include <array>
#include <memory>
#include <utility>
#include <string>

//アニメーションの種類
enum class ANIM_ST {
//複数コマアニメーション	
	HUNT,		//攻撃を食らった
	IDLE,		//待ち状態
	JUMP,		//ジャンプ
	RUN,		//走る
	RUN_SHOT,	//走りながら撃つ
	STAND,		//銃を構えて立つ
//1コマアニメーション
	SHOOT_UP,	//上向きに撃つ
	CLING,		//登る
	DUCK,		//しゃがみ構える
	MAX
};

#define lpAnimCtl AnimCtl::GetInstance()//AnimCtlを外部から参照する際に短いコードで書くための定義
using AnimInfo = std::array<cocos2d::Animation*, static_cast<int>(ANIM_ST::MAX)>;//アニメーション情報、アニメーションの種類

class AnimCtl
{
public:
	static AnimCtl& GetInstance()	//外部からpublicな関数を呼び出す用のゲッター
	{
		return *s_instance;			//自身のクラスのポインターを返す
	}
	void Init(cocos2d::Node* nd);									//初期化関数　					　（引数：Nodeクラスを継承しているクラスのポインター）
	void AddSprite(cocos2d::Animation* anim, std::string filename);	//スプライトを追加（登録）していく（引数：アニメーション情報と、"画像名.png"）
	cocos2d::Action* GetAct();										//アニメーション情報を取得できる　（返り値：アニメーション情報が入っている場所へのポインター）
	ANIM_ST GetAnimSt();											//現在のアニメーションが何かを返す（返り値：enumclassのANIM_ST型）
	void SetAnimSt(cocos2d::Node* nd, ANIM_ST anim);				//変えたいアニメーションを設定する（引数：Nodeクラスを継承しているクラスのポインター、変えたいアニメーションのenumclassのANIM_ST型）
	void InitAnim(cocos2d::Node* nd);								//最初のInit時に１回のみアニメーションの情報を設定する（引数：Nodeクラスを継承しているクラスのポインター）

private:
	struct AnimCtlDeleter	//unique_ptr用の自作デストラクター
	{
		void operator()(AnimCtl* animCtl) const
		{
			delete animCtl;
		}
	};
	AnimCtl();
	~AnimCtl();
	static std::unique_ptr<AnimCtl, AnimCtlDeleter> s_instance;

	ANIM_ST animSt;			//現在アニメーションの種類を保持する
	AnimInfo animInfo;		//アニメーション情報、アニメーションの種類を保持する
	cocos2d::Sprite* sprite;//スプライト情報を入れる
	cocos2d::Action* action;//アニメーション情報を入れる
	//全アニメーションのフレーム数を格納
	int animFrameNum[static_cast<int>(ANIM_ST::MAX)] = {2, 4, 6, 10, 10, 3, 1, 1, 1};
	//全アニメーションの名前を格納
	std::string animName[static_cast<int>(ANIM_ST::MAX)] = { "hurt", "idle", "jump", "run", "run-shot", "stand", "shoot-up", "cling", "duck" };
};