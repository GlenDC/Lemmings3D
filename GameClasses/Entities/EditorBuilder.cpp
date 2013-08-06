//====================== #INCLUDES ===================================
#include "EditorBuilder.h"
//--------------------------------------------------------------------
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
//--------------------------------------------------------------------
#include "../GameObjects/PreviewObject.h"
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Managers/ScreenManager.h"
#include "../GameScenes/GameScreen.h"
#include "../UserInterface/UIDockInterface.h"
#include "../Interfaces/IEditMode.h"
#include "../GameScenes/Editor/EditorModeBuilder.h"
#include "../GameScenes/Editor/EditorModeEraser.h"
#include "../GameScenes/Editor/EditorModePainter.h"
//====================================================================

EditorBuilder::EditorBuilder(GameScreen * pScreen)
	: m_pPreviewObject(nullptr)
	, m_Position(0,0,0)
	, m_pGame(pScreen)
	, m_pMainMenu(nullptr)
	, m_EditorMode(EditorMode::build)
{
	m_pPreviewObject = new PreviewObject();
	m_pPreviewObject->Initialize();

	m_pMainMenu = new UIDockInterface(45,0,400,200, nullptr, nullptr);
	m_pMainMenu->AddButton(0,5,_T("Abtn_Mode_Builder"), _T("Header_Editor_Square_Hammer.png"), [&] () 
	{ 
		m_pMainMenu->ToggleElement(_T("Abtn_Mode_Builder"));
		m_EditorMode = EditorMode::build;
	}, false, true);
	m_pMainMenu->AddButton(50,5,_T("Abtn_Mode_Eraser"), _T("Header_Editor_Square_Erase.png"), [&] () 
	{ 
		m_pMainMenu->ToggleElement(_T("Abtn_Mode_Eraser"));
		m_EditorMode = EditorMode::erase;
	}, false, false);
	m_pMainMenu->AddButton(100,5,_T("Abtn_Mode_Painter"), _T("Header_Editor_Square_Painter.png"), [&] () 
	{ 
		m_pMainMenu->ToggleElement(_T("Abtn_Mode_Painter"));
		m_EditorMode = EditorMode::paint;
	}, false, false);
	m_pMainMenu->Initialize();

	m_pModeArr[0] = new EditorModeBuilder(this);
	m_pModeArr[1] = new EditorModeEraser(this);
	m_pModeArr[2] = new EditorModePainter(this);
}

EditorBuilder::~EditorBuilder(void)
{
	delete m_pPreviewObject;
	delete m_pMainMenu;
}

void EditorBuilder::Draw(const GameContext & context)
{
	m_pPreviewObject->Draw(context);
	m_pMainMenu->Draw(context);
	m_pModeArr[(UINT)m_EditorMode]->Draw(context);
}

void EditorBuilder::DrawSubMenu(const GameContext & context)
{
	m_pModeArr[(UINT)m_EditorMode]->DrawMenu(context);
}

void EditorBuilder::Update(const GameContext & context)
{
	m_pPreviewObject->Update(context);
	m_pMainMenu->Update(context);
	m_pModeArr[(UINT)m_EditorMode]->Update(context);
}

void EditorBuilder::SetSnapPosition(const GameContext & context, const D3DXVECTOR3 & pos)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	D3DXVECTOR3 camDir = context.Camera->GetTransform()->GetWorldPosition() - pos;
	D3DXVec3Normalize(&camDir, &camDir);
	D3DXVECTOR3 snapPosition = pos + camDir * size;
	LemmingsHelpers::SnapPositionXYZ(snapPosition, size);
	m_Position = snapPosition;
	m_pPreviewObject->SetPosition(snapPosition);
}

void EditorBuilder::CalculatePositionFromEnvironment(const GameContext & context, const std::vector<D3DXVECTOR3> & posVec
	 ,UINT length, const int accurary, const UINT extraDistance, const float distanceScalar)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	D3DXVECTOR3 worldPos;
	D3DXVECTOR3 mouseDir = LemmingsHelpers::GetMouseWorldDirection(context, &worldPos);
	length += extraDistance;
	length = (UINT)(length * distanceScalar);
	float diameter = accurary * size;
	float radius = diameter * 0.5f;
	float curDistance = diameter;

	float minDistance = 99999;
	D3DXVECTOR3 snapPos(0,0,0);
	float prevDistance(0);
	do
	{
		D3DXVECTOR3 pos = worldPos + mouseDir * curDistance;
		for(UINT i = 0 ; i < posVec.size() ; ++i)
		{
			float checkLength = LemmingsHelpers::CalculateVector3Length(pos, posVec[i]);
			if(checkLength < radius)
			{
				if(checkLength < minDistance) 
				{
					prevDistance = curDistance - diameter;
					minDistance = checkLength;
					snapPos = posVec[i];
					/*if(minDistance > size * 3)
					{
						curDistance += diameter * (minDistance/size);
					}*/
				}
			}
		}
		curDistance += diameter;
	} while(curDistance < length);
	//LemmingsHelpers::SnapPositionXYZ(snapPos, size);
	//============ Get pos
	LemmingsHelpers::SnapPositionXYZ(snapPos, size);
	//snap to empty block space closest to camera and based on mouse position
	// to do: improve the algorithm!
	if(m_EditorMode == EditorMode::build)
	{
		D3DXVECTOR3 originalSnapPos = snapPos;
		D3DXVECTOR3 checkSnapPos = worldPos + mouseDir * prevDistance;
		snapPos += LemmingsHelpers::GetCubeClosestPlane(snapPos, size * 0.5f, checkSnapPos) * 2;
		LemmingsHelpers::SnapPositionXYZ(snapPos, size);
		if(snapPos == originalSnapPos)
		{
			D3DXVECTOR3 worldDir = worldPos - snapPos;
			D3DXVec3Normalize(&worldDir, &worldDir);
			snapPos += size * worldDir;
			LemmingsHelpers::SnapPositionXYZ(snapPos, size);
		}
	}
	//==================================
	m_Position = snapPos;
	m_pPreviewObject->SetPosition(snapPos);
}
	/*m_SearchVec.clear();
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	D3DXVECTOR3 worldPos;
	D3DXVECTOR3 mouseDir = LemmingsHelpers::GetMouseWorldDirection(context, &worldPos);
	length += extraDistance;
	length = (UINT)(length * distanceScalar);
	float diameter = accurary * size;
	float radius = diameter * 0.5f;
	float curDistance = diameter;
	std::vector<UINT> tempVec;
	do
	{
		D3DXVECTOR3 pos = worldPos + mouseDir * curDistance;
		for(UINT i = 0 ; i < posVec.size() ; ++i)
		{
			if(LemmingsHelpers::CalculateVector3Length(pos, posVec[i]) < radius)
			{
				tempVec.push_back(i);
				m_SearchVec.push_back(posVec[i]);
			}
		}
		for(UINT i = 0 ; i < tempVec.size() ; ++i)
		{
			posVec.erase(posVec.begin() + tempVec[i]);
		}
		tempVec.clear();
		curDistance += diameter;
	} while(curDistance < length && posVec.size() > 0);*/
//}