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
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/KeyObject.h"
#include "../GameObjects/Decal.h"
#include "../GameObjects/SkyBox.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/ParameterManager.h"
#include "../Materials/BaseModelMaterial.h"
#include "../GameObjects/PortalEnter.h"
#include "../GameObjects/PortalExit.h"
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
	, m_Center(0,0,0)
	, m_pLevelParser(nullptr)
	, m_pPhysicsCubeVec(0)
	, m_ColissionEntities(0)
	, m_GameEntities(0)
	, m_pSkyBox(nullptr)
	, m_pPortalEntrance(nullptr)
	, m_pPortalExit(nullptr)
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
	m_pPhysicsCubeVec.clear();
	m_ColissionEntities.clear();
	m_GameEntities.clear();
	delete m_pSkyBox;
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


	bool create_blocks = GlobalParameters::GetParameters()->GetParameter<bool>(_T("CREATE_LEVEL_BLOCKS"));
	bool create_objects = GlobalParameters::GetParameters()->GetParameter<bool>(_T("CREATE_LEVEL_OBJECTS"));
	m_Offset = GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR3>(_T("LEVEL_OFFSET"));
	m_HeigthDifference = XMLConverter::ConvertTString<float>(GetAttribueValue<tstring>(root, _T("height_scale")));

	m_pInstancedObject = new InstancedObject(_T("./Resources/Lemmings3D/textures/Test64x64.png"));
	
	if(create_blocks)
	{
		//Get Heightmap File and parse it!
		//file = GlobalParameters::GetParameters()->GetParameter<tstring>(_T("CONTENT_DIRECTORY"));
		tstring heightmapFile = _T("./Resources/Lemmings3D/levels/heightmaps/") + heightmapName;

		vector<vector<D3DXVECTOR3>> positionVec;
		D3DXVECTOR2 depth;
		ASSERT(HeightmapParser::Read(heightmapFile, m_Width, m_Height, positionVec, 
			depth, size * m_HeigthDifference, size), _T("an error has occured, while parsing the heightmap!"));
		m_HeigthDifference = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));;

		m_MinDepth = depth.x;
		m_MaxDepth = depth.y;

		UINT sizeY = (UINT)(m_MaxDepth - m_MinDepth);
		m_SizeXYZ = (UINT)sqrt(pow(m_SizeXZ,2) + pow(sizeY, 2));
		//make sure the origin is vertically at the correct origin based on the offset.y
		if(m_MinDepth != m_Offset.y)
		{
			float difference = m_Offset.y - m_MinDepth;
			m_MaxDepth += difference;
			m_MinDepth = m_Offset.y;
			m_Offset.y += difference;
		}

		float minDepth(999999), maxDepth(0);
		float minX(999999), maxX(0), minZ(9999999), maxZ(0);

		for(vector<D3DXVECTOR3> vec : positionVec)
		{
			for(D3DXVECTOR3 pos : vec)
			{
				//add offset
				pos += m_Offset;
				if(pos.y < m_Offset.y)
					pos.y += m_MaxDepth;
				if(pos.y < minDepth)
				{
					minDepth = pos.y;
				}
				else if(pos.y > maxDepth)
				{
					maxDepth = pos.y;
				}
				if(pos.x < minX)
				{
					minX = pos.x;
				}
				else if(pos.x > maxX)
				{
					maxX = pos.x;
				}
				if(pos.z < minZ)
				{
					minZ = pos.z;
				}
				else if(pos.z > maxZ)
				{
					maxZ = pos.z;
				}
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
					m_pGame->AddObject(cube);
					m_pPhysicsCubeVec.push_back(cube);*/
					pos.y -= size;
					++counter;
				} while ( pos.y > m_Offset.y );
				//Fill holes
				/*do
				{
					m_pInstancedObject->AddInstance(pos, 0);
					pos.y -= size;
				} while(pos.y >= m_MinDepth);*/
			}
		}

		m_MinDepth = minDepth;
		m_MaxDepth = maxDepth;

		CreateBlocks();
		m_CurrentDepth = (m_MinDepth + m_MaxDepth) / 2.0f;
		m_Center = D3DXVECTOR3((minX + maxX) / 2.0f, m_CurrentDepth, (minZ + maxZ) / 2.0f);
		m_CurrentDepth -= fmod(m_CurrentDepth, m_HeigthDifference);
		PaintBlocks();
		m_pInstancedObject->Initialize();
	}
	if(create_objects)
	{
		CreateObjects();
	}
	m_pSkyBox = new SkyBox(this, m_Center, _T("grassenvmap1024.dds"));
	m_pSkyBox->Initialize();

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

	m_pSkyBox->Draw(context);

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
	bool create_blocks = GlobalParameters::GetParameters()->GetParameter<bool>(_T("CREATE_LEVEL_BLOCKS"));
	if(create_blocks)
		m_pInstancedObject->Draw(context);

	for( auto pEntity : m_ColissionEntities )
	{
		pEntity->Draw(context);
	}
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
	bool create_blocks = GlobalParameters::GetParameters()->GetParameter<bool>(_T("CREATE_LEVEL_BLOCKS"));
	if(create_blocks)
		m_pInstancedObject->Update(context);

	for( auto pEntity : m_ColissionEntities )
	{
		pEntity->Update(context);
	}
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

