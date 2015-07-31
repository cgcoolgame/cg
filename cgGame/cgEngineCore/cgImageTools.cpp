#include "StdAfx.h"
#include "cgImageTools.h"

#include "cgRender.h"
#include "cgEngineTools.h"


void cgXRenderImageEx( cgImagePtr spImage, float centerX, float centerY, float w, float h, 
	cgColor color, float fRotation /*= 0.0f*/, bool bXFlip /*= false*/, bool bYFlip /*= false*/ )
{
	static const size_t rect_vertex_num = 4;
	static cgRenderVertex polygon[rect_vertex_num];

	polygon[0].x = -w/2;
	polygon[0].y = -h/2;
	polygon[0].color = color;
	spImage->PointToFinalTextureCoordinate(0, 0, polygon[0].u, polygon[0].v);

	polygon[1].x = w/2;
	polygon[1].y = -h/2;
	polygon[1].color = color;
	spImage->PointToFinalTextureCoordinate(spImage->GetWidth(), 0, polygon[1].u, polygon[1].v);

	polygon[2].x = w/2;
	polygon[2].y = h/2;
	polygon[2].color = color;
	spImage->PointToFinalTextureCoordinate(spImage->GetWidth(), spImage->GetHeight(), polygon[2].u, polygon[2].v);


	polygon[3].x = -w/2;
	polygon[3].y = h/2;
	polygon[3].color = color;
	spImage->PointToFinalTextureCoordinate(0, spImage->GetHeight(), polygon[3].u, polygon[3].v);


	// 旋转，如果小于1°，则不处理了
	for (size_t i = 0; i < rect_vertex_num; ++i)
	{
		if (fRotation > 0.006f || fRotation <-0.006f )
			cgXRotate(polygon[i].x, polygon[i].y, fRotation);

		polygon[i].x += centerX;
		polygon[i].y += centerY;
	}
	

	// X反转
	if (bXFlip)
	{
		float fTemp = 0.0f;

		fTemp = polygon[0].u;
		polygon[0].u = polygon[1].u;
		polygon[1].u = fTemp;

		fTemp = polygon[2].u;
		polygon[2].u = polygon[3].u;
		polygon[3].u = fTemp;
	}

	// Y反转
	if (bYFlip)
	{
		float fTemp = 0.0f;

		fTemp = polygon[0].v;
		polygon[0].v = polygon[3].v;
		polygon[3].v = fTemp;

		fTemp = polygon[1].v;
		polygon[1].v = polygon[2].v;
		polygon[2].v = fTemp;
	}

	cgRender::Get()->RenderPolygon(polygon, rect_vertex_num, spImage->GetTextureID());
}
