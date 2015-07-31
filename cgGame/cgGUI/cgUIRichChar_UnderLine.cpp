#include "StdAfx.h"
#include "cgUIRichChar_UnderLine.h"

void cgUIRichChar_UnderLine::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PushUnderLine();
}

void cgUIRichChar_UnderLineEnd::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PopUnderLine();
}
