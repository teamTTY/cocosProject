#ifdef _DEBUG
#include "_DebugConOut.h"

_DebugConOut::_DebugConOut()
{
	HWND hWnd = GetForegroundWindow();				//�O�ɂ���window�̃n���h�����擾
	AllocConsole();									//�R���\�[���\��
	SetForegroundWindow(hWnd);						//�ŏ��ɐݒ肵��window��O�ɂ���
	freopen_s(&_debugFp, "CONOUT$", "w", stdout);	//������̏o��
	freopen_s(&_debugFp, "CONIN$", "r", stdin);		//������̓���
}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();	//�R���\�[���폜
}

#endif
