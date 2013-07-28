#pragma once

//====================== #INCLUDES ===================================
//====================================================================

//====================== Rect Class ============================
// Description:
//		Self written rectangle class, that works with width/height
// Last Modification: 20/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace LemmingsHelpers
{
	class Rect
	{
	public:
		Rect();
		Rect(int x, int y, int width, int height);
		Rect(const Rect& yRef);									
		Rect& operator=(const Rect& yRef);

		~Rect();

		int X, Y, Width, Height;
	};
};