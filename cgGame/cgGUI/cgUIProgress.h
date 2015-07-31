
#ifndef cgUIProgress_h__
#define cgUIProgress_h__

#include "cgUIWidget.h"

class cgUIProgress :
	public cgUIWidget
{
public:
	cgUIProgress(void);
	~cgUIProgress(void);

	// ���ý�������ͼƬ
	void SetCoverImage(LPCTSTR cover);
	void SetCoverImage(cgID cover);

	// ���ý������ױߵ�ͼƬ
	void SetLayerImage(LPCTSTR layer);
	void SetLayerImage(cgID layer);

	// ������׼����ͼƬ
	void SetAimerImage(LPCTSTR aim);
	void SetAimerImage(cgID aim);

	// ���õ�ǰ��Χ
	void SetRange(int nRange);
	int GetRange()const;

	// ���õ�ǰλ��
	// bForceImmediate:ǿ������λ�ã�progress��aimmer˲��ͬ����
	// ���磺��ʼ����ʱ��Ͳ�ϣ����������������
	void SetProgress(int nProgress, bool bForceImmediate = false);
	int GetProgress()const;

	// ������׼���ٶ�
	void SetAimerSpeed(float fSpeed);
	float GetAimerSpeed()const;

	// ������׼����ʱ
	void SetAimerDelayTime(float fDelay);
	float GetAimerDelayTime()const;

	// ��ȡ��ǰ����׼��λ��
	int GetAimerPos()const;

	// �Ƿ����̸���
	bool IsImmediate()const;
	void SetImmediate(bool bImmediate);

	// �Ƿ��Ǵ�ֱ
	bool IsVertical()const;
	void SetVertical(bool bVertical);

	// �ױ���ɫ
	void SetLayerColor(cgColor color);
	cgColor GetLayerColor();

	// ��������ɫ
	void SetCoverColor(cgColor color);
	cgColor GetCoverColor();

protected:
	virtual void UpdateSelf(float fTime);

	// ������׼����λ��
	void UpdateAimerPos(float fTime);

	//���Ʊ���ͼƬ
	virtual void DrawBackPic(const cgRectF& clipRect);

	// ����ͼƬ����
	void DrawLayerImage(const cgRectF& clipRect);
	void DrawCoverImage(const cgRectF& clipRect);
	void DrawAimerImage(const cgRectF& clipRect);
protected:
	cgUIImagePtr m_spCoverImage;			// �����Ľ���ͼƬ
	cgUIImagePtr m_spLayerImage;		// �ײ��ͼƬ�����ڶ�̬��ʾ
	cgUIImagePtr m_spAimerImage;			// ��׼��ͼƬ

	cgColor m_uCoverColor;
	cgColor m_uLayerColor;

	int	m_nRange;		// ��Χ��0-range��
	int m_nProgress;			// ��ǰλ��

	float m_fAimerPos;		// ��׼��λ��
	float m_fAimerSpeed;		// ��׼�����ƶ��ٶȣ��ڿ����˽����Ժ�����

	float m_fAimerDelayTime;		// �仯��delayʱ��

	float m_fLeftAimerDelayTime;		// ʣ�����ʱ
	float m_fProgressChangeTime;	// ���������ȱ仯ʱ��
};

#endif // cgUIProgress_h__
