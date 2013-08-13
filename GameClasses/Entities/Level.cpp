//====================== #INCLUDES ===================================
#include "Level.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "SceneGraph/GameScene.h"
//--------------------------------------------------------------------
#include <cmath>
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../XML/XMLParser.h"
#include "../Helpers/HeightmapParser.h"
#include "../Lib/LemmingsHelpers.h"
#include "../GameObjects/InstancedObject.h"
#include "../GameObjects/PhysicsCube.h"
#include "../Managers/ScreenManager.h"
//====================================================================

Level::Level(const tstring & file, GameScene * pScene)
	: m_LevelXMLFileName(file)
	, m_pInstancedObject(nullptr)
	, m_Width(0)
	, m_Height(0)
	, m_SizeXZ(0)
	, m_SizeXYZ(0)
	, m_MinDepth(0)
	, m_MaxDepth(0)
	, m_CurrentDepth(0)
	, m_HeigthDifference(0)
	, m_Name(_T(""))
	, m_Offset(0,0,0)
	, m_pLevelParser(nullptr)
	, m_pPhysicsCubeVec(0)
	, m_pGame(pScene)
{

}

Level::~Level(void)
{
	// release positions;
	/*for(UINT i = 0 ; i < m_Height ; ++i)
	{
		delete [] m_pPositionsHeightMap[i];
	}
	delete [] m_pPositionsHeightMap;*/
	/*for( UINT r = 0; r < m_Height; r++ )
	{
		for( UINT c = 0; c < m_Width; c++ )
		{
			delete m_Cubes2DVector[r][c];
		}
	}*/
	delete m_pInstancedObject;
	for(UINT i = 0 ; i < m_pPhysicsCubeVec.size() ; ++i)
	{
		m_pGame->RemoveSceneObject(m_pPhysicsCubeVec[i]);
		delete m_pPhysicsCubeVec[i];
	}
	m_pPhysicsCubeVec.clear();
}

