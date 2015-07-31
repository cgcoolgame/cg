/********************************************************************
	created:	2014/08/24
	created:	24:8:2014   0:46
	filename: 	cgDownloadThread.h
	author:		Master
	
	purpose:	һ�������������߳�
*********************************************************************/
#ifndef cgDownloadThread_h__
#define cgDownloadThread_h__
#include <Windows.h>
#include "cgSimpleThread.h"
#include <wininet.h>

// �����õ���Url�ַ�������
#define CG_LONG_PATH_LEN 512

// Ĭ�����ص����ݻ���Ĵ�С
//#define CG_DEFAULT_DOWNLOAD_BUFFER_LEN 1024*512

// Ĭ�϶�ȡ�������ݵĻ����С
#define CG_DOWNLOAD_DATA_READ_BUFFER_LEN 64*1024

#define CG_DOWNLOAD_RESULT_UNDEFINED	-1 // �����ȷ����˵��δ��ʼ���أ����߻�û�������
#define CG_DOWNLOAD_RESULT_SUC 0		// ���سɹ�
#define CG_DOWNLOAD_RESULT_FAILED 1		// ����ʧ��

/*
 *	ÿһ��Url��Ӧһ�������̣߳�
 *	����ѡ�����ص��ڴ滹�����ص��ļ�
 *	�����Զ��建���С
 */
class cgDownloadThread:
	public cgSimpleThread
{
public:
	cgDownloadThread(LPCTSTR lpctSrcUrl, LPCTSTR lpctSavePath);

	virtual ~cgDownloadThread(void);

	LPCTSTR GetSrcUrl();
	LPCTSTR GetSavePath();

	// ��IsFinished����true֮ǰ������ķ���ֵ�����ο���
	unsigned GetTotalSize();
	unsigned GetDownloadSize();
	unsigned GetDownloadSpeed();

	// �������ؽ��,��IsFinished����true֮ǰ�����������Ч�ġ�
	int GetDownloadResult();

protected:
	// ��������
	virtual unsigned Run();

private:

	// ����
	unsigned DoDownload();

	// ����url
	bool ParseUrl(TCHAR * szWeb, unsigned uWebLen,
		TCHAR * szObject, unsigned uObjectLen,
		WORD & dwPort);

	// ����������������
	bool DonwloadData(HINTERNET hRequest);

	// ��ȡһ����������ʱ����
	bool OnReadData(void * pData, unsigned uDataSize);

private:
	TCHAR m_szUrl[CG_LONG_PATH_LEN];
	TCHAR m_szSavePath[CG_LONG_PATH_LEN];

	unsigned m_uTotalSize;
	unsigned m_uDownloadSize;

	DWORD m_dwLastTime;
	unsigned m_uDownloadSpeed;

	int m_nDownloadResult;
};

#endif // cgDownloadThread_h__
