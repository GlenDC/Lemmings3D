#pragma once
//====================== #INCLUDES ===================================
#include "../XML/XMLParser.h"
//====================================================================

//====================== ParameterClass Class =================================
// Description:
//		A stand automatic parameter class.
//		With a custom XML format it will reconogize the correct variables automaticly
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ParameterClass
{
public:
	ParameterClass();
	ParameterClass(const tstring & file);
	~ParameterClass();

	ParameterClass(const ParameterClass& yRef);									
	ParameterClass& operator=(const ParameterClass& yRef);

	void Refresh();

	template <typename T>
	T GetParameter(const tstring & parameter_name) const
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(const pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<T>(parameter_value);
			}
		}
		
		return 0;
	}

	template <>
	D3DXVECTOR2 GetParameter<D3DXVECTOR2>(const tstring & parameter_name) const
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(const pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR2>(parameter_value);
			}
		}
		return D3DXVECTOR2();
	}

	template <>
	D3DXVECTOR3 GetParameter<D3DXVECTOR3>(const tstring & parameter_name) const
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(const pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR3>(parameter_value);
			}
		}
		return D3DXVECTOR3();
	}

	template <>
	D3DXVECTOR4 GetParameter<D3DXVECTOR4>(const tstring & parameter_name) const
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(const pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR4>(parameter_value);
			}
		}
		return D3DXVECTOR4();
	}

	template <>
	D3DXQUATERNION GetParameter<D3DXQUATERNION>(const tstring & parameter_name) const
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(const pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXQUATERNION>(parameter_value);
			}
		}
		return D3DXQUATERNION();
	}

	template <typename T>
	bool SetParameter(const tstring & parameter_name, const T & parameter)
	{
		pugi::xml_node root = m_pParser->GetRoot();
		for(pugi::xml_node & child : root.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
			{
				SetAttributeValue<T>(child, _T("value"), parameter);
				return true;
			}
		}
		return false;
	}

	template <typename T>
	T GetChildParameter(const tstring & parameter_name, const tstring & child_name) const
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(const pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<T>(parameter_value);
			}
		}
		
		return 0;
	}

	template <>
	D3DXVECTOR2 GetChildParameter<D3DXVECTOR2>(const tstring & parameter_name, const tstring & child_name) const
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(const pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR2>(parameter_value);
			}
		}
		return D3DXVECTOR2();
	}

	template <>
	D3DXVECTOR3 GetChildParameter<D3DXVECTOR3>(const tstring & parameter_name, const tstring & child_name) const
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(const pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR3>(parameter_value);
			}
		}
		return D3DXVECTOR3();
	}

	template <>
	D3DXVECTOR4 GetChildParameter<D3DXVECTOR4>(const tstring & parameter_name, const tstring & child_name) const
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(const pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXVECTOR4>(parameter_value);
			}
		}
		return D3DXVECTOR4();
	}

	template <>
	D3DXQUATERNION GetChildParameter<D3DXQUATERNION>(const tstring & parameter_name, const tstring & child_name) const
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(const pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				tstring parameter_value = GetAttribueValue<tstring>(child, _T("value"));
				return XMLConverter::ConvertTString<D3DXQUATERNION>(parameter_value);
			}
		}
		return D3DXQUATERNION();
	}

	template <typename T>
	bool SetChildParameter(const tstring & parameter_name, const tstring & child_name, const T & parameter)
	{
		pugi::xml_node node = GetChild(parameter_name);
		for(pugi::xml_node & child : node.children())
		{
			if(GetAttribueValue<tstring>(child, _T("name")) == child_name)
			{
				SetAttributeValue<T>(child, _T("value"), parameter);
				return true;
			}
		}
		return false;
	}

	void Save();

private:
	const pugi::xml_node & GetChild(const tstring & parameter_name) const;

	XMLParser *m_pParser;
	pugi::xml_node m_EmptyNode;
};