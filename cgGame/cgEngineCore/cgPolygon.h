#ifndef cgPolygon_h__
#define cgPolygon_h__

// �����
class cgPolygon
{
public:
	cgPolygon(size_t vertexNum);
	~cgPolygon(void);

	// ���ö�������
	void SetVertexAt(const cgRenderVertex& vertex, size_t index);
	cgRenderVertex * GetVertexAt(size_t index);

	// ��ȡ�ܵĶ������
	int GetVertexNum();

	// ���ã����ú󶥵�����Ҫ���������������Ԥ��
	void  Reset(size_t vertexNum);

	// ���ÿɼ��Ķ�����������ڻ��Ʋ��ֶ����
	void SetVisibleVertexNum(size_t visibleVertexNum);
	size_t GetVisibleVertexNum();


	// ����
	void Render( cgID idTex = CG_INVALID_ID);
protected:
	cgRenderVertex * m_pVertexArray;
	size_t m_uVertexNum;
	size_t m_uVisibleVertexNum;
};

cgPolygon * cgXCreateCircle(float r, cgColor color, size_t vertexNum);
#endif // cgPolygon_h__
