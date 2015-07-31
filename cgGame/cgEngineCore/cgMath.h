#ifndef cgMath_h__
#define cgMath_h__

namespace cgMath
{
	static const float PI = 3.1415927f; 
	static const float MINI_ROTATION = 0.001f;
	static const float MINI_SCALE = 0.01F;
	static const float MINI_ALPHA = 0.0F;
	static const float MAX_ALPHA = 1.0F;

	// ��С�����ֵ��a+FLOAT_EPSILON != a;
	static const float FLOAT_EPSILON = FLT_EPSILON;

	// ��С���ĸ�����
	static const float FLOAT_MIN	= FLT_MIN;
	static const float FLOAT_MAX	= FLT_MAX;

	float Random(float r);
	float Random(float min, float max);
	cgVector RandomOnCircle(float r);
	cgVector RandomInCircle(float r);

	// ��ֵ
	float Lerp(float l, float r, float delta);
	float Clamp(float x, float min, float max);

	bool IsPointInRect(const cgVector& point, const cgRectF & rect);
};

#endif // cgMath_h__
