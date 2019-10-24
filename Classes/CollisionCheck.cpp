#include "CollisionCheck.h"

bool CollisionCheck::operator()(cocos2d::Vec2 pos)const
{
	//Director����TMXTiledMap�̏����擾
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
	//�擾����TMXTiledMap�̏�����TMXLayer�^�̃��C���[�����擾
	auto lay = (cocos2d::TMXLayer*)map->getLayer("ground");

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//��ʂ͈̔͊O�܂ňړ����Ă�����i�܂Ȃ��悤�ɂ���
	if (pos.x < 0 || pos.x > visibleSize.width || pos.y < -map->getTileSize().height - 1 || pos.y > visibleSize.height)
	{
		return true;
	}

	uint32_t tile;
	//���݂̍��W���}�X�ڒP�ʂɂȂ���
	float tileX = pos.x / map->getTileSize().width;
	float tileY = (map->getMapSize().height - 1) - (pos.y / map->getTileSize().height);
	//�����Ŏw�肵���}�X�ڂ̏���tile�ɓ����
	tile = lay->getTileGIDAt(cocos2d::Vec2((int)tileX, (int)tileY));
	if (tile)
	{
		auto properties = map->getPropertiesForGID(tile).asValueMap();
		if (properties.at("col").asInt() == 1)
		{
			//�^�C����col�̏��1(��`����p)�ł����true��Ԃ�
			return true;
		}
	}

	return false;
}
