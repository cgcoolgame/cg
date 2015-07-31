#ifndef cgGameCommandUtility_h__
#define cgGameCommandUtility_h__

#include "cgGameCommand.h"

// Ԥ�����һЩ��Ϸ����
// ----------------------------------------------------------------------------
// �޸�fps
class cgGameCommand_ChangeMaxFps:
	public cgGameCommand
{
public:
	cgGameCommand_ChangeMaxFps(int nNewFps);
	~cgGameCommand_ChangeMaxFps();

	bool Execute();
	bool Unexecute();
private:
	int m_nNewFps;
	int m_nOldFps;
};

// ----------------------------------------------------------------------------
// �رջ���ȡ��fps
class cgGameCommand_ShowFps:
	public cgGameCommand
{
public:
	cgGameCommand_ShowFps(bool bShow);

	bool Execute();
	bool Unexecute();

private:
	bool m_bShowFps;
	bool m_bOriginShowFps;
};


// ----------------------------------------------------------------------------
// �л���ʾfps
// �رջ���ȡ��fps
class cgGameCommand_ToggleFps:
	public cgGameCommand
{
public:
	bool Execute();
	bool Unexecute();
};

// ----------------------------------------------------------------------------

#endif // cgGameAppCommand_h__