void Level::AddSpecialObject(UINT id, const D3DXVECTOR3 & pos)
{
	if(id == 6)
	{
		CreatePortalEntrance(pos);
	}
	else if(id == 7)
	{
		CreatePortalExit(pos);
	}
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
	pugi::xml_node newNode = node.append_child("object");
	AddAttribute(newNode, _T("id"), id, true);
	AddAttribute(newNode, _T("pos"), pos, true);
	AddAttribute(newNode, _T("rot"), D3DXQUATERNION(0,0,0,1), true);
}

void Level::CreatePortalEntrance(const D3DXVECTOR3 & pos)
{
	if(m_pPortalEntrance == nullptr)
	{
		m_pPortalEntrance = new PortalEnter();
		m_pGame->AddSceneObject(m_pPortalEntrance);
		m_pPortalEntrance->Translate(pos);
		m_pPortalEntrance->Initialize();
	}
}

void Level::CreatePortalExit(const D3DXVECTOR3 & pos)
{
	if(m_pPortalExit == nullptr)
	{
		m_pPortalExit = new PortalExit();
		m_pGame->AddSceneObject(m_pPortalExit);
		m_pPortalExit->Translate(pos);
		m_pPortalExit->Initialize();
	}
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

void Level::CreateObjects()
{
	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
	for(auto node_it : node.children())
	{
		D3DXVECTOR3 pos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
		D3DXQUATERNION rot = GetAttribueValue<D3DXQUATERNION>(node_it, _T("rot"));
		int id = GetAttribueValue<int>(node_it, _T("id"));
		if(id == 6)
		{
			CreatePortalEntrance(pos);
		}
		else if(id == 7)
		{
			CreatePortalExit(pos);
		}
		else if(id > 1 && id < 6)
		{
			auto pEntity = CreateGameEntity(id, pos);
			pEntity->Rotate(rot);
			AddGameEntity(pEntity);
		}
		else
		{
			auto pEntity = CreateColissionEntity(id, pos);
			pEntity->Rotate(rot);
			AddColissionEntity(pEntity);
		}
	}
}

void Level::CheckCurrentDepth()
{
	if(m_CurrentDepth < m_MinDepth)
	{
		m_CurrentDepth += m_HeigthDifference;
	}
	else if(m_CurrentDepth > m_MaxDepth)
	{
		m_CurrentDepth -= m_HeigthDifference;
	}
}

ColissionEntity * Level::CreateColissionEntity(UINT model_id, const D3DXVECTOR3 & pos)
{
	ColissionEntity * pEntity(nullptr);
	if(model_id == 1)
	{
		pEntity = new KeyObject();
	}
	else
	{
		auto & modelParameters = ParameterManager::GetInstance()->CreateOrGet(_T("Models"));
		tstring name = XMLConverter::ConvertToTString(model_id);
		//Create previewObject
		tstringstream strstr;
		strstr << _T("./Resources/Lemmings3D/models/") << modelParameters.GetChildParameter<tstring>(name, _T("MODEL"));
		tstring model_path = strstr.str();
		strstr.str(_T(""));
		strstr << _T("./Resources/Lemmings3D/textures/") << modelParameters.GetChildParameter<tstring>(name, _T("TEXTURE"));
		tstring texture_path = strstr.str();
		strstr.str(_T(""));
		strstr << _T("./Resources/Lemmings3D/models/") << modelParameters.GetChildParameter<tstring>(name, _T("CONVEX"));


		auto material = new BaseModelMaterial();
		material->SetDiffuse(texture_path);
		material->SetAlpha(1.0f);

		pEntity = new ColissionEntity(model_path, material);
		pEntity->AddMeshCollider(strstr.str(), true, false);
	}
	
	m_pGame->AddSceneObject(pEntity);
	pEntity->SetIsStatic(true);
	pEntity->Initialize();

	pEntity->Translate(pos);

	return pEntity;
}

GameEntity * Level::CreateGameEntity(UINT model_id, const D3DXVECTOR3 & pos)
{
	GameEntity * pEntity(nullptr);
	if(model_id > 1 && model_id < 6)
	{
		pEntity = new Decal(model_id - 2);
	}
	if(pEntity != nullptr)
	{
		m_pGame->AddSceneObject(pEntity);
		pEntity->Initialize();
		pEntity->Translate(pos);
	}
	return pEntity;
}

bool Level::AddColissionEntity(ColissionEntity * pEntity)
{
	auto it = std::find(m_ColissionEntities.begin(), m_ColissionEntities.end(), pEntity);
	if(it == m_ColissionEntities.end())
	{
		m_ColissionEntities.push_back(pEntity);
		return true;
	}
	return false;
}

bool Level::AddGameEntity(GameEntity * pEntity)
{
	auto it = std::find(m_GameEntities.begin(), m_GameEntities.end(), pEntity);
	if(it == m_GameEntities.end())
	{
		m_GameEntities.push_back(pEntity);
		return true;
	}
	return false;
}


bool Level::AddColissionEntity(UINT model_id, const D3DXVECTOR3 & pos)
{
	ColissionEntity *pEntity = CreateColissionEntity(model_id, pos);

	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
	pugi::xml_node newNode = node.append_child("object");
	AddAttribute(newNode, _T("id"), model_id, true);
	AddAttribute(newNode, _T("pos"), pEntity->GetTranslation(), true);
	AddAttribute(newNode, _T("rot"), pEntity->GetRotation(), true);

	return AddColissionEntity(pEntity);
}

bool Level::AddGameEntity(UINT model_id, const D3DXVECTOR3 & pos)
{
	GameEntity *pEntity = CreateGameEntity(model_id, pos);

	auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
	pugi::xml_node newNode = node.append_child("object");
	AddAttribute(newNode, _T("id"), model_id, true);
	AddAttribute(newNode, _T("pos"), pEntity->GetTranslation(), true);
	AddAttribute(newNode, _T("rot"), pEntity->GetRotation(), true);

	return AddGameEntity(pEntity);
}
	

bool Level::RemoveColissionEntity(ColissionEntity * pEntity)
{
	auto it = std::find(m_ColissionEntities.begin(), m_ColissionEntities.end(), pEntity);
	if(it != m_ColissionEntities.end())
	{
		m_ColissionEntities.erase(it);
		bool removedXML(false);
		auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
		for(auto node_it : node.children())
		{
			D3DXVECTOR3 testPos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
			if(testPos == pEntity->GetTranslation())
			{
				node.remove_child(node_it);
				removedXML = true;
			}
		}
		return removedXML;
	}
	return false;
}

bool Level::RemoveColissionEntity(const D3DXVECTOR3 & pos)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	ColissionEntity * pTarget(nullptr);
	auto it = std::find_if(m_ColissionEntities.begin(), m_ColissionEntities.end(), [&] (ColissionEntity * pEntity) 
	{
		D3DXVECTOR3 vec = pEntity->GetTranslation() - pos;
		float length(D3DXVec3Length(&vec));
		bool result(length<size);
		if(length < size)
		{
			pTarget = pEntity;
			return true;
		}
		return false;
	});
	if(it != m_ColissionEntities.end())
	{
		m_ColissionEntities.erase(it);
		bool removedXML(false);
		auto node = m_pLevelParser->GetNode(XML_PARSER_LAYER(LayerTestCategory::xml_test_node, _T("objects")));
		for(auto node_it : node.children())
		{
			D3DXVECTOR3 testPos = GetAttribueValue<D3DXVECTOR3>(node_it, _T("pos"));
			D3DXVECTOR3 vec = pos - testPos;
			float length(D3DXVec3Length(&vec));
			if(length < size)
			{
				node.remove_child(node_it);
				removedXML = true;
			}
		}
		return removedXML;
	}
	return false;
}

void Level::ClearColissionEntities()
{
	//todo : shouldn't we clear this
	m_ColissionEntities.clear();
}

bool Level::IsLegalToBuild(const D3DXVECTOR3 & pos)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	auto it = std::find_if(m_ColissionEntities.begin(), m_ColissionEntities.end(), [&] (ColissionEntity * pEntity) 
	{
		D3DXVECTOR3 vec = pEntity->GetTranslation() - pos;
		float length(D3DXVec3Length(&vec));
		bool result(length<size);
		return length < size;
	});
	return it == m_ColissionEntities.end();
}

void Level::EnterEditor()
{
	/*for(auto it : m_ColissionEntities)
	{
		it->Disable();
	}*/
}

void Level::LeaveEditor()
{
	/*for(auto it : m_ColissionEntities)
	{
		it->Disable();
	}*/
}