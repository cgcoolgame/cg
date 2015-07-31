#include "StdAfx.h"
#include "cgUIRichText.h"
#include "cgUIRichChar.h"
#include "cgUIChar.h"
#include "cgUIRichChar_Link.h"
#include "cgUIRichCharSpawner.h"

#ifdef _DEBUG
#define _DEBUG_LOG_CGUIRICHTEXT_
#endif

cgUIRichText::cgUIRichText(void)
{
}

cgUIRichText::cgUIRichText( const string & strName ):
cgUIWidget(strName)
{

}


cgUIRichText::~cgUIRichText(void)
{
}


void cgUIRichText::ParseRawString()
{
	m_spHotChar = NULL;
	m_kCharList.clear();

	LPCTSTR rawStr = m_strText.c_str();

	TCHAR szControlField[CG_UI_CHAR_MAX_RAW_STRING_LEN] = {0};
	int nFieldLen = 0;

	TCHAR ch = *rawStr++;
	bool bFieldBegin = false;
	while (ch)
	{
		switch(ch)
		{
		case TEXT('<'):
			{
				if (!bFieldBegin)
				{
					bFieldBegin = true;
					nFieldLen = 0;
					szControlField[nFieldLen++] = ch;
				}
			}break;
		case TEXT('>'):
			{
				if (bFieldBegin)
				{
					bFieldBegin = false;
					szControlField[nFieldLen++] = ch;
					szControlField[nFieldLen] = NULL;

					ParseControlField(szControlField);
					nFieldLen = 0;
				}
			}break;
		default:
			{
				szControlField[nFieldLen++] = ch;
				if (!bFieldBegin)
				{
					szControlField[nFieldLen] = NULL;
					InsertNormalChar(szControlField);
					nFieldLen = 0;
				}
			}
		}

		ch = *rawStr++;
	}
}


void cgUIRichText::ParseControlField( LPCTSTR str )
{
#ifdef _DEBUG_LOG_CGUIRICHTEXT_
	wcout<<"cgUIRichText::ParseControlField:"<<str<<endl;
#endif
	int nCharTypeLen = 0;
	TCHAR szCharType[CG_UI_CHAR_MAX_RAW_STRING_LEN] = {0};

	int nAttrNameLen = 0;
	TCHAR szAttrName[CG_UI_CHAR_MAX_RAW_STRING_LEN] = {0};

	int nAttrValueLen = 0;
	TCHAR szAttrValue[CG_UI_CHAR_MAX_RAW_STRING_LEN] = {0};

	int nState_AttrName = 0;
	int nState_AttrValue = 1;
	int nState = nState_AttrName;

	
	int nOffset = ParseFieldName(str, szCharType);
	cgUIRichChar * pkChar = cgUIRichCharSpawner::Spawn(szCharType);
	if (!pkChar)
		return ;
	pkChar->SetTypeString(szCharType);

	nOffset += EatSpace(str+nOffset);
#ifdef _DEBUG_LOG_CGUIRICHTEXT_
	wcout<<TEXT("\t")<<szCharType<<TEXT(":")<<endl;
#endif

	TCHAR ch = str[nOffset++];
	while (ch)
	{
		switch(ch)
		{
		case TEXT(' '):
			{
				if (nState == nState_AttrName)
				{
					szAttrName[nAttrNameLen] = NULL;
					nOffset += EatSpace(str+nOffset);
				}else if (nState_AttrValue == nState)
				{
					szAttrValue[nAttrValueLen] = NULL;

#ifdef _DEBUG_LOG_CGUIRICHTEXT_
					wcout<<TEXT("\t\t")<<szAttrName<<TEXT(":")<<szAttrValue<<endl;
#endif
					pkChar->SetAttr(szAttrName, szAttrValue);
					// ---------------------------------------
					nOffset += EatSpace(str+nOffset);
					nState = nState_AttrName;
					nAttrNameLen = 0;
				}
			}break;

		case TEXT('='):
			{
				if (nState == nState_AttrName)
				{
					szAttrName[nAttrNameLen] = NULL;
					nOffset += EatSpace(str+nOffset);
					nState = nState_AttrValue;
					nAttrValueLen = 0;
				}
			}break;
		case TEXT('>'):
			{
				if (nState_AttrValue == nState)
				{
					szAttrValue[nAttrValueLen] = NULL;
#ifdef _DEBUG_LOG_CGUIRICHTEXT_
					wcout<<TEXT("\t\t")<<szAttrName<<TEXT(":")<<szAttrValue<<endl;
#endif			
					pkChar->SetAttr(szAttrName, szAttrValue);
				}
			}break;
		default:
			{
				if (nState == nState_AttrName)
				{
					szAttrName[nAttrNameLen++] = ch;
					
				}else if (nState_AttrValue == nState)
				{
					szAttrValue[nAttrValueLen++] = ch;
				}
			}
		}

		ch = str[nOffset++];
	}

	InsertRichChar(pkChar);
}

