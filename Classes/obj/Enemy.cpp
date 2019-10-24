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
	//�A�j���[�V�������Ă��Ȃ���΁i�����Ǝ~�܂��Ă�����j
	if (numberOfRunningActions() == 0)
	{
		//reverseFlag��true�������甽�]����
		runAction(lpAnimCtl.GetAct());
	}
}
