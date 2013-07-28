#include "ScreenManager.h"
#include "Helpers/DebugRenderer.h"
#include "Game.h"
#include <algorithm>
#include "../UserInterface/BaseCursor.h"
#include "../Lib/GlobalParameters.h"
#include "ColissionCollector.h"

ScreenManager* ScreenManager::m_pInstance = nullptr;

ScreenManager::ScreenManager(void)
	: m_MainGame(nullptr),
	m_pControlScreen(nullptr),
	m_IsInitialized(false),
	m_Simulated(false),
	m_Fetched(false),
	m_PhysicsDisabled(false),
	m_EnablePhysicsRendering(true),
	m_pDefaultCursor(nullptr),
	m_pCurrentCursor(nullptr)
{
	m_pInputManager = new InputManager();
}

ScreenManager::~ScreenManager(void)
{
	for(UINT i = 0 ; i < m_Screens.size() ; ++i)
	{
		SafeDelete(m_Screens[i]);
		m_Screens[i] = nullptr;
	}
	m_Screens.clear();
	m_ActiveScreens.clear();
	/*m_sPhysicsDebugScreens.clear();*/
	m_pControlScreen = nullptr;
	SafeDelete(m_pInputManager);
}

void ScreenManager::AddScreen(BaseScreen* screen)
{
	// Check if the scene is not already in the vector
	if(find(m_Screens.begin(), m_Screens.end(), screen) == m_Screens.end()) {
		m_Screens.push_back(screen);

		if (m_IsInitialized && !screen->m_IsInitialized)
			screen->SceneInitialize();
	}
}

void ScreenManager::RemoveScreen(BaseScreen* screen)
{
	m_Screens.erase(find(m_Screens.begin(), m_Screens.end(), screen));
	delete screen;
}

bool ScreenManager::AddActiveScreen(wstring name)
{
	// Check if the scene is in our vector
	auto chosenScene = *find_if(m_Screens.begin(), m_Screens.end(), 
         [&name](BaseScreen* scene) { return scene->GetName() == name; });

    if (chosenScene != nullptr)
    {
		if(m_ActiveScreens.size() == 0)
			SetControlScreen(name);
		m_ActiveScreens.push_back(chosenScene);
    }

    return chosenScene != nullptr;
}

bool ScreenManager::RemoveActiveScreen(wstring name)
{
	bool removed = false;
	m_ActiveScreens.erase(std::remove_if(m_ActiveScreens.begin(), m_ActiveScreens.end(), 
		[&name, &removed](const BaseScreen* scene) { 
			 removed = true; 
			 return scene->GetName() == name; 
	}), m_ActiveScreens.end());
   return removed;
}

bool ScreenManager::SetControlScreen(wstring name)
{
	// Check if the scene is in our vector
	auto chosenScene = *find_if(m_Screens.begin(), m_Screens.end(), 
         [&name](BaseScreen* scene) { return scene->GetName() == name; });

    if (chosenScene != nullptr)
    {
		if(m_pControlScreen != nullptr)
			m_pControlScreen->Deactivated();
		m_pControlScreen = chosenScene;
		m_pControlScreen->Activated();
    }

    return chosenScene != nullptr;
}
//
//bool ScreenManager::AddPhysicsDebugScreen(wstring name)
//{
//	// Check if the scene is in our vector
//	auto chosenScene = *find_if(m_Screens.begin(), m_Screens.end(), 
//         [&name](BaseScreen* scene) { return scene->GetName() == name; });
//
//    if (chosenScene != nullptr)
//    {
//		m_sPhysicsDebugScreens.push_back(chosenScene);
//    }
//
//    return chosenScene != nullptr;
//}
//
//bool ScreenManager::RemovePhysicsDebugScreen(wstring name)
//{
//	bool removed = false;
//	BaseScreen * controlScreen = m_pControlScreen;
//	auto chosenScene = *find_if(m_sPhysicsDebugScreens.begin(), m_sPhysicsDebugScreens.end(), 
//         [&name, &removed](BaseScreen* scene) { 
//			 removed = true;
//			 return scene->GetName() == name; 
//	});
//
//   return removed;
//}
void ScreenManager::Initialize()
{
	for(BaseScreen* baseScreen : m_Screens)
	{
		if(baseScreen &&  !baseScreen->m_IsInitialized)
		{
			baseScreen->SceneInitialize();
		}
	}
	m_pInputManager->Initialize();
	m_IsInitialized = true;
}

