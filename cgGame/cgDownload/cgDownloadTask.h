#include "cgDownloadThread.h"
// һ�����������Ƕ������̵߳�һ�η�װ�����̵߳Ĺ���Ӧ�þ�����һ
// ���Ը���ͳ�����ݶ��ŵ��������������棬����໹���𱣴�������Ϣ����

#ifndef CGDownloadTask_h__
#define CGDownloadTask_h__

struct cgDownloadProgress
{
	unsigned uTotalSize;
	unsigned uDownloadSize;
	unsigned uSpeed;
	int nState;
	int nDownloadResult;
};

class cgDownloadTask
{
public:
	cgDownloadTask(unsigned uDownloadID, LPCTSTR lpctUrl, LPCTSTR lpctDestPath);
	~cgDownloadTask(void);

	// ��ʼ����
	void Start();

	// ���¿���
	void Update(float fTime);

	// �Ƿ����
	bool IsFinished();

	// ���ؽ��
	int GetDownloadResult();

	// �ٶ����
	DWORD GetSpeed()const;

	// ��ǰ�ܴ�С����
	DWORD GetTotalSize()const;

	// �����ش�С����
	DWORD GetDownloadedSize()const;

	unsigned GetID()const;

	// Դ�ļ����·��
	LPCTSTR GetUrl() const;

	// Ŀ���ļ�·��
	LPCTSTR GetSavePath() const;
protected:
	cgDownloadThread* m_pkDownloadThread; // ����������

	unsigned m_uID;
	TCHAR m_szUrl[CG_LONG_PATH_LEN];
	TCHAR m_szSavePath[CG_LONG_PATH_LEN];

	// ���ؿ���
	DWORD m_dwTotalFileSize;
	DWORD m_dwDownloadedSize;
	DWORD m_dwSpeed;

	bool m_bIsFinished;
	int m_nDownloadResult;
};
#endif // CGDownloadTask_h__

