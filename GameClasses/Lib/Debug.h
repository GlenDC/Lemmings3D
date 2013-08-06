#pragma once
//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include <D3DX10.h>
//====================================================================

//====================== Debug Namespace =============================
// Description:
//		Basic functions used for debugging purposes.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace Debug
{
	template <typename T>
	void Output(const tstring & name, const T & value, const bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T(": ");
		strstr << value << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}

	template <>
	void Output(const tstring & name, const tstring & value, const bool newLine);

	template <>
	void Output(const tstring & name, const std::string & value, const bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR2 & value, const bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR3 & value, const bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR4 & value, const bool newLine);

	template <>
	void Output(const tstring & name, const D3DXQUATERNION & value, const bool newLine);
}