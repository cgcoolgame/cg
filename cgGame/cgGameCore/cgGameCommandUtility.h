#ifndef cgGameCommandUtility_h__
#define cgGameCommandUtility_h__

#include "cgGameCommand.h"

// 预定义的一些游戏命令
// ----------------------------------------------------------------------------
// 修改fps
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
// 关闭或者取消fps
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
// 切换显示fps
// 关闭或者取消fps
class cgGameCommand_ToggleFps:
	public cgGameCommand
{
public:
	bool Execute();
	bool Unexecute();
};

// ----------------------------------------------------------------------------

#endif // cgGameAppCommand_h__
