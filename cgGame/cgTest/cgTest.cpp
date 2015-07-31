// cgTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "..\cgSimpleThread\cgSimpleThread.h"
#include <Windows.h>
#include <stdlib.h>
#include "cgDownloadThread.h"
#include "cgDownloadManager.h"

using namespace std;


class cgTestDownloadListner:
	public cgDownloadListener
{
public:
	virtual bool OnDownloadProcess(const cgDownloadTask * pkDownloader)
	{
		if (!pkDownloader || pkDownloader->GetTotalSize() <= 0)
			return false;

		TCHAR szStr[CG_LONG_PATH_LEN];
		swprintf_s(szStr, CG_LONG_PATH_LEN, TEXT("file : %s\nprogress: %0.2f%%, size: %d/%d, speed: %d k/s"), 
			pkDownloader->GetUrl(),
			(pkDownloader->GetDownloadedSize()*1.0/pkDownloader->GetTotalSize()*100),
			pkDownloader->GetDownloadedSize(),
			pkDownloader->GetTotalSize(), 
			pkDownloader->GetSpeed()/1024);

		wcout<<szStr<<endl;

		return true;
	}
	virtual bool OnDownloadFinished(const cgDownloadTask * pkDownloader)
	{
		cout<<"File Download Success !"<<endl;

		return true;
	}
	virtual bool OnDownloadFailed(const cgDownloadTask * pkDownloader)
	{
		cout<<"File Download Failed !"<<endl;

		return true;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Begin"<<endl;
	{
		// http://dldir1.qq.com/qqfile/qq/QQ6.2/12179/QQ6.2.exe
		// http://img14.360buyimg.com/n7/g16/M00/0C/0C/rBEbRVONMegIAAAAAAEkxfo1a-wAACahgCq5FUAASTd504.jpg
	//	LPCTSTR lpctUrl = TEXT("http://cbup.6hgame.com/update/1.0.0.0261-1.0.0.0270patch.exe");
		LPCTSTR lpctUrl = TEXT("http://dldir1.qq.com/qqfile/qq/QQ6.7/13458/QQ6.7.exe");	
		LPCTSTR lpctSavePath = TEXT("f:/download/a.exe");

		cgTestDownloadListner kListner;
		cgDownloadManager kManager;
		kManager.SetDownloadListener(&kListner);

		kManager.DownloadFile(lpctUrl, lpctSavePath);
		/*for (int i = 0; i < 100; ++i)
		{
			TCHAR szSave[MAX_PATH];
			swprintf_s(szSave, MAX_PATH, TEXT("f:/download/a_%d.jpg"), i);
			kManager.DownloadFile(TEXT("http://img14.360buyimg.com/n7/g16/M00/0C/0C/rBEbRVONMegIAAAAAAEkxfo1a-wAACahgCq5FUAASTd504.jpg"),
				szSave);
		}
		*/

		while (kManager.GetDownloadNum())
		{
			kManager.Update(0);
			cout<<"total Speed :"<<kManager.GetTotalSpeed()<<endl;
			Sleep(100);
		}
	}

	cout<<"Done !"<<endl;
	system("pause");
	return 0;
}

