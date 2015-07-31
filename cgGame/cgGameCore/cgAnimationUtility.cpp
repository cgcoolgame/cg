#include "StdAfx.h"
#include "cgAnimationUtility.h"
#include "cgSrcImageManager.h"
#include "cgTxtDataReader.h"
#include "cgStringTable.h"


cgImageSequencePtr cgXLoadImageSequenceFromFile( LPCTSTR lpctPath, int nSequenceNum, float fDuration )
{
	if (nSequenceNum <= 0)
		return NULL;

	cgImagePtr spBaseImage = cgSrcImageManager::Get()->LoadImage(lpctPath);
	if (!spBaseImage)
		return NULL;

	int nWidth = spBaseImage->GetWidth()/nSequenceNum;
	int nHeight = spBaseImage->GetHeight()/4;

	return cgXLoadSequenceFromImage(spBaseImage, fDuration, nSequenceNum, 0, 0, nWidth, nHeight);
}

cgImageSequencePtr cgXLoadSequenceFromImage( cgImagePtr spImage, float fFrameDuration, int nFrameNum, 
	int nXOff, int nYOff, int nFrameWith, int nFrameHeight )
{
	cgImageSequencePtr spSequence = new cgImageSequence;

	for (int i = 0; i < nFrameNum; ++i)
	{
		cgImagePtr spChild = cgImage::ClipFromImage(spImage, cgRectF(nXOff, nYOff, nFrameWith, nFrameHeight));
		spSequence->AddFrame(new cgImageFrame(spChild, fFrameDuration) );

		nXOff += nFrameWith;
	}

	return spSequence;
}

cgAnimationPtr cgXLoadAnimationFromFile( LPCTSTR lpctPath , int nFramePerSequence, int nDirectionNum, float fFrameDuration)
{
	if (nFramePerSequence <= 0 || nDirectionNum <= 0)
		return NULL;

	cgImagePtr spBaseImage = cgSrcImageManager::Get()->LoadImage(lpctPath);
	if (!spBaseImage)
		return NULL;

	cgAnimationPtr spAnim = new cgAnimation;
	int nFrameWidth = spBaseImage->GetWidth()/nFramePerSequence;
	int nFrameHeight = spBaseImage->GetHeight()/nDirectionNum;

	for (int i = 0; i < nDirectionNum; ++i)
	{
		cgImageSequencePtr spSequence = cgXLoadSequenceFromImage(spBaseImage, fFrameDuration, nFramePerSequence, 
			0, i*nFrameHeight, nFrameWidth, nFrameHeight);

		spAnim->AddSequence(spSequence, static_cast<cgDirectionEnum>(i));
	}

	return spAnim;
}

// ----------------------------------------------------------------------------------------


cgActorPtr cgXLoadActor( const char * path )
{
	cgTxtDataReader kReader;
	if (!kReader.Open(path))
		return NULL;

	cgActorPtr spActor = new cgActor;

	// 跳过第一行
	const cgTxtRecord * pkRecord = kReader.Next();

	char szImagePath[MAX_PATH] = {0};
	const char * pFind = strrchr(path, '/');
	size_t len = pFind-path+1;
	strncpy_s(szImagePath, MAX_PATH, path, len);
	while (pkRecord = kReader.Next())
	{
		int index = 0;
		cgID id = static_cast<cgID>(atoi(pkRecord->GetField(index++)));
		string strPath = (pkRecord->GetField(index++));
		int nFramePerSequence = atoi(pkRecord->GetField(index++));
		int nSequenceNum = atoi(pkRecord->GetField(index++));
		float fDuration = static_cast<float>(atoi(pkRecord->GetField(index++))/1000.0f);

		strcpy_s(szImagePath+len, MAX_PATH-len, strPath.c_str());
		cgAnimationPtr spAnim = cgXLoadAnimationFromFile(cgXUtf8TocgTxt(szImagePath), nFramePerSequence, nSequenceNum, fDuration);
		spAnim->SetID(id);
		spActor->AddAnimation(spAnim);
	}

	return spActor;
}
