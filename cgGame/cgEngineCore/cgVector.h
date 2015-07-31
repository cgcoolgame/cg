
#ifndef cgVector_h__
#define cgVector_h__

class cgVector
{
public:
	cgVector():x(0.0f), y(0.0f){}
	cgVector(float fX, float fY):x(fX), y(fY){}

	// 赋值
	cgVector& Set(float xPos, float yPos){x = xPos; y = yPos; return *this;}

	// 标准化
	void Normalize();

	// 取长度
	float Length()const;

	// 相加
	cgVector& operator += (const cgVector& v);

	// 相减
	cgVector& operator -= (const cgVector& v);

	// 加长
	cgVector& operator *= (float fValue);

	// 相除
	cgVector& operator /= (float fValue);

	// 值
	float x;
	float y;

public:
	static float Dot(const cgVector& leftV, const cgVector& rightV);
	static float Cross(const cgVector& leftV, const cgVector& rightV);
};

// --------------------------------------------------------------------------
cgVector operator* (const cgVector& v, float fValue);
cgVector operator*(float fValue, const cgVector& v);
cgVector operator/(const cgVector& v, float fValue);
cgVector operator+(const cgVector& leftV, const cgVector& rightV);
cgVector operator-(const cgVector& leftV, const cgVector& rightV);

// 这个当做是缩放乘法吧，点成用cgVector.Dot，叉乘用cgVector.Cross
cgVector operator*(const cgVector& leftV, const cgVector& rightV);
cgVector operator/(const cgVector& leftV, const cgVector& rightV);

#endif // cgVector_h__