void Level::Initialize()
{
	//_CrtSetBreakAlloc(14387);
	//Read Level XML File
	tstring contentDirectory(GlobalParameters::GetParameters()->GetParameter<tstring>(_T("CONTENT_DIRECTORY")));
	tstring file(contentDirectory.append(GlobalParameters::GetParameters()->GetParameter<tstring>(_T("LEVEL_DIRECTORY"))));
	file = file.append(m_LevelXMLFileName);

	//Get Root Level Information
	m_pLevelParser = new XMLParser(file, false);
	pugi::xml_node root = m_pLevelParser->GetRoot();
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	tstring heightmapName(GetAttribueValue<tstring>(root, _T("heightmap")));
	m_Width = XMLConverter::ConvertTString<int>(GetAttribueValue<tstring>(root, _T("width")));
	m_Height = XMLConverter::ConvertTString<int>(GetAttribueValue<tstring>(root, _T("height")));
	m_SizeXZ = (UINT)sqrt(pow(m_Width*size,2) + pow(m_Height*size, 2));
	m_Name = GetAttribueValue<tstring>(root, _T("name"));
	//for(const pugi::xml_node & child : root.children())

	//Get Heightmap File and parse it!
	//file = GlobalParameters::GetParameters()->GetParameter<tstring>(_T("CONTENT_DIRECTORY"));
	tstring heightmapFile = _T("./Resources/Lemmings3D/levels/heightmaps/") + heightmapName;

	vector<vector<D3DXVECTOR3>> positionVec;
	D3DXVECTOR2 depth;
	m_HeigthDifference = XMLConverter::ConvertTString<float>(GetAttribueValue<tstring>(root, _T("height_scale")));
	ASSERT(HeightmapParser::Read(heightmapFile, m_Width, m_Height, positionVec, 
		depth, size * m_HeigthDifference, size), _T("an error has occured, while parsing the heightmap!"));
	m_HeigthDifference = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));;

	m_MinDepth = depth.x;
	m_MaxDepth = depth.y;

	UINT sizeY = (UINT)(m_MaxDepth - m_MinDepth);
	m_SizeXYZ = (UINT)sqrt(pow(m_SizeXZ,2) + pow(sizeY, 2));

	m_pInstancedObject = new InstancedObject(_T("./Resources/Lemmings3D/textures/Test64x64.png"));

	m_Offset = GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR3>(_T("LEVEL_OFFSET"));
	//make sure the origin is vertically at the correct origin based on the offset.y
	if(m_MinDepth != m_Offset.y)
	{
		float difference = m_Offset.y - m_MinDepth;
		m_MaxDepth += difference;
		m_MinDepth = m_Offset.y;
		m_Offset.y += difference;
	}
	for(vector<D3DXVECTOR3> vec : positionVec)
	{
		for(D3DXVECTOR3 pos : vec)
		{
			//add offset
			pos += m_Offset;
			if(pos.y < m_Offset.y)
				pos.y += m_MaxDepth;
			//snap to grid defined by grid_size
			LemmingsHelpers::SnapPositionXYZ(pos, size);
			//add cube to world instance!
			UINT counter(0);
			do 
			{
				int newInstanceID(0);
				int rid = rand() % 5;
				if(rid == 1)
					newInstanceID = 6;
				if(rid == 2)
					newInstanceID = 7;
				m_pInstancedObject->AddInstance(pos, newInstanceID);
				//PhysicsCube Creation
				/*PhysicsCube * cube = new PhysicsCube(pos, size);
				m_pGame->AddSceneObject(cube);
				m_pPhysicsCubeVec.push_back(cube);*/
				pos.y -= size;
				++counter;
			} while ( counter < 3 && pos.y > m_Offset.y );
			//Fill holes
			/*do
			{
				m_pInstancedObject->AddInstance(pos, 0);
				pos.y -= size;
			} while(pos.y >= m_MinDepth);*/
		}
	}

	CreateBlocks();
	m_CurrentDepth = (m_MinDepth + m_MaxDepth) / 2.0f;
	m_CurrentDepth = fmod(m_CurrentDepth, m_HeigthDifference);
	PaintBlocks();

	m_pInstancedObject->Initialize();

	///*tstringstream strstr;
	//strstr << _T("HeightMap[") << (m_Height-1) << _T("][") << (m_Width-1) << _T("] == {") <<
	//	m_Positions2DVector[m_Height-1][m_Width-1].x << _T(";") << 
	//	m_Positions2DVector[m_Height-1][m_Width-1].y << _T(";") << 
	//	m_Positions2DVector[m_Height-1][m_Width-1].z << _T("}\n");
	//OutputDebugString(strstr.str().c_str());*/
}

void Level::Draw(const GameContext & context)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));

	if(ScreenManager::GetInstance()->CanDrawPhysics())
	{
		//LemmingsHelpers::DrawGrid((float)m_Width, (float)m_Height, m_MinDepth, m_MaxDepth);
		DebugRenderer::DrawLine(m_Offset, m_Offset + D3DXVECTOR3((float)m_Width * size, 0, 0), D3DXCOLOR(1,0,0,1));
		DebugRenderer::DrawLine(m_Offset, m_Offset + D3DXVECTOR3(0, m_MaxDepth - m_MinDepth, 0), D3DXCOLOR(0,1,0,1));
		DebugRenderer::DrawLine(m_Offset, m_Offset + D3DXVECTOR3(0, 0, m_Height * size), D3DXCOLOR(0,0,1,1));
	}

	//Draw the level
	/*for( UINT r = 0; r < m_Height; r++ )
	{
		for( UINT c = 0; c < m_Width; c++ )
		{
			m_Cubes2DVector[r][c]->Draw(context);
		}
	}*/
	m_pInstancedObject->Draw(context);
}

void Level::Update(const GameContext & context)
{
	//Update the level
	/*for( UINT r = 0; r < m_Height; r++ )
	{
		for( UINT c = 0; c < m_Width; c++ )
		{
			m_Cubes2DVector[r][c]->GetComponent<TransformComponent>()->Translate(m_Positions2DVector[r][c]);
			m_Cubes2DVector[r][c]->Update(context);
		}
	}*/
	m_pInstancedObject->Update(context);
}

const D3DXVECTOR3 & Level::GetSnapPosition(const D3DXVECTOR3 & pos) const
{
	return m_pInstancedObject->GetClosestPosition(pos);
}

