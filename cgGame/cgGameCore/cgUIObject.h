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

	// ���ü�����
	void SetEventListener(cgUIEventListener * pkListener);

	// ���
	void SetCursor(const string & strCursor);
	const string& GetCursor()const;

	// ������ɫ
	void SetBackColor(cgColor color);
	cgColor GetBackColor()const;

	// �߿���ɫ
	void SetBorderColor(cgColor color);
	cgColor GetBorderColor()const;

	// ���Ʊ��
	cgUIObjectDrawFlag GetDrawFlag()const;
	void SetDrawFlag(cgUIObjectDrawFlag flag);

	// ͼƬ
	void SetBackImage(const cgString& strPath, bool autoFitSize = false);
	void SetBackImage(cgImagePtr spImage, bool autoFitSize = false);

	// ����Ĭ������
	void SetText(const cgString & strText);
	const cgString& GetText();

	cgGameSpiritPtr GetBackImageObject();
	cgGameTextPtr GetTextObject();

protected:
	// ��ʼ��
	void SetupParams();

	// �ߴ�仯
	virtual void OnSizeChanged();

	// ����
	virtual void DoRenderSelf(cgCamera * renderCamera);
	void DrawBackground(cgCamera * renderCamera);
	void DrawBorder(cgCamera * renderCamera);

	// ��Ϣ����������gameobject
	virtual bool DoProcessEvent(cgGameObjectEvent eventType, int firstParam, int secondParam);

	// ui��Ϣ�Ĵ����֧���������أ��򵥴ֱ���������
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
	// �������
	cgColor m_uBackColor;
	cgColor m_uBorderColor;
	cgUIObjectDrawFlag m_uDrawFlag;

	// ����ͼƬ
	cgGameSpiritPtr m_spBackImage;
	cgString m_strText;
	cgGameTextPtr m_spTextObject;

	// ������
	cgUIEventListener * m_pkEventListner;
};

typedef cgSmartPointer<cgUIObject> cgUIObjectPtr;

#endif // cgUIObject_h__
