#include "StdAfx.h"
#include "cgUIObject.h"
#include "cgUIEventListener.h"
#include <cgRender.h>
#include "cgCursorManager.h"
#include "cgSrcImageManager.h"


// -----------------------------------------------------------------------

#ifdef _DEBUG
#define _DEBUG_LOG_UI_BASE_
#endif
// -----------------------------------------------------------------------

cgUIObject::cgUIObject(void)
{
	m_strName = "cgUIObject";
	SetupParams();
}

cgUIObject::cgUIObject( const string & strName )
{
	m_strName = strName;
	SetupParams();
}


cgUIObject::~cgUIObject(void)
{
#ifdef _DEBUG_LOG_UI_BASE_
	cout<<"<cgUIObject>:"<<GetName().c_str()<<"->Destroyed!"<<endl;
#endif
}


void cgUIObject::SetupParams()
{
	m_pkEventListner = NULL;
	m_uBackColor = 0x8f004f4f;
	m_uBorderColor = 0xff004f4f;
	m_uDrawFlag = 0;

	m_bIsPickable = true;
	m_bIsEventable = true;
	m_strCursor = "Default";

	m_spBackImage = NULL;
}

// -------------------------------------------------------------------------------------------

void cgUIObject::DoRenderSelf( cgCamera * renderCamera )
{
	if (m_uDrawFlag&cgUIObjectDrawFlag_DrawBackGround)
		DrawBackground(renderCamera);

	if (m_uDrawFlag&cgUIObjectDrawFlag_DrawBorder)
		DrawBorder(renderCamera);
}


void cgUIObject::DrawBackground(cgCamera * renderCamera)
{
	cgVector center = GetWorldPosition();
	renderCamera->WorldToScreen(center);

	cgVector scale = GetWorldScale()*renderCamera->GetViewScale();

	cgRectF rect(center.x-m_kSize.w/2*scale.x, 
		center.y-m_kSize.h/2*scale.y,
		m_kSize.w*scale.x, 
		m_kSize.h*scale.y);

	cgRender::Get()->FillRect(rect, m_uBackColor);
}

void cgUIObject::DrawBorder(cgCamera * renderCamera)
{
	cgVector center = GetWorldPosition();
	renderCamera->WorldToScreen(center);

	cgVector scale = GetWorldScale()*renderCamera->GetViewScale();

	cgRectF rect(center.x-m_kSize.w/2*scale.x, 
		center.y-m_kSize.h/2*scale.y,
		m_kSize.w*scale.x, 
		m_kSize.h*scale.y);

	cgRender::Get()->DrawBox(rect, m_uBorderColor);
}

// ----------------------------------------------------------------------------------------------
bool cgUIObject::DoProcessEvent( cgGameObjectEvent eventType, int firstParam, int secondParam )
{
	switch (eventType)
	{
	case cgGameObjectEvent_MouseEnter:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseEnter!"<<endl;
#endif
			cgCursorManager::Get()->SetCursor(m_strCursor);

			DoProcessMouseEnter(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnMouseEnter(this);

			return true;
		}break;
	case cgGameObjectEvent_MouseOut:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseOut!"<<endl;
#endif
			DoProcessMouseOut(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnMouseOut(this);

			return true;
		}break;
	case cgGameObjectEvent_MouseDown:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseDown!"<<endl;
#endif
			DoProcessMouseDown(firstParam, secondParam);
			
			if (m_pkEventListner)
				m_pkEventListner->OnMouseDown(this);

			return true;
		}break;
	case cgGameObjectEvent_MouseUp:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseUp!"<<endl;
#endif
			DoProcessMouseUp(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnMouseUp(this);

			return true;
		}break;
	case cgGameObjectEvent_MouseMove:
		{
#ifdef _DEBUG_LOG_UI_BASE_
		//	cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseMove!"<<endl;
#endif
			DoProcessMouseMove(firstParam, secondParam);
			
			if (m_pkEventListner)
				m_pkEventListner->OnMouseMove(this);
			
			return true;
		}break;
	case cgGameObjectEvent_MouseWheel:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->MouseWheel!"<<endl;
#endif
			DoProcessMouseWheel(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnMouseWheel(this);
			
			return true;
		}break;
	case cgGameObjectEvent_DBClick:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->DbClick!"<<endl;
#endif
			DoProcessDbClick(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnDbClick(this);

			return true;
		}break;

	case cgGameObjectEvent_GainFocus:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->GainFocus!"<<endl;
#endif
			DoProcessGainFocus(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnGainFocus(this);

			return true;
		}break;
	case cgGameObjectEvent_LostFocus:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->LostFocus!"<<endl;
#endif
			DoProcessLostFocus(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnLostFocus(this);

			return true;
		}break;
	case cgGameObjectEvent_InputChar:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->InputChar!"<<endl;
#endif
			DoProcessInputChar(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnInputChar(this);

			return true;
		}break;
	case cgGameObjectEvent_Copy:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->Copy!"<<endl;
#endif
			DoProcessCopy(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnCopy(this);

			return true;
		}break;
	case cgGameObjectEvent_Cut:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->Cut!"<<endl;
#endif
			DoProcessCut(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnCut(this);

			return true;
		}break;
	case cgGameObjectEvent_Paste:
		{
#ifdef _DEBUG_LOG_UI_BASE_
			cout<<"<cgUIObject>:"<<GetName().c_str()<<"->Paste!"<<endl;
#endif
			DoProcessPaste(firstParam, secondParam);

			if (m_pkEventListner)
				m_pkEventListner->OnPaste(this);

			return true;
		}break;

	default:
		break;
	}

	return false;
}

