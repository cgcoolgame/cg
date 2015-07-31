
#ifndef cgUIProgress_h__
#define cgUIProgress_h__

#include "cgUIWidget.h"

class cgUIProgress :
	public cgUIWidget
{
public:
	cgUIProgress(void);
	~cgUIProgress(void);

	// 设置进度条的图片
	void SetCoverImage(LPCTSTR cover);
	void SetCoverImage(cgID cover);

	// 设置进度条底边的图片
	void SetLayerImage(LPCTSTR layer);
	void SetLayerImage(cgID layer);

	// 设置瞄准器的图片
	void SetAimerImage(LPCTSTR aim);
	void SetAimerImage(cgID aim);

	// 设置当前范围
	void SetRange(int nRange);
	int GetRange()const;

	// 设置当前位置
	// bForceImmediate:强制设置位置，progress和aimmer瞬间同步，
	// 比如：初始化的时候就不希望看到进度条渐变
	void SetProgress(int nProgress, bool bForceImmediate = false);
	int GetProgress()const;

	// 设置瞄准器速度
	void SetAimerSpeed(float fSpeed);
	float GetAimerSpeed()const;

	// 设置瞄准器延时
	void SetAimerDelayTime(float fDelay);
	float GetAimerDelayTime()const;

	// 获取当前的瞄准器位置
	int GetAimerPos()const;

	// 是否立刻更新
	bool IsImmediate()const;
	void SetImmediate(bool bImmediate);

	// 是否是垂直
	bool IsVertical()const;
	void SetVertical(bool bVertical);

	// 底边颜色
	void SetLayerColor(cgColor color);
	cgColor GetLayerColor();

	// 进度条颜色
	void SetCoverColor(cgColor color);
	cgColor GetCoverColor();

protected:
	virtual void UpdateSelf(float fTime);

	// 更新瞄准器的位置
	void UpdateAimerPos(float fTime);

	//绘制背景图片
	virtual void DrawBackPic(const cgRectF& clipRect);

	// 三个图片绘制
	void DrawLayerImage(const cgRectF& clipRect);
	void DrawCoverImage(const cgRectF& clipRect);
	void DrawAimerImage(const cgRectF& clipRect);
protected:
	cgUIImagePtr m_spCoverImage;			// 最外层的进度图片
	cgUIImagePtr m_spLayerImage;		// 底层的图片，用于动态显示
	cgUIImagePtr m_spAimerImage;			// 瞄准器图片

	cgColor m_uCoverColor;
	cgColor m_uLayerColor;

	int	m_nRange;		// 范围（0-range）
	int m_nProgress;			// 当前位置

	float m_fAimerPos;		// 瞄准器位置
	float m_fAimerSpeed;		// 瞄准器的移动速度，在开启了渐进以后有用

	float m_fAimerDelayTime;		// 变化的delay时间

	float m_fLeftAimerDelayTime;		// 剩余的延时
	float m_fProgressChangeTime;	// 进度条进度变化时间
};

#endif // cgUIProgress_h__
