#include "Player.h"
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOut.h"


Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player() : offsetPos(25, 120)
{
	//画面サイズと原点を取得
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	//アニメーションの初期化
	lpAnimCtl.Init(this);
	setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width / 6, visibleSize.height / 2 + origin.y));
	runAction(lpAnimCtl.GetAct());
	reverseFlag = false;
	plColFlg = false;
	speed = cocos2d::Vec2(3, 3);
	//プラットフォーム別に入力クラス（操作の仕方）を切り替える
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key());
#else
	oprt_state.reset(new OPRT_Touch());
#endif
	scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float frame)
{
	oprt_state->Update(this);
	data = oprt_state->GetData();

	//仮座標を持つ
	cocos2d::Vec2 tmpPos = getPosition();


	//何かしら入力があれば入る
	if (data.button[static_cast<int>(ST::NOW)])
	{
		//移動処理
		auto sp = cocos2d::Vec2(0, 0);
		if (data.dir == DIR::LEFT)
		{
			tmpPos.x -= speed.x;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = true;
		}
		else if (data.dir == DIR::RIGHT)
		{
			tmpPos.x += speed.x;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN);
			reverseFlag = false;
		}
		if (data.dir == DIR::UP)
		{
			tmpPos.y += speed.y;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::JUMP);
			reverseFlag = false;
		}
		else if (data.dir == DIR::DOWN)
		{
			tmpPos.y -= speed.y;
			lpAnimCtl.SetAnimSt(this, ANIM_ST::RUN_SHOT);
			reverseFlag = false;
		}
	}
	else
	{
		//移動していなければアニメーションをIDLEにする
		lpAnimCtl.SetAnimSt(this, ANIM_ST::IDLE);
	}

	//タイルとの当たり判定
	PlCollision(tmpPos);

	//アニメーションしていなければ次のアニメーションを開始させる
	if (numberOfRunningActions() == 0)
	{
		//reverseFlagがtrueだったら反転する
		runAction(cocos2d::FlipX::create(reverseFlag));
		runAction(lpAnimCtl.GetAct());
	}
}

void Player::PlCollision(cocos2d::Vec2 tmpPos)
{
	//空中にいたら常に落下させる
	tmpPos.y--;
	//下にブロックがあればそれ以上落とさない
	if (col->operator()(cocos2d::Vec2(tmpPos.x + offsetPos.x, tmpPos.y - offsetPos.y))
		|| col->operator()(cocos2d::Vec2(tmpPos.x - offsetPos.x, tmpPos.y - offsetPos.y)))
	{
		//ここで++してるのはめり込みを避けるため
		tmpPos.y++;
	}

	//左上、右上、左下、右下
	cocos2d::Vec2 leftUp = { tmpPos.x - offsetPos.x, tmpPos.y };
	cocos2d::Vec2 rightUp = { tmpPos.x + offsetPos.x, tmpPos.y };
	cocos2d::Vec2 leftDown = { tmpPos.x - offsetPos.x, tmpPos.y - offsetPos.y };
	cocos2d::Vec2 rightDown = { tmpPos.x + offsetPos.x, tmpPos.y - offsetPos.y };

	if (data.dir == DIR::LEFT)
	{
		//左2点どちらかが当たっている→true
		plColFlg = (col->operator()(leftUp) || col->operator()(leftDown));
	}
	else if (data.dir == DIR::RIGHT)
	{
		//右2点どちらかが当たっている→true
		plColFlg = (col->operator()(rightUp) || col->operator()(rightDown));
	}
	if (data.dir == DIR::UP)
	{
		//上2点どちらかが当たっている→true
		plColFlg = (col->operator()(leftUp) || col->operator()(rightUp));
	}
	else if (data.dir == DIR::DOWN)
	{
		//下2点どちらかが当たっている→true
		plColFlg = (col->operator()(leftDown) || col->operator()(rightDown));
	}

	//障害物に当たっていなかったら移動する
	if (!plColFlg)
	{
		setPosition(tmpPos);
	}
}
