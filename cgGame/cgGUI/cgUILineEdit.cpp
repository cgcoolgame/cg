#include "StdAfx.h"
#include "cgUILineEdit.h"
#include "cgUIRender.h"

cgUILineEdit::cgUILineEdit()
{
	m_strCursor = "IDC_IBEAM";
	m_enmType = enmUIEditType_Normal;
	m_fLastUpdateTime = 0.0f;
	m_uSelBackColor = 0xff3399ff;
	m_nCursorPos = 0;
	m_nSelBegin = 0;
	m_nFirstVisibleCharIndex = 0;
	m_nMaxCharNum = CG_LONG_TEXT_BUFF_LEN;
	m_bCursorVisible = true;
}

cgUILineEdit::cgUILineEdit( const string& strName )
{
	m_strName = strName;
	m_strCursor = "IDC_IBEAM";
	m_enmType = enmUIEditType_Normal;
	m_fLastUpdateTime = 0.0f;
	m_uSelBackColor = 0xff3399ff;
	m_nCursorPos = 0;
	m_nSelBegin = 0;
	m_nFirstVisibleCharIndex = 0;
	m_nMaxCharNum = CG_LONG_TEXT_BUFF_LEN;
	m_bCursorVisible = true;
}

cgUILineEdit::~cgUILineEdit(void)
{
}

void cgUILineEdit::SetSelColor( cgColor color )
{
	m_uSelBackColor = color;
}

cgColor cgUILineEdit::GetSelColor()
{
	return m_uSelBackColor;
}



// -----------------------------------------------------------------------------

void cgUILineEdit::UpdateSelf( float fTime )
{
	if (IsFocus() && fTime - m_fLastUpdateTime > 0.5f)
	{
		m_fLastUpdateTime = fTime;
		m_bCursorVisible = !m_bCursorVisible;

		ReportDirty();
	}
}


bool cgUILineEdit::IsCursorDrawable()
{
	return m_bCursorVisible&&IsFocus();
}

// -----------------------------------------------------------------------------------
bool cgUILineEdit::OnMessage( UINT uMsg, unsigned wparam, unsigned lparam )
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			OnLButtonDown(wparam, lparam);
		}break;
	case WM_MOUSEMOVE:
		{
			OnMouseMove(wparam, lparam);
		}break;
	case WM_CHAR:
		{
			return OnChar(wparam, lparam);
		}break;
	case WM_KEYDOWN:
		{
			if ( OnKeyDown(wparam, lparam))
				return true;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			SetSelBegin(0);
			SetCursorPos(m_strText.length());
		}break;
	case cgUIMsg_Copy:
		{
			return OnCopy();
		}break;
	case cgUIMsg_Cut:
		{
			return OnCut();
		}break;
	case cgUIMsg_Paste:
		{
			return OnPaste();
		}break;
	case cgUIMsg_MouseOut:
		{
			OnMouseMove(wparam, lparam);
		}break;
	case cgUIMsg_MouseIn:
		{

		}
	default:
		break;
	}

	return cgUIWidget::OnMessage(uMsg, wparam, lparam);
}


bool cgUILineEdit::OnKeyDown( unsigned wparam, unsigned lparam )
{
	switch(wparam)
	{
	case VK_BACK:
		{
			return EraseChar(m_nCursorPos);
		}break;
	case VK_DELETE:
		{
			return EraseChar(m_nCursorPos+1);
		}break;
	case VK_LEFT:
		{
			int nDestPos = m_nCursorPos-1;
			if (GetKeyState(VK_CONTROL) < 0)
			{
				nDestPos = 0;
			}
			KeyMoveCursor(nDestPos);
		}break;
	case VK_RIGHT:
		{
			int nDestPos = m_nCursorPos+1;
			if (GetKeyState(VK_CONTROL) < 0)
			{
				nDestPos = m_strText.length();
			}
			KeyMoveCursor(nDestPos);
		}break;
	case VK_HOME:
		{
			KeyMoveCursor(0);
		}break;
	case VK_END:
		{
			KeyMoveCursor(m_strText.length());
		}break;
	default:
		break;
	}

	return false;
}


