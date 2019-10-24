#include "CollisionCheck.h"

bool CollisionCheck::operator()(cocos2d::Vec2 pos)const
{
	//DirectorからTMXTiledMapの情報を取得
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
	//取得したTMXTiledMapの情報内のTMXLayer型のレイヤー情報を取得
	auto lay = (cocos2d::TMXLayer*)map->getLayer("ground");

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//画面の範囲外まで移動していたら進まないようにする
	if (pos.x < 0 || pos.x > visibleSize.width || pos.y < -map->getTileSize().height - 1 || pos.y > visibleSize.height)
	{
		return true;
	}

	uint32_t tile;
	//現在の座標をマス目単位になおす
	float tileX = pos.x / map->getTileSize().width;
	float tileY = (map->getMapSize().height - 1) - (pos.y / map->getTileSize().height);
	//引数で指定したマス目の情報をtileに入れる
	tile = lay->getTileGIDAt(cocos2d::Vec2((int)tileX, (int)tileY));
	if (tile)
	{
		auto properties = map->getPropertiesForGID(tile).asValueMap();
		if (properties.at("col").asInt() == 1)
		{
			//タイルのcolの情報が1(矩形判定用)であればtrueを返す
			return true;
		}
	}

	return false;
}
