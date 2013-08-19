//====================== #INCLUDES ===================================
#include "XMLParser.h"
#include <vector>
//====================================================================

//====================== STATICS =====================================
tstring XMLParser::m_Directory = _T("");
//====================================================================

XMLParser::XMLParser(const tstring & file_name, bool useDefaultDirectory)
	: m_UseDefaultDirectory(useDefaultDirectory)
{
	Load(file_name);
}

XMLParser::~XMLParser() //Default Destructor
{
}

void XMLParser::SetDirectory(const tstring & path)
{
	m_Directory = path;
}

void XMLParser::Load(const tstring & file_name)
{
	m_FileName = file_name;
	Reload();
}

void XMLParser::Reload()
{
	//add directory path and xml extension to the file name
	tstring file_path(_T(""));
	if(m_UseDefaultDirectory)
		file_path = m_Directory;
	file_path.append(m_FileName).append(_T(".xml"));

	pugi::xml_parse_result result = m_XMLDocument.load_file(file_path.c_str());
	

	#ifndef NDEBUG
		//assert if document can't load for any reason
		ASSERTC(result, result.description());
	#endif
}

void XMLParser::Save()
{
	SaveAs(m_FileName);
}

void XMLParser::SaveAs(const tstring & file_name)
{
	tstring file_path(_T(""));
	if(m_UseDefaultDirectory)
	{
		file_path = m_Directory;	
	}
	file_path.append(file_name).append(_T(".xml"));
	m_XMLDocument.save_file(file_path.c_str());
}

pugi::xml_node XMLParser::GetRoot() const
{
	//First child of an pugi::xml_document is the root node
	return m_XMLDocument.first_child();
}
	
//1 layer version - Get Node via the XML_PARSER_LAYER test.
pugi::xml_node XMLParser::GetNode(const XML_PARSER_LAYER & node_test) const
{
	//get root_node and use than the private node_test function
	pugi::xml_node node = GetRoot();
	return GetNode(node, node_test);
}

