//====================== #INCLUDES ===================================
#include "XMLConverter.h"
//====================================================================

namespace XMLConverter
{
	template <>
	tstring ConvertTString(const tstring & value)
	{
		return value;
	}
	
	template <>
	std::string ConvertTString(const tstring & value)
	{
		return string(value.begin(), value.end());
	}

	template <>
	bool ConvertTString(const tstring & value)
	{
		return value == _T("True") ? true : false;
	}

	template <>
	D3DXVECTOR2 ConvertTString(const tstring & value)
	{
        D3DXVECTOR2 vec;
        int index = value.find(';',0);
		vec.x = ConvertTString<float>(value.substr(0, index));
		vec.y = ConvertTString<float>(value.substr(++index,value.size()-index));
        return vec;
	}

	template <>
	D3DXVECTOR3 ConvertTString(const tstring & value)
	{
        D3DXVECTOR3 vec;
        int index = value.find(';', 0);
		vec.x = ConvertTString<float>(value.substr(0, index));
        int index2 = value.find(';', ++index);
        vec.y = ConvertTString<float>(value.substr(index, index2 - index));
		vec.z = ConvertTString<float>(value.substr(++index2, value.size() - index2));
        return vec;
	}

	template <>
	D3DXVECTOR4 ConvertTString(const tstring & value)
	{
		D3DXVECTOR4 vec;
		int index = value.find(';', 0);
		vec.x = ConvertTString<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		vec.y = ConvertTString<float>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = ConvertTString<float>(value.substr(index2, index - index2));
		vec.w = ConvertTString<float>(value.substr(++index, value.size() - index));
        return vec;
	}

	template <>
	D3DXQUATERNION ConvertTString(const tstring & value)
	{
		D3DXQUATERNION vec;
		int index = value.find(';', 0);
		vec.x = ConvertTString<float>(value.substr(0, index));
		int index2 = value.find(';', ++index);
		vec.y = ConvertTString<float>(value.substr(index, index2 - index));
		index = value.find(';', ++index2);
		vec.z = ConvertTString<float>(value.substr(index2, index - index2));
		vec.w = ConvertTString<float>(value.substr(++index, value.size() - index));
        return vec;
	}

	
	template <>
	tstring ConvertToTString(const tstring & value)
	{
		return value;
	}

	template <>
	tstring ConvertToTString(const std::string & value)
	{
		tstring str(value.begin(), value.end());
		return str;
	}

	template <>
	tstring ConvertToTString(const bool & value)
	{
		tstringstream strstr;
		strstr << value;
		return strstr.str();
	}

	template <>
	tstring ConvertToTString(const D3DXVECTOR2 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";") << value.y ;
		return strstr.str();
	}

	template <>
	tstring ConvertToTString(const D3DXVECTOR3 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";") << value.y 
			<< _T(";") << value.z;
		return strstr.str();
	}

	template <>
	tstring ConvertToTString(const D3DXVECTOR4 & value)
	{
		tstringstream strstr;
		strstr << value.x << _T(";") << value.y 
			<< _T(";") << value.z << _T(";") << value.w;
		return strstr.str();
	}

	template <>
	tstring ConvertToTString(const D3DXQUATERNION & value)
	{
		tstringstream strstr;
		strstr << _T("(") << value.x << _T(",") << value.y 
			<< _T(",") << value.z << _T(",") << value.w << _T(")");
		return strstr.str();
	}
};