bool cgUILineEdit::OnChar( unsigned wparam, unsigned lparam )
{
	if(!IsPrintableWord(wparam)) return false;

	ClearSel();// 清空选中项

	if (!InsertChar(wparam))
		return false;
	
	ReportUIEvent(cgUIEvent_OnTextChange);

	return true;
}

bool cgUILineEdit::OnLButtonDown( unsigned wparam, unsigned lparam )
{
	int x = LOWORD(lparam);

	int nCursorPos = XPointToCharIndex(x);

	SetSelBegin(nCursorPos);
	SetCursorPos(nCursorPos);

	return true;
}


bool cgUILineEdit::OnMouseMove( unsigned wparam, unsigned lparam )
{

	if (IsClickDown())
	{
		int x = LOWORD(lparam);

		int nCursorPos = XPointToCharIndex(x);

		if (nCursorPos == m_nFirstVisibleCharIndex)
		{
			// 如果到了左边缘，则一次到头
			nCursorPos = 0;
		}

		SetCursorPos(nCursorPos);
	}

	return true;
}

void cgUILineEdit::OnMouseOut( unsigned wparam, unsigned lparam )
{
	OnMouseMove(wparam, lparam);
}

// ---------------------------------------------------------------------------------------

bool cgUILineEdit::Insert( LPCTSTR lpctStr )
{
	if (!lpctStr )
	{
		return false;
	}

	TCHAR ch = 0;
	while (ch=*lpctStr++)
	{
		if (IsPrintableWord(ch))
			InsertChar(ch);
	}

	ReportUIEvent(cgUIEvent_OnTextChange);
	ReportDirty();

	return true;

}


bool cgUILineEdit::OnPaste()
{
	// 如果是密码控件，则不可粘贴
	if (m_enmType == enmUIEditType_Password)
		return true;

	ClearSel();

	if( !::OpenClipboard(NULL) ) return true;
#ifdef UNICODE
	HANDLE handle = ::GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE handle = ::GetClipboardData(CF_TEXT);
#endif

	if (handle)
	{
		LPCTSTR lpctMem = (LPCTSTR)::GlobalLock(handle);

		Insert(lpctMem);

		::GlobalUnlock(handle);
	}

	::CloseClipboard();

	return true;
}

bool cgUILineEdit::OnCopy()
{
	// 如果是密码控件，则不可复制
	if (m_enmType == enmUIEditType_Password)
		return true;

	if(m_nSelBegin!=m_nCursorPos)
	{
		//得到选择文本

		int nBegin = min(m_nSelBegin, m_nCursorPos);
		int nEnd = max(m_nSelBegin, m_nCursorPos);

		//得到共享内存
		HGLOBAL hGlobal=GlobalAlloc(GHND|GMEM_SHARE,(nEnd-nBegin+1)*sizeof(TCHAR));
		if(!hGlobal) return true;

		//填充共享内存
		LPVOID pGlobal=GlobalLock(hGlobal);
		//strcpy((char*)pGlobal,selText.c_str());
		//_tcsncpy((LPTSTR)pGlobal, m_strText+nBegin, nEnd-nBegin);
		m_strText.copy((LPTSTR)pGlobal, nEnd-nBegin, nBegin);
		GlobalUnlock(hGlobal);

		//设置剪贴板
		if( !::OpenClipboard(NULL) ) return true;
		::EmptyClipboard();
#ifdef UNICODE
		SetClipboardData(CF_UNICODETEXT,hGlobal);
#else
		SetClipboardData(CF_TEXT, hGlobal);
#endif
		//	::SetClipboardData(CF_TEXT,hGlobal);
		::CloseClipboard();

	}

	return true;
}

bool cgUILineEdit::OnCut()
{
	// 如果是密码控件，则不可剪切，消息吃掉
	if (m_enmType == enmUIEditType_Password)
		return true;

	OnCopy();
	ClearSel();

	ReportUIEvent(cgUIEvent_OnTextChange);
	ReportDirty();

	return true;
}


