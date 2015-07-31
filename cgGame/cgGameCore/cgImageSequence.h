
#ifndef cgImageSequence_h__
#define cgImageSequence_h__


// ����ʵ��ͼƬ����֡����򵥵Ķ����ȡ�

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

	// ���ô�֡ͼƬ
	void SetImage(cgImagePtr spImage);
	cgImagePtr GetImage();

	// ���ô�֡ʱ�䳤��
	void SetDuration(float fDuration);
	float GetDuration();

	// ƫ�ƣ���Щ֡�����ϸ����ġ�
	void SetFrameOffset(float xOff, float yOff);

	float GetFrameOffsetX();
	float GetFrameOffsetY();

protected:

	// ͼƬ��Դ
	cgImagePtr m_spImage;

	// ��֡ʱ��
	float m_fDuration;

	// ֡ƫ��
	float m_fOffX;
	float m_fOffY;
};

typedef cgSmartPointer<cgImageFrame> cgImageFramePtr;
typedef std::vector<cgImageFramePtr>	cgImageFramePtrList;

// ͼƬ����֡
class cgImageSequence:
	public cgGameObject
{
public:
	cgImageSequence();

	// ����
	virtual void DoUpdateSelf(float fDeltaTime);

	// ���һ֡
	void AddFrame(cgImageFramePtr spFrame);

	// ����
	void Reset();

	// ��ȡ��ǰFrame�����
	unsigned GetCurFrameIndex();

	// ǿ�����õ�ǰ֡
	void SetCurFrameIndex(unsigned uIndex);

protected:

	// ��ȡĳһ֡
	cgImageFramePtr GetFrameByIndex(unsigned uIndex);

protected:
	cgImageFramePtrList m_kFrameList;
	unsigned m_uCurFrameIndex;
	float m_fSequenceTime;
	cgGameSpiritPtr m_spCurImage;
};

typedef cgSmartPointer<cgImageSequence> cgImageSequencePtr;

#endif // cgImageSequence_h__
