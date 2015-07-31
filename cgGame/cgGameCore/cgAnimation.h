#ifndef cgAnimation_h__
#define cgAnimation_h__

#include "cgImageSequence.h"

// 简单的帧动画动作

// ----------------------------------------------------------------
// 动画方向暂时支持四个方向
enum cgDirectionEnum
{
	cgFront ,			
	cgLeft ,
	cgRight,
	cgBack,
	cgFrontLeft,
	cgFrontRight,
	cgBackLeft,
	cgBackRight,
	cgDirectionEnumMax,
};

// 动作
class cgAnimation:
	public cgGameObject
{
public:
	cgAnimation(void);
	~cgAnimation(void);

	// 每个动作都有一个id，不是全局唯一，而是在当前动作组（一个角色）唯一
	void SetID(cgID id);
	cgID GetID();

	// 添加一个序列帧
	void AddSequence(cgImageSequencePtr spSequence, cgDirectionEnum enmDir);
	cgImageSequencePtr GetSequence(cgDirectionEnum enmDir);

	// 设置当前的方向
	void SetDirection(cgDirectionEnum enmDir);
	cgDirectionEnum GetDirection();

	// 获取当前序列帧
	cgImageSequencePtr GetCurSequence();

	// 动作频率
	void SetFrequence(float fFreq);
	float GetFrequence();

protected:
	cgImageSequencePtr m_kSequenceList[cgDirectionEnumMax];
	cgImageSequencePtr m_spCurSequence;

	cgDirectionEnum m_enmDir;
	cgID m_id;
	float m_fFrequence;	// 频率，默认为1.0f
};

typedef cgSmartPointer<cgAnimation> cgAnimationPtr;
#endif // cgAnimation_h__
