
#ifndef cgAnimationUtility_h__
#define cgAnimationUtility_h__
#include "cgImageSequence.h"
#include "cgAnimation.h"
#include "cgActor.h"

// 从一个图片加载一个序列帧
cgImageSequencePtr cgXLoadSequenceFromImage(cgImagePtr spImage, float fFrameDuration, int nFrameNum, 
	int nXOff, int nYOff, int nFrameWith, int nFrameHeight);

// 从一个图片文件中加载一个动作
cgAnimationPtr cgXLoadAnimationFromFile(LPCTSTR lpctPath, int nFramePerSequence, int nDirectionNum, float fFrameDuration);


// ------------------------------------------------------------------------------------------

// 从一个定义好的文件中加载一个动作组，理论上不应该出现在这里
cgActorPtr cgXLoadActor(const char * path);


#endif // cgFrameSequenceUtility_h__