//2 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	node = GetNode(node, node_1_test);
	return node;
}
//3 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//4 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//5 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//6 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	layerTests.push_back(node_5_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//7 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
						const XML_PARSER_LAYER & node_6_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	layerTests.push_back(node_5_test);
	layerTests.push_back(node_6_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//8 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
						const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	layerTests.push_back(node_5_test);
	layerTests.push_back(node_6_test);
	layerTests.push_back(node_7_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//9 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
						const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test,
						const XML_PARSER_LAYER & node_8_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	layerTests.push_back(node_5_test);
	layerTests.push_back(node_6_test);
	layerTests.push_back(node_7_test);
	layerTests.push_back(node_8_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}

//10 layers version - Get Node via the XML_PARSER_LAYER tests.
pugi::xml_node XMLParser::GetNode(	const XML_PARSER_LAYER & node_0_test, const XML_PARSER_LAYER & node_1_test,
						const XML_PARSER_LAYER & node_2_test, const XML_PARSER_LAYER & node_3_test,
						const XML_PARSER_LAYER & node_4_test, const XML_PARSER_LAYER & node_5_test,
						const XML_PARSER_LAYER & node_6_test, const XML_PARSER_LAYER & node_7_test,
						const XML_PARSER_LAYER & node_8_test, const XML_PARSER_LAYER & node_9_test) const
{
	pugi::xml_node node = GetNode(node_0_test);
	std::vector<XML_PARSER_LAYER> layerTests;
	layerTests.push_back(node_1_test);
	layerTests.push_back(node_2_test);
	layerTests.push_back(node_3_test);
	layerTests.push_back(node_4_test);
	layerTests.push_back(node_5_test);
	layerTests.push_back(node_6_test);
	layerTests.push_back(node_7_test);
	layerTests.push_back(node_8_test);
	layerTests.push_back(node_9_test);
	for (auto it : layerTests)
	{
		node = GetNode(node, it);
	}
	return node;
}
	
pugi::xml_node XMLParser::GetNode(const pugi::xml_node & node, const XML_PARSER_LAYER & node_test) const
{
	//Private node_test.
	//This function will be used for both one_layer as multiple_layer tests
	//It excecutes the test of choice, which gives the user(programmer) a lot of freedom
	// As their are a lot of dangers in this freedom their are multiple asserts placed 
	// to protect an unknowing user.
	switch(node_test.Category)
	{
	case xml_test_node_attribute:
		return GetNode(node, node_test.NodeName, node_test.AttributeName, node_test.AttributeValue);
	case xml_test_node_value:
		return GetNode(node, node_test.NodeName, node_test.NodeValue);
	default:
		return GetNode(node, node_test.NodeName);
	}
}

pugi::xml_node XMLParser::GetNode(const pugi::xml_node & node, const tstring & node_name) const
{
	ASSERT(node.first_child() != nullptr, _T("This node doesn't have children!"));
	for(auto node_it : node.children())
	{
		tstring nodeName(CHARToString(node_it.name()));
		if(nodeName == node_name)
			return node_it;
	}
	tstringstream strstr;
	strstr << _T("Can't find the node '") << node_name << _T("' in xml file '")
		<< m_FileName << _T(".xml'.");
	ASSERT(false, strstr.str().c_str());
	return node;
}

pugi::xml_node XMLParser::GetNode(const pugi::xml_node & node, const tstring & node_name, 
								  const tstring & attribute_name, const tstring & attribute_value) const
{
	ASSERT(node.first_child() != nullptr, _T("This node doesn't have children!"));
	for(auto node_it : node.children())
	{
		tstring nodeName = CHARToString(node_it.name());
		auto attribute = node_it.find_attribute([&attribute_name](const pugi::xml_attribute & attribute)
		{
			tstring attribute_name(CHARToString(attribute.name()));
			return attribute_name == attribute_name;
		});
		if(nodeName == node_name
			&& attribute != nullptr 
			&& CHARToString(attribute.value()) == attribute_value)
		{
			return node_it;
		}
	}
	tstringstream strstr;
	strstr << _T("Can't find the node '") << node_name << _T("' with attribute name '")
		<< attribute_name << _T("' and attribute value '") << attribute_value << 
		_T("' in xml file '") << m_FileName << _T(".xml'!");
	ASSERT(false, strstr.str().c_str());
	return node;
}

pugi::xml_node XMLParser::GetNode(const pugi::xml_node & node, const tstring & node_name, 
								  const tstring & node_value) const
{
	ASSERT(node.first_child() != nullptr, _T("This node doesn't have children!"));
	for(auto node_it : node.children())
	{
		tstring nodeName = CHARToString(node_it.name());
		if(nodeName == node_name
			&& CHARToString(node_it.value()) == node_value)
		{
			return node_it;
		}
	}
	tstringstream strstr;
	strstr << _T("Can't find the node '") << node_name << _T("' with node value '")
		<< node_value << __T("' in xml file '") << m_FileName << _T(".xml'!");
	ASSERT(false, strstr.str().c_str());
	return node;
}

	
tstring CHARToString(const pugi::char_t * str)
{
		std::string stringNodeName(str);
		tstring nodeName(stringNodeName.begin(), stringNodeName.end());
		return nodeName;
}

//public non-member function to convert a tstring to a char array cstring.
const pugi::char_t * StringToCHAR(tstring str)
{
#pragma warning( disable : 4996 )
	int BUFFER_SIZE = str.size() + 1;
    char    *pMBBuffer = (char *)malloc( BUFFER_SIZE );
    wcstombs(pMBBuffer, str.c_str(), BUFFER_SIZE );
#pragma warning( default : 4996 )
	return pMBBuffer;
}

template <>
tstring GetAttribueValue(const pugi::xml_node & node, const tstring & attribute_name)
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
	strstr << CHARToString(found_attribute.value());
	return strstr.str();
}

template <>
std::string GetAttribueValue(const pugi::xml_node & node, const tstring & attribute_name)
{
	tstring strValue = GetAttribueValue<tstring>(node, attribute_name);
	return std::string(strValue.begin(), strValue.end());
}

//public non-member template specialized function to set an attribute value
template <>
bool SetAttributeValue(const pugi::xml_node & node, const tstring & attribute_name, const std::string & attribute_value)
{
	pugi::xml_attribute attribute = node.find_attribute([&attribute_name](const pugi::xml_attribute &test_attribute)
	{
		return CHARToString(test_attribute.name()) == attribute_name;
	});
	ASSERT(attribute != nullptr, _T("Couldn't find the attribute in the node."));
	attribute.set_value(attribute_value.c_str());
	return attribute != nullptr;
}

//public non-member template function to change an attribute's name
bool SetAttributeName(const pugi::xml_node & node, const tstring & attribute_name, const tstring & attribute_new_name)
{
	pugi::xml_attribute attribute = node.find_attribute([&attribute_name](const pugi::xml_attribute &test_attribute)
	{
		return CHARToString(test_attribute.name()) == attribute_name;
	});
	ASSERT(attribute != nullptr, _T("Couldn't find the attribute in the node."));
	attribute.set_name(StringToCHAR(attribute_new_name));
	return attribute != nullptr;
}

//public non-member template function to add a new attribute
template <>
void AddAttribute(pugi::xml_node & node, const tstring & attribute_name, const std::string & attribute_value, bool append)
{
	if(append)
	{
		const pugi::char_t * cStr = StringToCHAR(attribute_name);
		node.append_attribute(cStr);
		delete [] cStr;
	}
	else
	{
		const pugi::char_t * cStr = StringToCHAR(attribute_name);
		node.prepend_attribute(cStr);
		delete [] cStr;
	}
	SetAttributeValue(node, attribute_name, attribute_value);
}

//public non-member template function to change a node's name
bool SetChildName(const pugi::xml_node & node, const tstring & node_name, const tstring & node_new_name)
{
	pugi::xml_node foundNode = node.find_child([&node_name](const pugi::xml_node &test_node)
	{
		return CHARToString(test_node.name()) == node_name;
	});
	ASSERT(foundNode != nullptr, _T("Couldn't find the child in the node."));
	foundNode.set_name(StringToCHAR(node_new_name));
	return foundNode != nullptr;
}

//public non-member template function to set a node's value (string specialization)
template <>
bool SetChildValue(const pugi::xml_node & node, const tstring & node_name, const std::string & node_value)
{
	pugi::xml_node foundNode = node.find_child([&node_name](const pugi::xml_node &test_node)
	{
		return CHARToString(test_node.name()) == node_name;
	});
	ASSERT(foundNode != nullptr, _T("Couldn't find the child in the node."));
	foundNode.set_value(node_value.c_str());
	return foundNode != nullptr;
}

//public non-member template function to add a new attribute
template <>
void AddNode(pugi::xml_node & node, const tstring & node_name, const std::string & node_value, bool append)
{
	if(append)
	{
		const pugi::char_t * cStr = StringToCHAR(node_name);
		node.append_child(cStr);
		delete [] cStr;
	}
	else
	{
		const pugi::char_t * cStr = StringToCHAR(node_name);
		node.prepend_child(StringToCHAR(node_name));
		delete [] cStr;
	}
	SetChildValue(node, node_name, node_value);
}
//
//public non-member template function to remove a node
bool RemoveNode(pugi::xml_node & node, const tstring & node_name)
{
	return node.remove_child(StringToCHAR(node_name));
}

//public non-member template function to remove an attribute
bool RemoveAttribute(pugi::xml_node & node, const tstring & attribute_name)
{
	return node.remove_attribute(StringToCHAR(attribute_name));
}