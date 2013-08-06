//====================== #INCLUDES ===================================
#include "Rectangle.h"
//====================================================================

namespace LemmingsHelpers
{
	Rect::Rect()
		: X(0), Y(0), Width(0), Height(0) {}

	Rect::Rect(const int x, const int y, 
							const int width, const int height)
		: X(x), Y(y), Width(width), Height(height) {}

	Rect::Rect(const Rect& yRef)
		: X(yRef.X), Y(yRef.Y)
		, Width(yRef.Width), Height(yRef.Height) {}

	Rect& Rect::operator=(const Rect& yRef)
	{
		X = yRef.X;
		Y = yRef.Y;
		Width = yRef.Width;
		Height = yRef.Height;
		return (*this);
	}
}