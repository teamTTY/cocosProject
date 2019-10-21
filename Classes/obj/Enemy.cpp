#include "Enemy.h"
#include "Animation/AnimCtl.h"

Enemy * Enemy::createPlayer()
{
	return Enemy::create();
}

Enemy::Enemy()
{
	lpAnimCtl.Init(this);
}


Enemy::~Enemy()
{
}

void Enemy::update(float frame)
{
	lpAnimCtl.SetAnimSt(this, ANIM_ST::IDLE);
}
