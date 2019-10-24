#pragma once
#include "cocos2d.h"

#if (_DEBUG && (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32))
#include <windows.h>
//�����̕������R���\�[���ɏo�͂���
#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)//...���C�ӂ̘A������������(�ψ���)�A_���΂炵�Ă����B
//�f�o�b�O���b�Z�[�W��\�����邽�߂̒�`
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "�A�T�[�g�\��", MB_OK);\
	}

class _DebugConOut
{
public:
	static _DebugConOut& GetInstance()
	{
		static _DebugConOut s_Instance;
		return s_Instance;
	}

private:
	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
};
#else
#define TRACE(fmt, ...)
#define AST()
#endif

