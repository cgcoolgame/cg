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

// 判断一个按键是否被按下
bool cgXIsKeyPressed(DWORD dwKey);

// ---------------------------------------------------------------------------------------------------------------
// 是否相交
template<typename T>
bool cgXIsRectIntersect(const cgRectT<T> & kFirstRect, const const cgRectT<T> & kSecondRect)
{
	if (kFirstRect.GetLeft() > kSecondRect.GetRight() || kFirstRect.GetRight() < kSecondRect.GetLeft() 
		|| kFirstRect.GetTop() > kSecondRect.GetBottom() || kFirstRect.GetBottom() < kSecondRect.GetTop())
	{
		// 不相交
		return false;
	}
	return true;
}
// 获取相交矩形
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

// 比较两个矩形的关系：相离，相等，包含，被包含，普通交叉（交叉：有重叠，但是不是相等、包含、被包含）
template<typename T>
cgRectCmpResult cgXCompareRect(const cgRectT<T> & kFirst, const cgRectT<T> & kSecond)
{
	if (!cgXIsRectIntersect(kFirst, kSecond))
	{
		return cgRectCmpResult_Away;// 相离
	}else if (kFirst.GetLeft() == kSecond.GetLeft() && kFirst.GetRight() == kSecond.GetRight() 
		&& kFirst.GetTop() == kSecond.GetTop() && kFirst.GetBottom() == kSecond.GetBottom())
	{
		return cgRectCmpResult_Equal;// 相等
	}else if (kFirst.GetLeft() <= kSecond.GetLeft() && kFirst.GetRight() >= kSecond.GetRight()
		&& kFirst.GetTop() <= kSecond.GetTop() && kFirst.GetBottom() >= kSecond.GetBottom())
	{
		return cgRectCmpResult_Contain;	// 包含
	}else if (kFirst.GetLeft() >= kSecond.GetLeft() && kFirst.GetRight() <= kSecond.GetRight()
		&& kFirst.GetTop() >= kSecond.GetTop() && kFirst.GetBottom() <= kSecond.GetBottom())
	{
		return cgRectCmpResult_BeContained;	// 被包含
	}

	return cgRectCmpResult_Cross;	// 交叉
}

// 坐标相交计算
template<typename T>
bool cgXIsPointInRect(cgRectT<T> &rect, int x, int y)
{
	return (x>=rect.x)&&(y>=rect.y)
		&&(x<rect.GetRight())&&(y<rect.GetBottom());
}

// ---------------------------------------------------------------------------------------------------------------
// 旋转
void cgXRotateAround(float & x, float & y, float fRotation, float fCenterX = 0.0f, float fCenterY = 0.0f);
void cgXRotateAround(cgVector & v, float fRotation, const cgVector& center);

// 旋转:围绕（0,0）旋转
void cgXRotate(float &x, float &y, float fRotation);
void cgXRotate(cgVector& v, float rotation);

#endif // cgEngineTools_h__
