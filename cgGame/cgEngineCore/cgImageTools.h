#ifndef cgImageTools_h__
#define cgImageTools_h__
#include "cgImage.h"

// 工具函数：绘制旋转图片
void cgXRenderImageEx(cgImagePtr spImage, float centerX, float centerY, float w, float h, cgColor color,
	float fRotation = 0.0f, bool bXFlip = false, bool bYFlip = false);

#endif // cgImageTools_h__
