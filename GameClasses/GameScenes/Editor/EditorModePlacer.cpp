//====================== #INCLUDES ===================================
#include "EditorModePlacer.h"
//--------------------------------------------------------------------
#include "../GameScreen.h"
#include "Overlordcomponents.h"
#include "../../Entities/EditorBuilder.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../GameScenes/EditModeScreen.h"
#include "../../Lib/GlobalParameters.h"
#include "../../Lib/LemmingsHelpers.h"
#include "../../Managers/ScreenManager.h"
#include "../../Managers/ParameterManager.h"
#include "../../UserInterface/UIDockInterface.h"
#include "../../Materials/BaseModelMaterial.h"
//====================================================================

EditorModePlacer::EditorModePlacer (EditorBuilder * pEditor)
	: IEditMode(pEditor)
	, m_CurrentModelID(0)
	, m_ModelsCount(0)
	, m_PreviewObjects()
{
	m_pModelMenu = new UIDockInterface(0,0,500,500,nullptr,nullptr);
	m_pModelMenu->AddImage(0, 0, _T("BACKGROUND"), _T("BG_EditorSubMenu.png"));

	int x(0), width(50);
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	
	auto & modelParameters = ParameterManager::GetInstance()->CreateOrGet(_T("Models"));
	m_ModelsCount = modelParameters.GetParameter<UINT>(_T("COUNT")); 

	for ( UINT i = 0 ; i < m_ModelsCount ; ++i )
	{
		tstring name = XMLConverter::ConvertToTString(i);
		
		//Create button
		m_pModelMenu->AddButton(x,65,name, modelParameters.GetParameter<tstring>(name), [&] () 
		{ 
			m_pModelMenu->ToggleElement(name);
			m_CurrentModelID = i;
		}, false, true);
		x += width;

		//Create previewObject
		tstringstream strstr;
		strstr << _T("./Resources/Lemmings3D/models/") << modelParameters.GetChildParameter<tstring>(name, _T("MODEL"));
		tstring model_path = strstr.str();
		strstr.str(_T(""));
		strstr << _T("./Resources/Lemmings3D/textures/") << modelParameters.GetChildParameter<tstring>(name, _T("TEXTURE"));

		auto material = new BaseModelMaterial();
		material->SetDiffuse(strstr.str());
		material->SetAlpha(1.0f);

		GameEntity * pEntity = new GameEntity(model_path, material);
		pEntity->Initialize();
		m_PreviewObjects.push_back(pEntity);
	}

	m_pModelMenu->Initialize();
}

EditorModePlacer::~EditorModePlacer()
{
	delete m_pModelMenu;
	for( UINT i = 0 ; i < m_PreviewObjects.size() ; ++i )
	{
		SafeDelete(m_PreviewObjects[i]);
	}
	m_PreviewObjects.clear();
}

void EditorModePlacer::Update(const GameContext & context)
{
	m_pModelMenu->Update(context);
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	D3DXVECTOR3 pos = m_pEditor->m_Position;
	pos.y += size / 2.0f;
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED))
	{
		m_pEditor->GetEditScreen()->GetCurrentLevel()->AddColissionEntity(m_CurrentModelID, pos);
	}
	m_PreviewObjects[m_CurrentModelID]->GetComponent<TransformComponent>()->Translate(pos);
	m_PreviewObjects[m_CurrentModelID]->Update(context);
}

void EditorModePlacer::Draw(const GameContext & context)
{
	m_PreviewObjects[m_CurrentModelID]->Draw(context);
}

void EditorModePlacer::DrawMenu(const GameContext & context)
{
	m_pModelMenu->Draw(context);
}