void Level::GetEnvironment(std::vector<D3DXVECTOR3> & envVector) const
{
	m_pInstancedObject->ParsePositionVector(envVector);
}

const std::vector<D3DXVECTOR3> & Level::GetEnvironment() const
{
	return m_pInstancedObject->GetPositions();
}

void Level::AddEnvironmentCube(const D3DXVECTOR3 & pos, const int id)
{
	if(m_pInstancedObject->AddInstance(pos, id))
	{
		auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("blocks")));
		pugi::xml_node newNode = node.append_child("block");
		AddAttribute(newNode, _T("pos"), pos, true);
		AddAttribute(newNode, _T("id"), id, true);
	}
}

bool Level::RemoveEnvironmentCube(const D3DXVECTOR3 & pos)
{
	bool removedXML(false);
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("blocks")));
	for(auto node_it : node.children())
	{
		D3DXVECTOR3 testPos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
		if(testPos == pos)
		{
			node.remove_child(node_it);
			removedXML = true;
		}
	}
	return m_pInstancedObject->RemoveInstance(pos) && removedXML;
}

bool Level::PaintEnvironmentCube(const D3DXVECTOR3 & pos, const int id, const bool editInstance)
{
	bool editXML(false);
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("blocks")));
	for(auto node_it : node.children())
	{
		D3DXVECTOR3 testPos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
		if(testPos == pos)
		{
			RemoveAttribute(node_it, _T("id"));
			AddAttribute(node_it, _T("id"), id, true);
			editXML = true;
			break;
		}
	}
	if(!editXML)
	{
		node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("painted")));
		for(auto node_it : node.children())
		{
			D3DXVECTOR3 testPos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
			if(testPos == pos)
			{
				RemoveAttribute(node_it, _T("id"));
				AddAttribute(node_it, _T("id"), id, true);
				editXML = true;
				break;
			}
		}
		if(!editXML)
		{
			pugi::xml_node newNode = node.append_child("paint");
			AddAttribute(newNode, _T("pos"), pos, true);
			AddAttribute(newNode, _T("id"), id, true);
			editXML = true;
		}
	}
	bool instanceCheck(true);
	if(editInstance)
	{
		instanceCheck = m_pInstancedObject->EditInstance(pos,id);
	}
	return instanceCheck && editXML;
}

void Level::RecheckEnvironment()
{
	vector<InstanceType> vec;
	m_pInstancedObject->RecheckCubes(vec);
	for(UINT i = 0 ; i < vec.size() ; ++i)
	{
		PaintEnvironmentCube(vec[i].Position, vec[i].ID, false);
	}
}

void Level::Save()
{
	m_pLevelParser->Save();
}

float Level::GetLowerDepth()
{
	m_CurrentDepth -= m_HeigthDifference;
	CheckCurrentDepth();
	return m_CurrentDepth;
}

float Level::GetHigherDepth()
{
	m_CurrentDepth += m_HeigthDifference;
	CheckCurrentDepth();
	return m_CurrentDepth;
}

void Level::CreateBlocks()
{
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("blocks")));
	for(auto node_it : node.children())
	{
		D3DXVECTOR3 pos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
		if(pos.y < m_MinDepth) 
		{
			m_MinDepth = pos.y;
		}
		else if (pos.y > m_MaxDepth)
		{
			m_MaxDepth = pos.y;
		}
		int id = GetAttribueValue<int>(node_it, _T("id"));
		m_pInstancedObject->AddInstance(pos, id);
	}
}

void Level::PaintBlocks()
{
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("painted")));
	for(auto node_it : node.children())
	{
		D3DXVECTOR3 pos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
		int id = GetAttribueValue<int>(node_it, _T("id"));
		m_pInstancedObject->EditInstance(pos, id);
	}
}

void Level::CheckCurrentDepth()
{
	if(m_CurrentDepth < m_MinDepth)
	{
		m_CurrentDepth = m_MinDepth;
	}
	else if(m_CurrentDepth > m_MaxDepth)
	{
		m_CurrentDepth = m_MaxDepth;
	}
	//recheck physics!
}