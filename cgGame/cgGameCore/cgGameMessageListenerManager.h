#include "cgSingleton.h"
#include <list>
#include "cgGameMessage.h"

#ifndef cgGameMessageListenerManager_h__
#define cgGameMessageListenerManager_h__

// ��Ϸ�ڲ���Ϣ�����߽ӿ�
class  cgGameMessageListener
{
public:
	// ����ֵ�����Ƿ�Ե���������ˣ�ʵ�ʻ������
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

	// ���£����ӿ�
	void Update(float fTime);

	// ��Ӻ�ɾ��
	void AddListener(cgGameMessageListener * pkListener);
	void DelListener(cgGameMessageListener * pkListener);

	// �ַ���Ϣ
	bool DispatchGameMessage(cgGameMessage msg, void * pData = NULL, int nLen = 0);

private:
	cgGameMessageListenerList m_kListenerList;
};

#endif // cgGameMessageListenerManager_h__