int cgUILineEdit::XPointToCharIndex( int x , int nType )
{
	int nTextLen = m_strText.length();
	int nXOff = m_kRect.x;

	int nIndex = 0;
	for (nIndex = m_nFirstVisibleCharIndex; nIndex < nTextLen; ++nIndex)
	{
		int nW = GetUICharWidth(m_strText[nIndex]);
		int nOff = 0; // 向后取整
		if (nType == 0) // 最近
			nOff = nW>>1;
		else if (nType == 1)
			nOff = nW;
		if (nXOff + nOff > x )
			break;

		nXOff += nW;
	}

	return nIndex;
}


int cgUILineEdit::CharIndexToXPoint( int pos )
{
	int nStrLen = m_strText.length();
	int nXOff = m_kRect.x;

	if (pos > m_nFirstVisibleCharIndex)
	{
		for (int i = m_nFirstVisibleCharIndex; i < nStrLen  && i < pos; ++i)
		{
			nXOff += GetUICharWidth(m_strText[i]);
		}
	}else
	{
		for (int i = m_nFirstVisibleCharIndex;  i > pos; --i)
		{
			nXOff -= GetUICharWidth(m_strText[i]);
		}
	}	

	return nXOff;
}

// ---------------------------------------------------------------------------------------

bool cgUILineEdit::IsPrintableWord( TCHAR ch )
{
	if (m_enmType == enmUIEditType_Normal)
		return iswprint(ch);

	return (!((ch>=0)&&(ch<TEXT(' '))||(ch==127 ))) && ch <= 0x007f;
}

bool cgUILineEdit::InsertChar( TCHAR ch )
{
	// 如果字数已满，则不插入
	if ( m_strText.length() >= m_nMaxCharNum)
		return false;

	// 如果光标位置非法，则移动到末尾
	if (m_nCursorPos < 0 || m_nCursorPos > m_strText.length())
		m_nCursorPos = m_strText.length();

	m_strText.insert(m_nCursorPos, 1, ch);

	SetSelBegin(m_nCursorPos+1);
	SetCursorPos(m_nCursorPos+1);

	return true;
}

void cgUILineEdit::SetText( LPCTSTR lpctText )
{	
	cgUIWidget::SetText(lpctText);
	SetSelBegin( m_strText.length() );
	SetCursorPos( m_strText.length() );
}

void cgUILineEdit::SetMaxCharNum( int nMax )
{
	m_nMaxCharNum = nMax<CG_LONG_TEXT_BUFF_LEN?nMax:CG_LONG_TEXT_BUFF_LEN;
}

int cgUILineEdit::GetMaxCharNum()
{
	return m_nMaxCharNum;
}

int cgUILineEdit::GetUICharWidth(TCHAR ch)
{
	return cgUIRender::GetRender()->GetUICharWidth(ch, m_idFont);
}


cgSizeF cgUILineEdit::GetUICharSize( TCHAR ch )
{
	return cgUIRender::GetRender()->GetUICharSize(ch, m_idFont);
}


bool cgUILineEdit::SetCursorPos( int nPos )
{
	nPos = max(nPos, 0);
	if (nPos != m_nCursorPos)
	{
		m_nCursorPos = min(nPos, m_strText.length());
		m_bCursorVisible = true;
		EnsureCursorVisible();
		ReportDirty();
	}

	return true;
}


bool cgUILineEdit::SetSelBegin( int nPos )
{
	nPos = max(nPos, 0);// 小于0，则选中0

	if (nPos != m_nSelBegin)
	{
		m_nSelBegin = min(nPos, m_strText.length());
		ReportDirty();
	}

	return true;
}


bool cgUILineEdit::KeyMoveCursor( int nDestPos )
{
	SetCursorPos(nDestPos);

	if (GetKeyState(VK_SHIFT) >= 0)
	{
		SetSelBegin(nDestPos);
	}

	return true;
}


