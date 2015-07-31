#include "StdAfx.h"
#include "cgEngineTools.h"

bool cgXIsKeyPressed( DWORD dwKey )
{
	//return ::GetKeyState(dwKey)<0;
	return ::GetAsyncKeyState(dwKey)<0;
}


void cgXRotateAround( float & x, float & y, float fRotation, float fCenterX /*= 0.0f*/, float fCenterY /*= 0.0f*/ )
{
	double sinValue = sin(fRotation);
	double cosValue = cos(fRotation);
	double deltaX = x-fCenterX;
	double deltaY = y-fCenterY;

	x = fCenterX+deltaX*cosValue-deltaY*sinValue;
	y = fCenterY+deltaX*sinValue+deltaY*cosValue;
}

void cgXRotateAround( cgVector & v, float fRotation, const cgVector& center )
{
	cgXRotateAround(v.x, v.y, fRotation, center.x, center.y);
}

void cgXRotate( float &x, float &y, float fRotation )
{
	double sinValue = sin(fRotation);
	double cosValue = cos(fRotation);

	float newX = x*cosValue-y*sinValue;
	float newY = x*sinValue+y*cosValue;

	x = newX;
	y = newY;
}

void cgXRotate( cgVector& v, float rotation )
{
	cgXRotate(v.x, v.y, rotation);
}
