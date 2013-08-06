#pragma once
//====================== #INCLUDES ===================================
#include "XMLConverter.h"
#include "../../PugiXML/src/pugixml.hpp"
#include "../../PugiXML/src/pugiconfig.hpp"
//====================================================================

//====================== XMLParser Class =============================
// Description:
//		Parser class used to have some automatisation 
//		based on the PugiXML Library.
// Last Modification: 11/03/2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

//====================== UNSOLVED BUGS ===============================
//	+ Value related Set functions don't work.
//		PugiXML probably used something else to set values!
//====================================================================

enum LayerTestCategory
{
	xml_test_node,
	xml_test_node_attribute,
	xml_test_node_value
};

struct XML_PARSER_LAYER
{
	LayerTestCategory Category;
	tstring NodeName;
	tstring AttributeName;
	tstring AttributeValue;
	tstring NodeValue;

	XML_PARSER_LAYER(LayerTestCategory category, const tstring & layer_name)
		:Category(category)
		,NodeName(layer_name)
		,AttributeName(_T(""))
		,AttributeValue(_T(""))
		,NodeValue(_T(""))
	{}

	XML_PARSER_LAYER(LayerTestCategory category, const tstring & layer_name,
		const tstring & attribute_name, const tstring & attribute_value)
		:Category(category)
		,NodeName(layer_name)
		,AttributeName(attribute_name)
		,AttributeValue(attribute_value)
		,NodeValue(_T(""))
	{}

	XML_PARSER_LAYER(LayerTestCategory category, const tstring & layer_name,
		const tstring & layer_value)
		:Category(category)
		,NodeName(layer_name)
		,AttributeName(_T(""))
		,AttributeValue(_T(""))
		,NodeValue(layer_value)
	{}
};

class XMLParser
{
public:
	XMLParser(const tstring & file_name, bool useDefaultDirectory = true);
	~XMLParser();

	static void SetDirectory(const tstring & path);
	
	void Load(const tstring & file_name);
	void Reload();
	void Save();
	void SaveAs(const tstring & file_name);

	pugi::xml_node GetRoot() const;
	//1 layer version - Get Node via the XML_PARSER_LAYER test.
	pugi::xml_node GetNode(const XML_PARSER_LAYER & node_0_test) const;
	//2 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test) const;
	//3 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test) const;
	//4 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test) const;
	//5 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test) const;
	//6 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test) const;
	//7 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
							const XML_PARSER_LAYER & node_6_test) const;
	//8 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
							const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test) const;
	//9 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
							const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test,
							const XML_PARSER_LAYER & node_8_test) const;
	//10 layers version - Get Node via the XML_PARSER_LAYER tests.
	pugi::xml_node GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
							const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
							const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
							const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test,
							const XML_PARSER_LAYER & node_8_test, const XML_PARSER_LAYER & node_9_test) const;

private:
	static tstring m_Directory;
	tstring m_FileName;

	bool m_UseDefaultDirectory;

	//Document loaded via class constructor
	pugi::xml_document m_XMLDocument;
	
	//private main node_test function, will excecute one of the 3 test functions
	pugi::xml_node GetNode(const pugi::xml_node & node, const XML_PARSER_LAYER & node_test) const;
	//first test, testing just on the node's name
	pugi::xml_node GetNode(const pugi::xml_node & node, const tstring & node_name) const;
	//second test, testing not only on the node's name, but also on an attribute's value
	pugi::xml_node GetNode(const pugi::xml_node & node, const tstring & node_name, const tstring & attribute_name, const tstring & attribute_value) const;
	//third test, testing not only on the node's name, but also on it's value
	pugi::xml_node GetNode(const pugi::xml_node & node, const tstring & node_name, const tstring & node_value) const;

	// Disabling default copy constructor and default assignment operator.
	XMLParser(const XMLParser& yRef);									
	XMLParser& operator=(const XMLParser& yRef);
};

//public non-member function to convert a char. array to a tstring variable.
tstring CHARToString(const pugi::char_t * str);

//public non-member function to convert a tstring to a char array cstring.
const pugi::char_t * StringToCHAR(tstring str);

