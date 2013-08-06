#pragma once

//====================== #INCLUDES ===================================
//====================================================================

//====================== Rect Struct ============================
// Description:
//		Self written rectangle class, that works with width/height
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace LemmingsHelpers
{
	struct Rect
	{
	public:
		Rect();
		Rect(int x, int y, int width, int height);
		Rect(const Rect& yRef);									
		Rect& operator=(const Rect& yRef);

		int X, Y, Width, Height;
	};
};