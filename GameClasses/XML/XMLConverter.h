#pragma once
//====================== #INCLUDES ===================================
#include "helpers/D3DUtil.h"
//====================================================================

//====================== XMLConverter NameSpace =================================
// Description:
//		Convert classes/types from/to XML format strings
// Last Modification: 11/03/2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

namespace XMLConverter
{
	template <typename T>
	T ConvertTString(const tstring & value)
	{
		T var(0);
		tstringstream strstr;
		strstr << value;
		strstr >> var;
		return var;
	}
	template <>
	tstring ConvertTString(const tstring & value);

	template <>
	std::string ConvertTString(const tstring & value);

	template <>
	bool ConvertTString(const tstring & value);

	template <>
	D3DXVECTOR2 ConvertTString(const tstring & value);

	template <>
	D3DXVECTOR3 ConvertTString(const tstring & value);

	template <>
	D3DXVECTOR4 ConvertTString(const tstring & value);

	template <>
	D3DXQUATERNION ConvertTString(const tstring & value);

	template <typename T>
	tstring ConvertToTString(const T & value)
	{
		tstringstream strstr;
		strstr << value;
		return strstr.str();
	}
	template <>
	tstring ConvertToTString(const tstring & value);

	template <>
	tstring ConvertToTString(const std::string & value);

	template <>
	tstring ConvertToTString(const bool & value);

	template <>
	tstring ConvertToTString(const D3DXVECTOR2 & value);

	template <>
	tstring ConvertToTString(const D3DXVECTOR3 & value);

	template <>
	tstring ConvertToTString(const D3DXVECTOR4 & value);

	template <>
	tstring ConvertToTString(const D3DXQUATERNION & value);
};