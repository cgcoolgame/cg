#include "cgSingleton.h"
#include <list>
#include "cgGameMessage.h"

#ifndef cgGameMessageListenerManager_h__
#define cgGameMessageListenerManager_h__

// 游戏内部消息接受者接口
class  cgGameMessageListener
{
public:
	// 返回值代表是否吃掉，本意如此，实际还不清楚
	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen) = NULL;
};

typedef std::list<cgGameMessageListener*> cgGameMessageListenerList;

class cgGameMessageListenerManager:
	public cgSingleton<cgGameMessageListenerManager>
{
public:
	cgGameMessageListenerManager(void);
	~cgGameMessageListenerManager(void);

	bool Initialize();

	// 更新，留接口
	void Update(float fTime);

	// 添加和删除
	void AddListener(cgGameMessageListener * pkListener);
	void DelListener(cgGameMessageListener * pkListener);

	// 分发信息
	bool DispatchGameMessage(cgGameMessage msg, void * pData = NULL, int nLen = 0);

private:
	cgGameMessageListenerList m_kListenerList;
};

#endif // cgGameMessageListenerManager_h__
