#ifndef cgTestUILoader_h__
#define cgTestUILoader_h__

#include "cguiloader.h"
#include <cgUIManager.h>

class cgTestUILoader :
	public cgUILoader,
	public cgUIEventListenerEx
{
public:
	cgTestUILoader(void);
	~cgTestUILoader(void);

	virtual cgUIWidgetPtr LoadScreen(const char * pcScreen);
	virtual cgUIWidgetPtr LoadDynamic(const char * pcID);

	virtual bool OnUIEvent(cgUIWidgetPtr spComponent, 
		cgUIEvent enmEvent, unsigned wparam, unsigned lparam);

protected:
	void ChangeProgress(int change);

	void ChangeWeb();
	void ParseRichText();
protected:

};

#endif // cgTestUILoader_h__