void ScreenManager::InitializeContent()
{
	m_pDefaultCursor = new BaseCursor();
	m_pDefaultCursor->Initialize();
	m_pCurrentCursor = m_pDefaultCursor;
	
	m_pInputManager->AddInputAction(InputAction((int)InputControls::MOUSE_LEFT_PRESSED, Pressed, -1, VK_LBUTTON));
	m_pInputManager->AddInputAction(InputAction((int)InputControls::MOUSE_RIGHT_PRESSED, Pressed, -2, VK_RBUTTON));
	m_pInputManager->AddInputAction(InputAction((int)InputControls::MOUSE_LEFT_DOWN, Down, -1, VK_LBUTTON));
	m_pInputManager->AddInputAction(InputAction((int)InputControls::MOUSE_RIGHT_DOWN, Down, -2, VK_RBUTTON));

	m_pInputManager->AddInputAction(InputAction((int)InputControls::KB_ALT_DOWN, Down, VK_MENU));
	m_pInputManager->AddInputAction(InputAction((int)InputControls::KB_CTRL_DOWN, Down, VK_CONTROL));
	m_pInputManager->AddInputAction(InputAction((int)InputControls::KB_SHIFT_DOWN, Down, VK_SHIFT));

	/*for(UINT i = 0 ; i < m_Screens.size() ; ++i)
	{
		m_Screens[i]->m_pInputManager->AddInputAction(InputAction(0, Pressed, -1, VK_LBUTTON));
		m_Screens[i]->m_pInputManager->AddInputAction(InputAction(1, Pressed, -2, VK_RBUTTON));
		m_Screens[i]->m_pInputManager->AddInputAction(InputAction(2, Down, -1, VK_LBUTTON));
		m_Screens[i]->m_pInputManager->AddInputAction(InputAction(3, Down, -2, VK_RBUTTON));
	}*/
}

void ScreenManager::Update(GameContext& context)
{
	ColissionCollector::GetInstance()->RefreshCollection(context);

	if(m_pControlScreen != nullptr)
	{
		//TODO: FIX (dirty solution)
		context.Camera = m_pControlScreen->m_pActiveCamera;
		context.Input = m_pInputManager;
		context.Input->Update(context);
		m_pControlScreen->SceneUpdate(context);
		m_pCurrentCursor->Update(context);

		m_LMBP = m_pInputManager->IsActionTriggered((int)InputControls::MOUSE_LEFT_PRESSED);
		m_RMBP = m_pInputManager->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED);
		m_LMBD = m_pInputManager->IsActionTriggered((int)InputControls::MOUSE_LEFT_DOWN);
		m_RMBD = m_pInputManager->IsActionTriggered((int)InputControls::MOUSE_RIGHT_DOWN);
	}

	if(m_pControlScreen->IsPhysicsEnabled())
	{
		PhysicsManager::GetInstance()->Simulate(m_pControlScreen->GetPhysicsScene(), context.GameTime.ElapsedSeconds());
		m_Simulated = true;
		m_Fetched = false;
	}
}

void ScreenManager::Draw(GameContext& context)
{
	context.Window->GetGraphicsDevice()->Clear(D3DXCOLOR(0,0,0,1));
	if (m_ActiveScreens.size() > 0)
	{
		//TODO: FIX (dirty solution)
		context.Camera = m_ActiveScreens[0]->m_pActiveCamera;
		context.Input = m_pInputManager;
	}
	for(auto screen : m_ActiveScreens)
	{
		screen->SceneDraw(context);
	}

	if(m_pControlScreen->IsPhysicsEnabled())
	{
		PhysicsManager::GetInstance()->FetchResults(m_pControlScreen->GetPhysicsScene());

		if(m_EnablePhysicsRendering && !m_PhysicsDisabled)
		{
			//TODO: Create physics debug renderer.
			auto renderables = m_pControlScreen->GetPhysicsScene()->getDebugRenderable();
			auto lines = renderables->getLines();
	
			for(unsigned int i = 0; i < renderables->getNbLines(); ++i, lines++)
			{
				D3DXCOLOR color;
				color.a=1;
				color.r=((lines->color&0x00ff0000)>>16)/255.0f;
				color.g=((lines->color&0x0000ff00)>>8)/255.0f;
				color.b=((lines->color&0x000000ff)>>0)/255.0f;

				auto start = D3DXVECTOR3(lines->p0.x,lines->p0.y,lines->p0.z);
				auto end = D3DXVECTOR3(lines->p1.x,lines->p1.y,lines->p1.z);

				DebugRenderer::DrawLine(start,end,color);
			}
			}
		m_Simulated = false;
		m_Fetched = true;
	}

}

void ScreenManager::DrawCursor(const GameContext & context)
{
	m_pCurrentCursor->Draw(context);
}

D3DXVECTOR2 ScreenManager::GetCursorPosition() const
{
	return m_pCurrentCursor->GetCursorPosition();
	//return D3DXVECTOR2(0,0);
}

bool ScreenManager::LeftMouseButtonPressed() const
{
	return m_LMBP;
}

bool ScreenManager::RightMouseButtonPressed() const
{
	return m_RMBP;
}

bool ScreenManager::LeftMouseButtonDown() const
{
	return m_LMBD;
}

bool ScreenManager::RightMouseButtonDown() const
{
	return m_RMBD;
}

void ScreenManager::SetPhysicsDrawEnabled(bool enable)
{
	m_EnablePhysicsRendering = enable;
}