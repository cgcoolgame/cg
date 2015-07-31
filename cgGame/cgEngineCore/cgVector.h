
#ifndef cgVector_h__
#define cgVector_h__

class cgVector
{
public:
	cgVector():x(0.0f), y(0.0f){}
	cgVector(float fX, float fY):x(fX), y(fY){}

	// ��ֵ
	cgVector& Set(float xPos, float yPos){x = xPos; y = yPos; return *this;}

	// ��׼��
	void Normalize();

	// ȡ����
	float Length()const;

	// ���
	cgVector& operator += (const cgVector& v);

	// ���
	cgVector& operator -= (const cgVector& v);

	// �ӳ�
	cgVector& operator *= (float fValue);

	// ���
	cgVector& operator /= (float fValue);

	// ֵ
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

// ������������ų˷��ɣ������cgVector.Dot�������cgVector.Cross
cgVector operator*(const cgVector& leftV, const cgVector& rightV);
cgVector operator/(const cgVector& leftV, const cgVector& rightV);

#endif // cgVector_h__
