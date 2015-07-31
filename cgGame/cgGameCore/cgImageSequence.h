
#ifndef cgImageSequence_h__
#define cgImageSequence_h__


// 用于实现图片序列帧，最简单的动作等。

#include "cgImage.h"
#include <vector>
#include "cgGameObject.h"
#include "cgGameSprite.h"

class cgImageFrame:
	public cgRefObject
{
public:
	cgImageFrame();
	cgImageFrame(cgImagePtr spImage, float fDuration);

	// 设置此帧图片
	void SetImage(cgImagePtr spImage);
	cgImagePtr GetImage();

	// 设置此帧时间长度
	void SetDuration(float fDuration);
	float GetDuration();

	// 偏移，有些帧不是严格对齐的。
	void SetFrameOffset(float xOff, float yOff);

	float GetFrameOffsetX();
	float GetFrameOffsetY();

protected:

	// 图片资源
	cgImagePtr m_spImage;

	// 此帧时长
	float m_fDuration;

	// 帧偏移
	float m_fOffX;
	float m_fOffY;
};

typedef cgSmartPointer<cgImageFrame> cgImageFramePtr;
typedef std::vector<cgImageFramePtr>	cgImageFramePtrList;

// 图片序列帧
class cgImageSequence:
	public cgGameObject
{
public:
	cgImageSequence();

	// 更新
	virtual void DoUpdateSelf(float fDeltaTime);

	// 添加一帧
	void AddFrame(cgImageFramePtr spFrame);

	// 重置
	void Reset();

	// 获取当前Frame的序号
	unsigned GetCurFrameIndex();

	// 强制设置当前帧
	void SetCurFrameIndex(unsigned uIndex);

protected:

	// 获取某一帧
	cgImageFramePtr GetFrameByIndex(unsigned uIndex);

protected:
	cgImageFramePtrList m_kFrameList;
	unsigned m_uCurFrameIndex;
	float m_fSequenceTime;
	cgGameSpiritPtr m_spCurImage;
};

typedef cgSmartPointer<cgImageSequence> cgImageSequencePtr;

#endif // cgImageSequence_h__
