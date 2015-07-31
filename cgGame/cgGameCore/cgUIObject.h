#ifndef cgUIObject_h__
#define cgUIObject_h__

#include "cggameobject.h"
#include "cgUIObjectDef.h"
#include <cgImage.h>
#include "cgGameSprite.h"
#include "cgGameText.h"

struct cgUIEventListener;

class cgUIObject :
	public cgGameObject
{
public:
	cgUIObject(void);
	cgUIObject(const string & strName);
	~cgUIObject(void);

	// 设置监听器
	void SetEventListener(cgUIEventListener * pkListener);

	// 光标
	void SetCursor(const string & strCursor);
	const string& GetCursor()const;

	// 背景颜色
	void SetBackColor(cgColor color);
	cgColor GetBackColor()const;

	// 边框颜色
	void SetBorderColor(cgColor color);
	cgColor GetBorderColor()const;

	// 绘制标记
	cgUIObjectDrawFlag GetDrawFlag()const;
	void SetDrawFlag(cgUIObjectDrawFlag flag);

	// 图片
	void SetBackImage(const cgString& strPath, bool autoFitSize = false);
	void SetBackImage(cgImagePtr spImage, bool autoFitSize = false);

	// 设置默认文字
	void SetText(const cgString & strText);
	const cgString& GetText();

	cgGameSpiritPtr GetBackImageObject();
	cgGameTextPtr GetTextObject();

protected:
	// 初始化
	void SetupParams();

	// 尺寸变化
	virtual void OnSizeChanged();

	// 绘制
	virtual void DoRenderSelf(cgCamera * renderCamera);
	void DrawBackground(cgCamera * renderCamera);
	void DrawBorder(cgCamera * renderCamera);

	// 消息处理，重载自gameobject
	virtual bool DoProcessEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

	// ui消息的处理分支，用于重载，简单粗暴！！！！
	virtual void DoProcessMouseEnter(int firstParam, int secondParam);
	virtual void DoProcessMouseOut(int firstParam, int secondParam);
	virtual void DoProcessMouseDown(int firstParam, int secondParam);
	virtual void DoProcessMouseUp(int firstParam, int secondParam);
	virtual void DoProcessMouseMove(int firstParam, int secondParam);
	virtual void DoProcessMouseWheel(int firstParam, int secondParam);
	virtual void DoProcessDbClick(int firstParam, int secondParam);
	virtual void DoProcessGainFocus(int firstParam, int secondParam);
	virtual void DoProcessLostFocus(int firstParam, int secondParam);
	virtual void DoProcessInputChar(int firstParam, int secondParam);
	virtual void DoProcessCopy(int firstParam, int secondParam);
	virtual void DoProcessCut(int firstParam, int secondParam);
	virtual void DoProcessPaste(int firstParam, int secondParam);

protected:
	string m_strCursor;
	// 绘制相关
	cgColor m_uBackColor;
	cgColor m_uBorderColor;
	cgUIObjectDrawFlag m_uDrawFlag;

	// 背景图片
	cgGameSpiritPtr m_spBackImage;
	cgString m_strText;
	cgGameTextPtr m_spTextObject;

	// 监听器
	cgUIEventListener * m_pkEventListner;
};

typedef cgSmartPointer<cgUIObject> cgUIObjectPtr;

#endif // cgUIObject_h__
