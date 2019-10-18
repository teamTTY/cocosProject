#pragma once
#include "cocos2d.h"
#include "../2d/CCNode.h"
#include <array>
#include <memory>
#include <utility>
#include <string>

//�A�j���[�V�����̎��
enum class ANIM_ST {
//�����R�}�A�j���[�V����	
	HUNT,		//�U����H�����
	IDLE,		//�҂����
	JUMP,		//�W�����v
	RUN,		//����
	RUN_SHOT,	//����Ȃ��猂��
	STAND,		//�e���\���ė���
//1�R�}�A�j���[�V����
	SHOOT_UP,	//������Ɍ���
	CLING,		//�o��
	DUCK,		//���Ⴊ�ݍ\����
	MAX
};

#define lpAnimCtl AnimCtl::GetInstance()//AnimCtl���O������Q�Ƃ���ۂɒZ���R�[�h�ŏ������߂̒�`
using AnimInfo = std::array<cocos2d::Animation*, static_cast<int>(ANIM_ST::MAX)>;//�A�j���[�V�������A�A�j���[�V�����̎��

class AnimCtl
{
public:
	static AnimCtl& GetInstance()	//�O������public�Ȋ֐����Ăяo���p�̃Q�b�^�[
	{
		return *s_instance;			//���g�̃N���X�̃|�C���^�[��Ԃ�
	}
	void Init(cocos2d::Node* nd);									//�������֐��@					�@�i�����FNode�N���X���p�����Ă���N���X�̃|�C���^�[�j
	void AddSprite(cocos2d::Animation* anim, std::string filename);	//�X�v���C�g��ǉ��i�o�^�j���Ă����i�����F�A�j���[�V�������ƁA"�摜��.png"�j
	cocos2d::Action* GetAct();										//�A�j���[�V���������擾�ł���@�i�Ԃ�l�F�A�j���[�V������񂪓����Ă���ꏊ�ւ̃|�C���^�[�j
	ANIM_ST GetAnimSt();											//���݂̃A�j���[�V������������Ԃ��i�Ԃ�l�Fenumclass��ANIM_ST�^�j
	void SetAnimSt(cocos2d::Node* nd, ANIM_ST anim);				//�ς������A�j���[�V������ݒ肷��i�����FNode�N���X���p�����Ă���N���X�̃|�C���^�[�A�ς������A�j���[�V������enumclass��ANIM_ST�^�j
	void InitAnim(cocos2d::Node* nd);								//�ŏ���Init���ɂP��̂݃A�j���[�V�����̏���ݒ肷��i�����FNode�N���X���p�����Ă���N���X�̃|�C���^�[�j

private:
	struct AnimCtlDeleter	//unique_ptr�p�̎���f�X�g���N�^�[
	{
		void operator()(AnimCtl* animCtl) const
		{
			delete animCtl;
		}
	};
	AnimCtl();
	~AnimCtl();
	static std::unique_ptr<AnimCtl, AnimCtlDeleter> s_instance;

	ANIM_ST animSt;			//���݃A�j���[�V�����̎�ނ�ێ�����
	AnimInfo animInfo;		//�A�j���[�V�������A�A�j���[�V�����̎�ނ�ێ�����
	cocos2d::Sprite* sprite;//�X�v���C�g��������
	cocos2d::Action* action;//�A�j���[�V������������
	//�S�A�j���[�V�����̃t���[�������i�[
	int animFrameNum[static_cast<int>(ANIM_ST::MAX)] = {2, 4, 6, 10, 10, 3, 1, 1, 1};
	//�S�A�j���[�V�����̖��O���i�[
	std::string animName[static_cast<int>(ANIM_ST::MAX)] = { "hurt", "idle", "jump", "run", "run-shot", "stand", "shoot-up", "cling", "duck" };
};