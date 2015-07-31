#include "StdAfx.h"
#include "cgImage.h"
#include "cgRenderImage.h"
#include "cgRefImage.h"
#include "cgEngineTools.h"
#include "cgRender.h"

cgImage::cgImage()
{
}

cgImage::~cgImage(void)
{
}


void cgImage::DrawToPoint( float x, float y, cgColor color )
{
	this->Draw(cgRectF(0, 0, GetWidth(), GetHeight()), 
		cgRectF(x, y, GetWidth(), GetHeight()), color);
}

void cgImage::DrawToRect( const cgRectF & kDestRect, 
	cgColor color /*= 0xffffffff*/ )
{
	this->Draw(cgRectF(0, 0, GetWidth(), GetHeight()), 
		kDestRect, color);
}

void cgImage::DrawToRect( float x, float y, float w, float h, cgColor color /*= 0xffffffff*/ )
{
	DrawToRect(cgRectF(x, y, w, h), color);
}

void cgImage::DrawPartToPoint( const cgRectF & kSrcRect, float x, float y,
	cgColor color /*= 0xffffffff*/ )
{
	this->Draw(kSrcRect, cgRectF(x, y, GetWidth(), GetHeight()), color);
}

// -------------------------------------------------------------------------------------------

cgImagePtr cgImage::LoadFromFile( LPCTSTR lpctPath )
{
	return new cgRenderImage(lpctPath);
}

cgImagePtr cgImage::CreateImage( int w, int h )
{
	return new cgRenderImage(w, h);
}

cgImagePtr cgImage::ClipFromImage( cgImagePtr spImage, const cgRectF& rect )
{
	return new cgRefImage(spImage, rect);
}

void cgImage::DrawEx( float centerX, float centerY,
	float w, float h, 
	cgColor color, float rotation, 
	bool xFlip /*= false*/, bool yFlip /*= false*/ )
{
	static const size_t rect_vertex_num = 4;
	static cgRenderVertex polygon[rect_vertex_num];

	polygon[0].x = -w/2;
	polygon[0].y = -h/2;
	PointToFinalTextureCoordinate(0, 0, polygon[0].u, polygon[0].v);

	polygon[1].x = -polygon[0].x;
	polygon[1].y = polygon[0].y;
	PointToFinalTextureCoordinate(GetWidth(), 0, polygon[1].u, polygon[1].v);

	polygon[2].x = polygon[1].x;
	polygon[2].y = -polygon[1].y;
	PointToFinalTextureCoordinate(GetWidth(), GetHeight(), polygon[2].u, polygon[2].v);

	polygon[3].x = polygon[0].x;
	polygon[3].y = polygon[2].y;
	PointToFinalTextureCoordinate(0, GetHeight(), polygon[3].u, polygon[3].v);

	// 旋转，如果小于1°，则不处理了
	for (size_t i = 0; i < rect_vertex_num; ++i)
	{
		if (rotation > 0.006f || rotation <-0.006f )
			cgXRotate(polygon[i].x, polygon[i].y, rotation);

		polygon[i].color = color;
		polygon[i].x += centerX;
		polygon[i].y += centerY;
	}

	// X反转
	if (xFlip)
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
	if (yFlip)
	{
		float fTemp = 0.0f;

		fTemp = polygon[0].v;
		polygon[0].v = polygon[3].v;
		polygon[3].v = fTemp;

		fTemp = polygon[1].v;
		polygon[1].v = polygon[2].v;
		polygon[2].v = fTemp;
	}

	cgRender::Get()->RenderPolygon(polygon, rect_vertex_num, GetTextureID());
}

// -------------------------------------------------------------------------------------------
