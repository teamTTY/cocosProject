#include "Player.h"
#include "../_DebugConOut.h"

Player * Player::createPlayer()
{
	/*Player* player = new(std::nothrow)Player();
	if (player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return player;*/
	return Player::create();
}

Player::Player()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	lpAnimCtl.Init(this);
	setPosition(cocos2d::Vec2(visibleSize.width / 2 + origin.x + visibleSize.width / 6, visibleSize.height / 2 + origin.y));
	runAction(lpAnimCtl.GetAct());
	reverseFlag = false;
	speed = cocos2d::Vec2(3, 3);
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

	cocos2d::Vec2 tmpPos = getPosition();

	//DirectorからTMXTiledMapの情報を取得
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
	//取得したTMXTiledMapの情報内のTMXLayer型のレイヤー情報を取得
	auto lay = (cocos2d::TMXLayer*)map->getLayer("ground");


	
	//move processing
	if (data.button[static_cast<int>(ST::NOW)])
	{
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
		
		if (!PLCollision(tmpPos, map, lay))
		{
			//障害物に当たってなかったら移動する
			setPosition(tmpPos);
		}
	}
	else
	{
		//If nothing is done → state is IDLE
		lpAnimCtl.SetAnimSt(this, ANIM_ST::IDLE);
	}

	//アニメーションしていなければ（ちゃんと止まっていたら）
	if (numberOfRunningActions() == 0)
	{
		//if reverseFlag is true →　reverse
		runAction(cocos2d::FlipX::create(reverseFlag));
		runAction(lpAnimCtl.GetAct());
	}
}

bool Player::PLCollision(cocos2d::Vec2 pos, cocos2d::TMXTiledMap* map, cocos2d::TMXLayer* lay)
{
	//playerの当たり判定する座標を指定
	cocos2d::Vec2 diff = { 25, 120 };
	//左上、右上、左下、右下
	cocos2d::Vec2 leftUp = { pos.x - diff.x, pos.y };
	cocos2d::Vec2 rightUp = { pos.x + diff.x, pos.y };
	cocos2d::Vec2 leftDown = { pos.x - diff.x, pos.y - diff.y };
	cocos2d::Vec2 rightDown = { pos.x + diff.x, pos.y - diff.y };
	//autoで回すための当たり判定の頂点座標配列
	cocos2d::Vec2 rect[4] = { leftUp, rightUp, leftDown, rightDown };

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	//4頂点を判定し当たっていたらtrueを返す
	for (auto plPos : rect)
	{
		//画面の範囲外まで移動していたら進まないようにする
		if (plPos.x < 0 || plPos.x > visibleSize.width || plPos.y < -map->getTileSize().height - 1 || plPos.y > visibleSize.height)
		{
			return true;
		}
		//現在の座標をマス目単位になおす
		float tileX = plPos.x / map->getTileSize().width;
		float tileY = (map->getMapSize().height - 1) - (plPos.y / map->getTileSize().height);
		//引数で指定したマス目のところに何か置かれているかを見る
		int tile = lay->getTileGIDAt(cocos2d::ccp((int)tileX, (int)tileY));

		/*auto objGroup = map->getObjectGroup("obj")->getObjects();
		auto obj = objGroup.begin()->asValueMap();*/


		//何か情報が入っていればtrueを返す
		if (tile)
		{
			auto properties = map->getPropertiesForGID(tile).asValueMap();
			if (properties.at("col").asInt() == 1)
			{
				return true;
			}
		}
	}
	return false;
}