void cgUIRichText::InsertNormalChar( LPCTSTR str)
{
#ifdef _DEBUG_LOG_CGUIRICHTEXT_
	wcout<<"cgUIRichText::InsertNormalChar:"<<str<<endl;
#endif
	cgUIChar * pkChar = new cgUIChar;
	pkChar->SetRawString(str);
	
	InsertRichChar(pkChar);
}

void cgUIRichText::InsertRichChar( cgUIRichChar * richChar )
{
	m_kCharList.push_back(richChar);
}

int cgUIRichText::ParseFieldName( LPCTSTR str, LPTSTR szName )
{
	int nEatLen = 1; // ³Ôµô<
	nEatLen += EatSpace(str+1);

	int nNameLen = 0;
	TCHAR ch = str[nEatLen++];
	while (ch && ch != TEXT(' ') && ch != TEXT('>'))
	{
		szName[nNameLen++] = ch;
		ch = str[nEatLen++];
	}
	szName[nEatLen] = NULL;

	return nEatLen;
}

int cgUIRichText::EatSpace( LPCTSTR str )
{
	int nSpaceCount = 0;
	while (*str++ == TEXT(' '))
		++nSpaceCount;

	return nSpaceCount;
}

void cgUIRichText::MeasureRichText( )
{
	int nContentHeight = 0;

	cgUIRichPen pen;
	pen.SetDefaultFont(m_idFont);

	m_kLineList.clear();
	cgRichLine * pkCurLine = new cgRichLine;
	m_kLineList.push_back(pkCurLine);

	for (int i = 0; i < m_kCharList.size(); ++i)
	{
		cgUIRichCharPtr spChar = m_kCharList[i];
		spChar->Measure(pen);// todo
		cgSizeF charSize = spChar->GetCharSize(pen.GetCurFont());

		if (spChar->NeedChangeLine() || pkCurLine->w + charSize.w > GetWidth())
		{
			pkCurLine->xOff = 0;
			if (m_nTextStyle & DT_RIGHT)
				pkCurLine->xOff = GetWidth() - pkCurLine->w;

			if (m_nTextStyle & DT_CENTER)
				pkCurLine->xOff = (GetWidth() - pkCurLine->w)/2;

			nContentHeight += pkCurLine->h + m_nTextRowSpace;
			
			pkCurLine = new cgRichLine;
			m_kLineList.push_back(pkCurLine);
		}
		
		pkCurLine->w += charSize.w;
		pkCurLine->h = max(pkCurLine->h, charSize.h);
		pkCurLine->kList.push_back(spChar);
	}
	pkCurLine->xOff = 0;
	if (m_nTextStyle & DT_RIGHT)
		pkCurLine->xOff = GetWidth() - pkCurLine->w ;

	if (m_nTextStyle & DT_CENTER)
		pkCurLine->xOff = (GetWidth() - pkCurLine->w)/2 ;

	nContentHeight += pkCurLine->h;

	int nYOff = 0;
	if (m_nTextStyle & DT_BOTTOM)
		nYOff = GetHeight() - nContentHeight;
	if (m_nTextStyle & DT_VCENTER)
		nYOff = (GetHeight() - nContentHeight)/2;

	for (int i = 0; i < m_kLineList.size(); ++i)
	{
		cgRichLinePtr spLine = m_kLineList[i];
		spLine->yOff = nYOff;
		nYOff += spLine->h+m_nTextRowSpace;
	}
}

