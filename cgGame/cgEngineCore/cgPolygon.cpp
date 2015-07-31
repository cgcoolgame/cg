#include "StdAfx.h"
#include "cgPolygon.h"
#include "cgRender.h"
#include "cgMath.h"

cgPolygon::cgPolygon( size_t vertexNum )
{
	m_uVertexNum = vertexNum;
	m_pVertexArray = new cgRenderVertex[m_uVertexNum];
	m_uVisibleVertexNum = m_uVertexNum;
}

cgPolygon::~cgPolygon(void)
{
	if (m_pVertexArray)
		delete[] m_pVertexArray;
}

void cgPolygon::SetVertexAt( const cgRenderVertex& vertex, size_t index )
{
	if (index < m_uVertexNum)
		m_pVertexArray[index] = vertex;
}
cgRenderVertex * cgPolygon::GetVertexAt( size_t index )
{
	if (index < m_uVertexNum)
		return m_pVertexArray+index;

	return NULL;
}

int cgPolygon::GetVertexNum()
{
	return m_uVertexNum;
}


void cgPolygon::Render( cgID idTex )
{
	cgRender::Get()->RenderPolygon(m_pVertexArray, m_uVisibleVertexNum, idTex);
}

void cgPolygon::Reset( size_t vertexNum )
{
	// 只有增加的时候才重新分配
	if (vertexNum > m_uVertexNum)
	{
		if (m_pVertexArray)
			delete[] m_pVertexArray;

		m_pVertexArray = new cgRenderVertex[vertexNum];
	}

	m_uVertexNum = vertexNum;
	m_uVisibleVertexNum = vertexNum;
}

void cgPolygon::SetVisibleVertexNum( size_t visibleVertexNum )
{
	m_uVisibleVertexNum = visibleVertexNum;
}

size_t cgPolygon::GetVisibleVertexNum()
{
	return m_uVisibleVertexNum;
}

// ------------------------------------------------------------------------------------------
cgPolygon * cgXCreateCircle( float r, cgColor color, size_t vertexNum )
{
	cgPolygon * pkPolygon = new cgPolygon(vertexNum);

	cgRenderVertex vertex;
	double arc = cgMath::PI*2/vertexNum;
	double curArc = -arc/2-cgMath::PI/2;
//	double curArc = 0;
	for (int i = 0; i < vertexNum; ++i)
	{
		double sinValue = sin(curArc);
		double cosValue = cos(curArc);

		vertex.color = color;
		vertex.x = r*cosValue;
		vertex.y = r*sinValue;
		vertex.u = cosValue*0.5+0.5;
		vertex.v = sinValue*0.5+0.5;

		pkPolygon->SetVertexAt(vertex, i);

		curArc += arc;
	}

	return pkPolygon;
}
