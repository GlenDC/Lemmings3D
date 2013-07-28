#pragma once
//====================== #INCLUDES ===================================
#include <D3DX10.h>
#include "Helpers/stdafx.h"
//====================================================================

//====================== Debug Namespace =============================
// Description:
//		Basic functions used for debugging purposes.
// Last Modification: 22/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace Debug
{
	template <typename T>
	void Output(const tstring & name, const T & value, bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T(": ");
		strstr << value << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}

	template <>
	void Output(const tstring & name, const tstring & value, bool newLine);

	template <>
	void Output(const tstring & name, const std::string & value, bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR2 & value, bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR3 & value, bool newLine);

	template <>
	void Output(const tstring & name, const D3DXVECTOR4 & value, bool newLine);

	template <>
	void Output(const tstring & name, const D3DXQUATERNION & value, bool newLine);
}