bool cgUILineEdit::EnsureCursorVisible()
{
	int nCursorXPoint = CharIndexToXPoint(m_nCursorPos);
	
	if (nCursorXPoint > m_kRect.GetRight())
	{
		m_nFirstVisibleCharIndex = XPointToCharIndex(nCursorXPoint-m_kRect.w, 2);
	}else if (nCursorXPoint < m_kRect.x)
	{
		m_nFirstVisibleCharIndex = m_nCursorPos;
	}

	return true;
}


bool cgUILineEdit::EraseChar(int nCursorPos)
{
	if (nCursorPos < 0 || nCursorPos > m_strText.length())
		return false;

	if (m_nSelBegin != m_nCursorPos)
	{
		ClearSel();

	}else if(nCursorPos > 0)
	{
		m_strText.erase(nCursorPos-1, 1);

		if (nCursorPos == m_nCursorPos)
		{
			SetSelBegin(m_nCursorPos-1);
			SetCursorPos(m_nCursorPos-1);

			if (m_nFirstVisibleCharIndex > 0)
				--m_nFirstVisibleCharIndex;
		}
	}

	EnsureCursorVisible();

	ReportUIEvent(cgUIEvent_OnTextChange);
	ReportDirty();

	return true;
}


bool cgUILineEdit::ClearSel()
{
	if (m_nSelBegin != m_nCursorPos)
	{
		int nMin = min(m_nSelBegin, m_nCursorPos);
		int nMax = max(m_nSelBegin, m_nCursorPos);

		m_strText.erase(nMin, nMax-nMin);

		m_nCursorPos = m_nSelBegin = nMin;
		m_nFirstVisibleCharIndex = min(m_nFirstVisibleCharIndex, m_strText.length());
	}

	return true;
}

// -----------------------------------------------------------------------------------------
void cgUILineEdit::SetEditType( enmUIEditType enmType )
{
	m_enmType = enmType;

	ReportDirty();
}

// ----------------------------------------------------------------------------------------------

void cgUILineEdit::DrawText( const cgRectF& clipRect )
{
	if (m_enmType == enmUIEditType_Normal)
	{
		DrawScrollCaption(clipRect, m_strText.c_str());

	}else if (m_enmType == enmUIEditType_Password)
	{
		cgString strCode(m_strText.length(), TEXT('*'));

		DrawScrollCaption(clipRect, strCode.c_str());
	}

}

void cgUILineEdit::DrawScrollCaption( const cgRectF& clipRect, LPCTSTR lpctStr )
{
	int nEndIndex = XPointToCharIndex(m_kRect.GetRight(), 1);// 向前
	
	DrawSelBar(clipRect);

	// todo edit问题太多了
	int yOff = m_kRect.y + (m_kRect.h-GetUICharSize(lpctStr[0]).h)/2;

	cgUIRender::GetRender()->DrawUIText(lpctStr+m_nFirstVisibleCharIndex, nEndIndex-m_nFirstVisibleCharIndex,
		m_kRect.x, yOff, m_idFont, m_uTextColor);

	DrawCursor();

}

void cgUILineEdit::DrawSelBar(const cgRectF& clipRect)
{
	if (IsFocus() && m_nSelBegin != m_nCursorPos)
	{
		int nCursorX = CharIndexToXPoint(m_nCursorPos);
		int nSelX = CharIndexToXPoint(m_nSelBegin);

		int nBarBegin = max(min(nCursorX, nSelX), m_kRect.x+1);
		int nBarEnd = min(max(nCursorX, nSelX)+1, m_kRect.GetRight());

		cgUIRender::GetRender()->FillRect(cgRectF(nBarBegin, m_kRect.y, nBarEnd-nBarBegin, m_kRect.h), m_uSelBackColor);
	}
}

void cgUILineEdit::DrawCursor()
{
	if (IsCursorDrawable())
	{
		int nPosX = CharIndexToXPoint(m_nCursorPos)+1;
		if (nPosX >= m_kRect.GetRight())
			nPosX = m_kRect.GetRight()-1;
		cgUIRender::GetRender()->DrawLine(cgPoint(nPosX, m_kRect.y+1), cgPoint(nPosX, m_kRect.y+m_kRect.h-1), m_uTextColor);
	}
}



// -----------------------------------------------------------------------------------------