void cgUIRichText::DrawText( const cgRectF& clipRect )
{
	cgUIRichPen pen;
	pen.SetDefaultFont(m_idFont);
	pen.SetDefaultColor(m_uTextColor);

	for (int lineIndex = 0; lineIndex < m_kLineList.size(); ++lineIndex)
	{
		cgRichLinePtr spLine = m_kLineList[lineIndex];

		int nDrawX = spLine->xOff + GetX();
		int nDrawY = spLine->yOff + GetY();

		for (int charIndex = 0; charIndex < spLine->kList.size(); ++charIndex)
		{
			cgUIRichCharPtr spChar = spLine->kList[charIndex];
			cgSizeF charSize = spChar->GetCharSize(pen.GetCurFont());
			spChar->Draw(pen, nDrawX, nDrawY + (spLine->h - charSize.h)/2);
			nDrawX += charSize.w;
		}
	}
}

cgUIRichCharPtr cgUIRichText::PickInteractiveChar( int x, int y )
{
	cgUIRichPen pen;
	pen.SetDefaultFont(m_idFont);

	cgUIRichCharPtr spLinkBegin;
	for (int lineIndex = 0; lineIndex < m_kLineList.size(); ++lineIndex)
	{
		cgRichLinePtr spLine = m_kLineList[lineIndex];

		int nCharX = spLine->xOff + GetX();
		int nLineY = spLine->yOff + GetY(); 
		for (int chIndex = 0; chIndex < spLine->kList.size(); ++chIndex)
		{
			cgUIRichCharPtr spChar = spLine->kList[chIndex];
			if (spChar->GetTypeString() == TEXT("link"))
			{
				spLinkBegin = spChar;
			}else if (spChar->GetTypeString() == TEXT("/link"))
			{
				spLinkBegin = NULL;
			}
			spChar->Measure(pen);
			cgSizeF charSize = spChar->GetCharSize(pen.GetCurFont());
			if ( x >= nCharX && x <= nCharX + charSize.w 
				&& y >= (spLine->h - charSize.h)/2+nLineY && y <= -(spLine->h - charSize.h)/2+spLine->h+nLineY)
			{
				return spLinkBegin;
			}
			nCharX += charSize.w;
		}
	}

	return NULL;
}

bool cgUIRichText::OnMessage( cgUIMsg msg, unsigned wparam, unsigned lparam )
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		{
			OnLButtonDown(wparam, lparam);
		}break;
	case WM_RBUTTONDOWN:
		{
			OnRButtonDown(wparam, lparam);
		}break;
	case WM_MOUSEMOVE:
		{
			OnMouseMove(wparam, lparam);
		}break;
	default:
		break;
	}

	return cgUIWidget::OnMessage(msg, wparam, lparam);
}

bool cgUIRichText::OnLButtonDown( unsigned wparam, unsigned lparam )
{
	int x = LOWORD(lparam);
	int y = HIWORD(lparam);

	cgUIRichCharPtr spHot = PickInteractiveChar(x, y);
	if (spHot)
	{
		spHot->OnLButtonDown();
	}
	return true;
}

bool cgUIRichText::OnRButtonDown( unsigned wparam, unsigned lparam )
{
	return false;
}

bool cgUIRichText::OnMouseMove( unsigned wparam, unsigned lparam )
{
	int x = LOWORD(lparam);
	int y = HIWORD(lparam);

	cgUIRichCharPtr spHot = PickInteractiveChar(x, y);
	if (spHot != m_spHotChar)
	{
		if (m_spHotChar)
			m_spHotChar->OnMouseOut();

		m_spHotChar = spHot;

		if (m_spHotChar)
			m_spHotChar->OnMouseIn();

		ReportDirty();
	}

	if (m_spHotChar)
	{
		m_spHotChar->OnMouseMove();
		m_strCursor = "IDC_HAND";
	}else
	{
		m_strCursor = "IDC_ARROW";
	}
	return true;
}



void cgUIRichText::OnTextChanged()
{
	ParseRawString();
	MeasureRichText();
}

void cgUIRichText::OnFontChanged()
{
	MeasureRichText();
}

void cgUIRichText::OnTextStyleChanged()
{
	MeasureRichText();
}

void cgUIRichText::OnTextColorChanged()
{
}

void cgUIRichText::OnTextRowSpaceChanged()
{
	MeasureRichText();
}

void cgUIRichText::OnSizeChanged()
{
	MeasureRichText();
}
