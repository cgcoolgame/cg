
#ifndef cgAnimationUtility_h__
#define cgAnimationUtility_h__
#include "cgImageSequence.h"
#include "cgAnimation.h"
#include "cgActor.h"

// ��һ��ͼƬ����һ������֡
cgImageSequencePtr cgXLoadSequenceFromImage(cgImagePtr spImage, float fFrameDuration, int nFrameNum, 
	int nXOff, int nYOff, int nFrameWith, int nFrameHeight);

// ��һ��ͼƬ�ļ��м���һ������
cgAnimationPtr cgXLoadAnimationFromFile(LPCTSTR lpctPath, int nFramePerSequence, int nDirectionNum, float fFrameDuration);


// ------------------------------------------------------------------------------------------

// ��һ������õ��ļ��м���һ�������飬�����ϲ�Ӧ�ó���������
cgActorPtr cgXLoadActor(const char * path);


#endif // cgFrameSequenceUtility_h__
