#include "Debug.h"

namespace Debug
{
	template <>
	void Output(const tstring & name, const tstring & value, bool newLine)
	{
		tstring output = name + _T(": ") + value + (newLine ? _T("\n") : _T(""));
		OutputDebugString(output.c_str());
	}

	template <>
	void Output(const tstring & name, const std::string & value, bool newLine)
	{
		std::string output = std::string(name.begin(), name.end()) + ": " + value + (newLine ? "\n" : "");
		OutputDebugStringA(output.c_str());
	}

	template <>
	void Output(const tstring & name, const D3DXVECTOR2 & value, bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T("(");
		strstr << value.x << _T(", ") << value.y << _T(")");
		strstr << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}

	template <>
	void Output(const tstring & name, const D3DXVECTOR3 & value, bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T("(");
		strstr << value.x << _T(", ") << value.y << _T(", ") << value.z << _T(")");
		strstr << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}

	template <>
	void Output(const tstring & name, const D3DXVECTOR4 & value, bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T("(");
		strstr << value.x << _T(", ") << value.y << _T(", ") << value.z << _T(", ");
		strstr << value.w << _T(")");
		strstr << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}

	template <>
	void Output(const tstring & name, const D3DXQUATERNION & value, bool newLine)
	{
		tstringstream strstr;
		strstr << name << _T("(");
		strstr << value.x << _T(", ") << value.y << _T(", ") << value.z << _T(", ");
		strstr << value.w << _T(")");
		strstr << (newLine ? _T("\n") : _T(""));
		OutputDebugString(strstr.str().c_str());
	}
}