#include "StdAfx.h"
#include "cgMath.h"
namespace cgMath
{
	float Random( float r )
	{
		return rand()*1.0f/RAND_MAX*r;
	}

	float Random( float min, float max )
	{
		return Random(max-min)+min;
	}

	cgVector RandomOnCircle( float r )
	{
		float arc = Random(360.0f)/180.0f*cgMath::PI;
		return cgVector(sin(arc)*r, cos(arc)*r);
	}

	cgVector RandomInCircle( float r )
	{
		return RandomOnCircle(Random(r));
	}

	bool IsPointInRect( const cgVector& point, const cgRectF & rect )
	{
		return point.x >= rect.GetLeft() && point.y >= rect.GetTop() 
			&& point.x <= rect.GetRight() && point.y <= rect.GetBottom();
	}

	float Lerp( float l, float r, float delta )
	{
		return l+(r-l)*delta;
	}

	float Clamp( float x, float min, float max )
	{
		if (x < min)
			x = min;
		if (x > max)
			x = max;

		return x;
	}

}
