#include "Enemy.h"
#include "Animation/AnimCtl.h"

Enemy * Enemy::createEnemy()
{
	return Enemy::create();
}

Enemy::Enemy()
{
	lpAnimCtl.Init(this);
	runAction(lpAnimCtl.GetAct());
	setPosition(100, 300);
	scheduleUpdate();
}


Enemy::~Enemy()
{
}

void Enemy::update(float frame)
{
	//アニメーションしていなければ（ちゃんと止まっていたら）
	if (numberOfRunningActions() == 0)
	{
		//reverseFlagがtrueだったら反転する
		runAction(lpAnimCtl.GetAct());
	}
}
