#ifndef cgButton_h__
#define cgButton_h__

#include "cgUIObject.h"
#include <cgImage.h>
#include "cgGameSprite.h"
#include "cgGameText.h"

class cgButton :
	public cgUIObject
{
public:
	cgButton(void);
	cgButton(const string & strName);
	cgButton(const string & strName, const cgVector& localPos, const cgSizeF& size);

	~cgButton(void);


protected:
	// ��ʼ��
	void SetupParams();

	// �¼�����
	virtual void DoProcessMouseEnter(int firstParam, int secondParam);
	virtual void DoProcessMouseOut(int firstParam, int secondParam);
	virtual void DoProcessMouseDown(int firstParam, int secondParam);
	virtual void DoProcessMouseUp(int firstParam, int secondParam);

};

#endif // cgButton_h__
