#include <windows.h>

#ifndef CGFileDownloader_h__
#define CGFileDownloader_h__

#define CG_DOWNLOAD_MAX_FILE_PATH_LEN 512

enum enmCGDownloadState
{
	enmCGDownloadStateUnstart = 0,		// δ����״̬
	enmCGDownloadStateDownloading = 1,	// ������
	enmCGDownloadStateFinished = 2,		// �Ѿ����
	enmCGDownloadStateFailed = 3,		// ����ʧ��
	// --------------------------------------
	// ��ʱ�õ����漸�����������������
	enmCGDownloadStatePaused = 4,
	enmCGDownloadStateStopped = 5,
};

class CCGFileDownloader
{
public:
	CCGFileDownloader(void);
	~CCGFileDownloader(void);

public:

	// �������� url = www.onlinedown.net/newhuagg/newhua012.jpg
	// ����Ŀ¼ destdir = d:/download, ��ô��
	// website = www.onlinedown.net
	// ��� url = newhuagg/newhua012.jpg
	// filename = newhua012.jpg
	// destpath = d:/download/newhua012.jpg
	// ������Ҫ����������ŵ�����

	// ÿ����������̫�����ˣ�Ūһ�����ϲ����ĺ���
	void Download(LPCTSTR lpctWeb, LPCTSTR lpctSrcUrl, LPCTSTR lpctDestPath);

	// ��ȡ����ϸ��
	void GetDownloadDetail(enmCGDownloadState& enmState, DWORD& dwTotalSize, DWORD& dwDownloadSize);

	// ֹͣ
	void Stop();

protected:
	// �����߳�
	static  DWORD WINAPI DoDownload(void * pParam);

	// ���õ�ǰ�ļ��ܴ�С
	void SetTotalSize(DWORD dwSize);

	// ��ȡ�����صĴ�С
	void SetDownloadedSize(DWORD dwSize);

	// ��������״̬
	void SetState(enmCGDownloadState enmState);

	// ������վ������������һ���˿ڵķ���
	void SetWebSite(LPCTSTR lpctWebsite);

protected:
	enmCGDownloadState m_enmDownloadState;
	DWORD m_dwTotalFileSize;
	DWORD m_dwDownloadedSize;
	// �����������������̶߳�Ҫ���ʵ�

	// ����Ķ����������̰߳�ȫ���⡣
	TCHAR m_szWebSite[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	TCHAR m_szSrcUrl[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	TCHAR m_szDestFilePath[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	WORD m_iPort;

	// �߳���Ϣֻ���Լ����Է���
	HANDLE m_hDownloadThread;

};
#endif // CGFileDownloader_h__

