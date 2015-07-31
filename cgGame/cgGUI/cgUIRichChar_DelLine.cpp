#include "StdAfx.h"
#include "cgUIRichChar_DelLine.h"

void cgUIRichChar_DelLine::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PushDelLine();
}

void cgUIRichChar_DelLineEnd::Draw( cgUIRichPen & pen, int x, int y )
{
	pen.PopDelLine();
}