void cgUIObject::DoProcessMouseEnter( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessMouseOut( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessMouseDown( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessMouseUp( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessMouseMove( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessMouseWheel( int firstParam, int secondParam )
{

}


void cgUIObject::DoProcessDbClick( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessGainFocus( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessLostFocus( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessInputChar( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessCopy( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessCut( int firstParam, int secondParam )
{

}

void cgUIObject::DoProcessPaste( int firstParam, int secondParam )
{

}
// -----------------------------------------------------------------------------------
void cgUIObject::SetEventListener( cgUIEventListener * pkListener )
{
	m_pkEventListner = pkListener;
}

void cgUIObject::SetCursor( const string & strCursor )
{
	m_strCursor = strCursor;
}

const string& cgUIObject::GetCursor()const
{
	return m_strCursor;
}

void cgUIObject::SetBackColor( cgColor color )
{
	m_uBackColor = color;
}

cgColor cgUIObject::GetBackColor()const
{
	return m_uBackColor;
}

void cgUIObject::SetBorderColor( cgColor color )
{
	m_uBorderColor = color;
}

cgColor cgUIObject::GetBorderColor() const
{
	return m_uBorderColor;
}


cgUIObjectDrawFlag cgUIObject::GetDrawFlag()const
{
	return m_uDrawFlag;
}

void cgUIObject::SetDrawFlag( cgUIObjectDrawFlag flag )
{
	m_uDrawFlag = flag;
}

void cgUIObject::SetBackImage( const cgString& strPath, bool autoFitSize )
{
	SetBackImage(cgSrcImageManager::Get()->LoadImage(strPath.c_str()), autoFitSize);
}

void cgUIObject::SetBackImage( cgImagePtr spImage, bool autoFitSize )
{
	GetBackImageObject()->SetImage(spImage);
	if (autoFitSize && spImage)
		SetSize(spImage->GetWidth(), spImage->GetHeight());
}
void cgUIObject::SetText( const cgString & strText )
{
	m_strText = strText;
	GetTextObject()->SetText(m_strText);
}

const cgString& cgUIObject::GetText()
{
	return m_strText;
}

// -------------------------------------------------------
void cgUIObject::OnSizeChanged()
{
	if (m_spBackImage)
		m_spBackImage->SetSize(m_kSize);

	if (m_spTextObject)
		m_spTextObject->SetSize(GetSize());
}

cgGameSpiritPtr cgUIObject::GetBackImageObject()
{
	if (!m_spBackImage)
	{
		m_spBackImage = (cgGameSprite*)AttachChild(new cgGameSprite("backImage"));
		m_spBackImage->SetSize(m_kSize);
	}

	return m_spBackImage;
}

cgGameTextPtr cgUIObject::GetTextObject()
{
	if (!m_spTextObject)
	{
		m_spTextObject = (cgGameText*)AttachChild(new cgGameText("text"));
		m_spTextObject->SetSize(GetSize());
	}

	return m_spTextObject;
}



// -----------------------------------------------------------------------------------
