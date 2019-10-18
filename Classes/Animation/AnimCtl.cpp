#include "AnimCtl.h"

std::unique_ptr<AnimCtl, AnimCtl::AnimCtlDeleter> AnimCtl::s_instance(new AnimCtl());

AnimCtl::AnimCtl()
{
}

AnimCtl::~AnimCtl()
{
}

void AnimCtl::Init(cocos2d::Node* nd)
{
	animSt = ANIM_ST::IDLE;
	InitAnim(nd);
}

void AnimCtl::AddSprite(cocos2d::Animation* anim, std::string filename)
{
	anim->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(filename));
}

cocos2d::Action* AnimCtl::GetAct()
{	
	cocos2d::Animation* ani = cocos2d::AnimationCache::getInstance()->getAnimation(animName[static_cast<int>(animSt)]);
	ani->setDelayPerUnit(0.08f);
	ani->setRestoreOriginalFrame(true);
	cocos2d::Action* act = cocos2d::RepeatForever::create(cocos2d::Animate::create(ani));
	action = act;
	return act;
}

ANIM_ST AnimCtl::GetAnimSt()
{
	return animSt;
}

void AnimCtl::SetAnimSt(cocos2d::Node* nd, ANIM_ST anim)
{	
	if (animSt != anim)
	{
		nd->stopAction(action);
		animSt = anim;
	}
}

void AnimCtl::InitAnim(cocos2d::Node* nd)
{
	int animCnt = 0;

	for (auto name : animName)
	{
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/Sprites/player/player-" + name + "/sprites.plist");
		animInfo[animCnt] = cocos2d::Animation::create();
		if (name == "shoot-up" || name == "cling" || name == "duck")
		{
			AddSprite(animInfo[animCnt], "player-" + name + ".png");
		}
		else
		{
			for (int num = 1; num <= animFrameNum[animCnt]; num++)
			{
				AddSprite(animInfo[animCnt], "player-" + name + "-" + std::to_string(num) + ".png");
			}
		}
		animInfo[animCnt]->setDelayPerUnit(0.08f);
		animInfo[animCnt]->setRestoreOriginalFrame(true);
		cocos2d::AnimationCache::getInstance()->addAnimation(animInfo[animCnt], name);
		animCnt++;
	}

	nd = cocos2d::Sprite::createWithSpriteFrameName("player-idle-1.png");
}
