#ifndef cgPolygon_h__
#define cgPolygon_h__

// 多边形
class cgPolygon
{
public:
	cgPolygon(size_t vertexNum);
	~cgPolygon(void);

	// 设置顶点数组
	void SetVertexAt(const cgRenderVertex& vertex, size_t index);
	cgRenderVertex * GetVertexAt(size_t index);

	// 获取总的顶点个数
	int GetVertexNum();

	// 重置，重置后顶点数据要重新填，否则结果不可预期
	void  Reset(size_t vertexNum);

	// 设置可见的顶点个数，用于绘制部分多边形
	void SetVisibleVertexNum(size_t visibleVertexNum);
	size_t GetVisibleVertexNum();


	// 绘制
	void Render( cgID idTex = CG_INVALID_ID);
protected:
	cgRenderVertex * m_pVertexArray;
	size_t m_uVertexNum;
	size_t m_uVisibleVertexNum;
};

cgPolygon * cgXCreateCircle(float r, cgColor color, size_t vertexNum);
#endif // cgPolygon_h__
