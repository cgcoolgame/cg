#ifndef cgEngineTools_h__
#define cgEngineTools_h__

enum cgRectCmpResult
{
	cgRectCmpResult_Away,
	cgRectCmpResult_Equal,
	cgRectCmpResult_Contain,
	cgRectCmpResult_BeContained,
	cgRectCmpResult_Cross,
};

// �ж�һ�������Ƿ񱻰���
bool cgXIsKeyPressed(DWORD dwKey);

// ---------------------------------------------------------------------------------------------------------------
// �Ƿ��ཻ
template<typename T>
bool cgXIsRectIntersect(const cgRectT<T> & kFirstRect, const const cgRectT<T> & kSecondRect)
{
	if (kFirstRect.GetLeft() > kSecondRect.GetRight() || kFirstRect.GetRight() < kSecondRect.GetLeft() 
		|| kFirstRect.GetTop() > kSecondRect.GetBottom() || kFirstRect.GetBottom() < kSecondRect.GetTop())
	{
		// ���ཻ
		return false;
	}
	return true;
}
// ��ȡ�ཻ����
template<typename T>
bool cgXGetIntersectRect(const cgRectT<T> & kFirstRect, const cgRectT<T> & kSecondRect, cgRectT<T> & kIntersectRect)
{
	if (!cgXIsRectIntersect(kFirstRect, kSecondRect))
		return false;

	kIntersectRect.x = max(kFirstRect.GetLeft(), kSecondRect.GetLeft());
	kIntersectRect.y = max(kFirstRect.GetTop(), kSecondRect.GetTop());
	kIntersectRect.w = min(kFirstRect.GetRight(), kSecondRect.GetRight())-kIntersectRect.x;
	kIntersectRect.h = min(kFirstRect.GetBottom(), kSecondRect.GetBottom())-kIntersectRect.y;

	return true;
}

// �Ƚ��������εĹ�ϵ�����룬��ȣ�����������������ͨ���棨���棺���ص������ǲ�����ȡ���������������
template<typename T>
cgRectCmpResult cgXCompareRect(const cgRectT<T> & kFirst, const cgRectT<T> & kSecond)
{
	if (!cgXIsRectIntersect(kFirst, kSecond))
	{
		return cgRectCmpResult_Away;// ����
	}else if (kFirst.GetLeft() == kSecond.GetLeft() && kFirst.GetRight() == kSecond.GetRight() 
		&& kFirst.GetTop() == kSecond.GetTop() && kFirst.GetBottom() == kSecond.GetBottom())
	{
		return cgRectCmpResult_Equal;// ���
	}else if (kFirst.GetLeft() <= kSecond.GetLeft() && kFirst.GetRight() >= kSecond.GetRight()
		&& kFirst.GetTop() <= kSecond.GetTop() && kFirst.GetBottom() >= kSecond.GetBottom())
	{
		return cgRectCmpResult_Contain;	// ����
	}else if (kFirst.GetLeft() >= kSecond.GetLeft() && kFirst.GetRight() <= kSecond.GetRight()
		&& kFirst.GetTop() >= kSecond.GetTop() && kFirst.GetBottom() <= kSecond.GetBottom())
	{
		return cgRectCmpResult_BeContained;	// ������
	}

	return cgRectCmpResult_Cross;	// ����
}

// �����ཻ����
template<typename T>
bool cgXIsPointInRect(cgRectT<T> &rect, int x, int y)
{
	return (x>=rect.x)&&(y>=rect.y)
		&&(x<rect.GetRight())&&(y<rect.GetBottom());
}

// ---------------------------------------------------------------------------------------------------------------
// ��ת
void cgXRotateAround(float & x, float & y, float fRotation, float fCenterX = 0.0f, float fCenterY = 0.0f);
void cgXRotateAround(cgVector & v, float fRotation, const cgVector& center);

// ��ת:Χ�ƣ�0,0����ת
void cgXRotate(float &x, float &y, float fRotation);
void cgXRotate(cgVector& v, float rotation);

#endif // cgEngineTools_h__