//public non-member template function return attribute_value
template <typename T>
T GetAttribueValue(const pugi::xml_node & node, const tstring & attribute_name)
{
	tstringstream strstr;
	pugi::xml_attribute found_attribute(nullptr);
	for (const pugi::xml_attribute & attribute : node.attributes())
	{
		if(CHARToString(attribute.name()) == attribute_name)
		{
			found_attribute = attribute;
		}
	}
	ASSERT(found_attribute != nullptr, _T("Attribute not found."));
	strstr << found_attribute.value();
	tstring valueString;
	strstr >> valueString;
	return XMLConverter::ConvertTString<T>(valueString);
}

//public non-member template function specialization for string values
template <>
tstring GetAttribueValue(const pugi::xml_node & node, const tstring & attribute_name);

//public non-member template function specialization for string values
template <>
std::string GetAttribueValue(const pugi::xml_node & node, const tstring & attribute_name);

//public non-member template function to set an attribute value
template <typename T>
bool SetAttributeValue(const pugi::xml_node & node, const tstring & attribute_name, const T & attribute_value)
{
	tstringstream strstr;
	strstr << _T("") << XMLConverter::ConvertToTString<T>(attribute_value);
	pugi::xml_attribute attribute = node.find_attribute([&attribute_name](const pugi::xml_attribute &test_attribute)
	{
		return CHARToString(test_attribute.name()) == attribute_name;
	});
	ASSERT(attribute != nullptr, _T("Couldn't find the attribute in the node."));
	const pugi::char_t * valueString = StringToCHAR(strstr.str());
	attribute.set_value(valueString);
	delete [] valueString;
	return attribute != nullptr;
}

//public non-member template specialized function to set an attribute value
template <>
bool SetAttributeValue(const pugi::xml_node & node, const tstring & attribute_name, const std::string & attribute_value);

//public non-member template function to change an attribute's name
bool SetAttributeName(const pugi::xml_node & node, const tstring & attribute_name, const tstring & attribute_new_name);

//public non-member template function to add a new attribute
template <typename T>
void AddAttribute(pugi::xml_node & node, const tstring & attribute_name, const T & attribute_value, bool append)
{
	if(append)
	{
		node.append_attribute(StringToCHAR(attribute_name));
	}
	else
	{
		node.prepend_attribute(StringToCHAR(attribute_name));
	}
	SetAttributeValue(node, attribute_name, XMLConverter::ConvertToTString<T>(attribute_value));
}

//public non-member template function to add a new attribute
template <>
void AddAttribute(pugi::xml_node & node, const tstring & attribute_name, const std::string & attribute_value, bool append);

//public non-member template function to change a node's name
bool SetChildName(const pugi::xml_node & node, const tstring & node_name, const tstring & node_new_name);

//public non-member template function to set a node's value
template <typename T>
bool SetChildValue(const pugi::xml_node & node, const tstring & node_name, const T & node_value)
{
	tstringstream strstr;
	strstr << node_value;
	pugi::xml_node foundNode = node.find_child([&node_name](const pugi::xml_node &test_node)
	{
		return CHARToString(test_node.name()) == node_name;
	});
	ASSERT(foundNode != nullptr, _T("Couldn't find the child in the node."));
	foundNode.set_value(StringToCHAR(strstr.str()));
	return foundNode != nullptr;
}

////public non-member template function to set a node's value (string specialization)
template <>
bool SetChildValue(const pugi::xml_node & node, const tstring & node_name, const std::string & node_value);

//public non-member template function to add a new attribute
template <typename T>
void AddNode(pugi::xml_node & node, const tstring & node_name, const T & node_value, bool append)
{
	tstringstream strstr;
	strstr << node_value;
	if(append)
	{
		node.append_child(StringToCHAR(node_name));
	}
	else
	{
		node.prepend_child(StringToCHAR(node_name));
	}
	SetChildValue(node, node_name, strstr.str());
}

//public non-member template function to add a new attribute
template <>
void AddNode(pugi::xml_node & node, const tstring & node_name, const std::string & node_value, bool append);

//public non-member template function to remove a node
bool RemoveNode(pugi::xml_node & node, const tstring & node_name);

//public non-member template function to remove an attribute
bool RemoveAttribute(pugi::xml_node & node, const tstring & attribute_name);