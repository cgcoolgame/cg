#ifndef cgUIEventListener_h__
#define cgUIEventListener_h__

class cgUIObject;

// UI消息的监听器接口
struct cgUIEventListener
{
	virtual int OnMouseEnter(cgUIObject* eventSrc) = NULL;
	virtual int OnMouseOut(cgUIObject* eventSrc) = NULL;
	virtual int OnMouseDown(cgUIObject* eventSrc) = NULL;
	virtual int OnMouseUp(cgUIObject* eventSrc) = NULL;
	virtual int OnMouseMove(cgUIObject* eventSrc) = NULL;
	virtual int OnMouseWheel(cgUIObject* eventSrc) = NULL;
	virtual int OnDbClick(cgUIObject* eventSrc) = NULL;
	virtual int OnGainFocus(cgUIObject* eventSrc) = NULL;
	virtual int OnLostFocus(cgUIObject* eventSrc) = NULL;
	virtual int OnInputChar(cgUIObject* eventSrc) = NULL;
	virtual int OnCopy(cgUIObject* eventSrc) = NULL;
	virtual int OnCut(cgUIObject* eventSrc) = NULL;
	virtual int OnPaste(cgUIObject* eventSrc) = NULL;
};

// 防止每次都实现一堆虚函数
// 大概是这么个格式，根据需要再改进
struct cgUIEventListenerSample:
	public cgUIEventListener
{
	virtual int OnMouseEnter(cgUIObject* eventSrc){return 0;}
	virtual int OnMouseOut(cgUIObject* eventSrc){return 0;}
	virtual int OnMouseDown(cgUIObject* eventSrc){return 0;}
	virtual int OnMouseUp(cgUIObject* eventSrc){return 0;}
	virtual int OnMouseMove(cgUIObject* eventSrc){return 0;}
	virtual int OnMouseWheel(cgUIObject* eventSrc){return 0;}
	virtual int OnDbClick(cgUIObject* eventSrc){return 0;}
	virtual int OnGainFocus(cgUIObject* eventSrc){return 0;}
	virtual int OnLostFocus(cgUIObject* eventSrc){return 0;}
	virtual int OnInputChar(cgUIObject* eventSrc){return 0;}
	virtual int OnCopy(cgUIObject* eventSrc){return 0;}
	virtual int OnCut(cgUIObject* eventSrc){return 0;}
	virtual int OnPaste(cgUIObject* eventSrc){return 0;}
};

#endif // cgUIEventListener_h__
