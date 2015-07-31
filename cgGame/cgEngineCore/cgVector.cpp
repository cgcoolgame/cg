#include "StdAfx.h"
#include "cgVector.h"


void cgVector::Normalize()
{
	assert(x!=0.0f || y!=0.0f);

	float fLen = sqrt(x*x+y*y);
	x /= fLen;
	y /= fLen;
}


float cgVector::Length()const
{
	return sqrt(x*x+y*y);
}


cgVector& cgVector::operator*=( float fValue )
{
	x *= fValue;
	y *= fValue;
	
	return *this;
}

cgVector& cgVector::operator+=( const cgVector& v )
{
	x += v.x;
	y += v.y;

	return *this;
}

cgVector& cgVector::operator-=( const cgVector& v )
{
	x -= v.x;
	y -= v.y;

	return *this;
}

cgVector& cgVector::operator/=( float fValue )
{
	x /= fValue;
	y /= fValue;

	return *this;
}

float cgVector::Dot( const cgVector& leftV, const cgVector& rightV )
{
	return leftV.x*rightV.x + leftV.y*rightV.y;
}

// --------------------------------------------------------------------------
cgVector operator*( const cgVector& v, float fValue )
{
	return cgVector(v.x*fValue, v.y*fValue);
}

cgVector operator*( float fValue, const cgVector& v )
{
	return v*fValue;
}

cgVector operator/( const cgVector& v, float fValue )
{
	return cgVector(v.x/fValue, v.y/fValue);
}

cgVector operator+( const cgVector& leftV, const cgVector& rightV )
{
	return cgVector(leftV.x+rightV.x, leftV.y+rightV.y);
}

cgVector operator-( const cgVector& leftV, const cgVector& rightV )
{
	return cgVector(leftV.x-rightV.x, leftV.y-rightV.y);
}

cgVector operator*( const cgVector& leftV, const cgVector& rightV )
{
	return cgVector(leftV.x*rightV.x, leftV.y*rightV.y);
}

cgVector operator/( const cgVector& leftV, const cgVector& rightV )
{
	return cgVector(leftV.x/rightV.x, leftV.y/rightV.y);
}
