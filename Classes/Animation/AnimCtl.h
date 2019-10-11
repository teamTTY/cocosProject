#pragma once
#include "cocos2d.h"
#include "../2d/CCNode.h"
#include <array>
#include <memory>
#include <utility>
#include <string>

enum class ANIM_ST {
	
	HUNT,
	IDLE,
	JUMP,
	RUN,
	RUN_SHOT,
	STAND,
	SHOOT_UP,	//Ç±Ç±Ç©ÇÁ1ÉRÉ}
	CLING,
	DUCK,
	MAX
};

using AnimInfo = std::array<cocos2d::Animation*, static_cast<int>(ANIM_ST::MAX)>;
#define lpAnimCtl AnimCtl::GetInstance()

class AnimCtl
{
public:
	static AnimCtl& GetInstance() 
	{
		return *s_instance;
	}
	void Init(cocos2d::Node* nd);
	void AddSprite(cocos2d::Animation* anim, std::string filename);
	cocos2d::Action* GetAct();
	ANIM_ST GetAnimSt();
	void SetAnimSt(cocos2d::Node* nd, ANIM_ST anim);
	void InitAnim(cocos2d::Node* nd);

private:
	struct AnimCtlDeleter
	{
		void operator()(AnimCtl* animCtl) const
		{
			delete animCtl;
		}
	};
	AnimCtl();
	~AnimCtl();

	static std::unique_ptr<AnimCtl, AnimCtlDeleter> s_instance;
	ANIM_ST animSt;
	AnimInfo animInfo;
	cocos2d::Sprite* sprite;
	cocos2d::Action* action;
	int animFrameNum[static_cast<int>(ANIM_ST::MAX)] = {2, 4, 6, 10, 10, 3, 1, 1, 1};
	std::string animName[static_cast<int>(ANIM_ST::MAX)] = { "hurt", "idle", "jump", "run", "run-shot", "stand", "shoot-up", "cling", "duck" };
};

