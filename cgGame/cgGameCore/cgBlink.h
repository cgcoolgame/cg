#ifndef cgBlink_h__
#define cgBlink_h__


#include "cgaction.h"
class cgBlink :
	public cgAction
{
public:
	cgBlink(void);
	cgBlink(float blinkFreq, float binkTime);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	float m_fBlinkFreq;
	float m_fBlinkTime;
	float m_fBlinkTimeSpace; // 
	float m_fBlinkDeltaTime;
};

#endif // cgBlink_h__
