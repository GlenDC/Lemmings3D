#include "UIElement.h"
#include "UIDockInterface.h"
#include "../Lib/GlobalParameters.h"
#include "../Managers/ScreenManager.h"

const int UIElement::MAX_ELEMENT_STATES = 5;

UIElement::UIElement(const int x, const int y, const int width, const int height, const tstring & name, const UIDockInterface * pParrent)
	:m_ElementZone(x, y, width, height)
	,m_Name(name)
	,m_pParrentDock(pParrent)
	,m_SelectFunction(nullptr)
	,m_HoverFunction(nullptr)
	,m_UnHoverFunction(nullptr)
	,m_IsHovered(false)
	,m_IsVisible(true)
	,m_IsOffline(false)
	,m_CanToggle(true)
	,m_AlphaValue(1.0f)
{
	//nothing to create
}

UIElement::~UIElement()
{
	//nothing to destroy
}

void UIElement::Initialize()
{
	//nothing to initialize
}

void UIElement::Draw(const GameContext &context) const
{
	//nothing to draw
}

void UIElement::Update(const GameContext &context)
{
	//online calculate a new state if the element is not disabled
	if (!IsDisabled())
    {
        //if its hovered save it in a variable,
        // so that we can check for clicking
		LemmingsHelpers::Rect parentZone(m_pParrentDock->GetRealElementZone());
		LemmingsHelpers::Rect myZone(GetScreenZone());
		POINT mousePosition(context.Input->GetMousePosition());
        bool hoveredButton = myZone.X < mousePosition.x &&
                                myZone.X + myZone.Width * 1.5f > mousePosition.x &&
                                myZone.Y < mousePosition.y &&
                                myZone.Y + myZone.Height > mousePosition.y;
		bool clicked = ScreenManager::GetInstance()->LeftMouseButtonPressed();
		if (m_State != ElementStates::TOGGLE)
        {
			m_State = hoveredButton && clicked ? ElementStates::CLICK : hoveredButton ? ElementStates::HOVER : ElementStates::IDLE;
        }
		if (m_State == ElementStates::CLICK && m_SelectFunction != nullptr)
        {
			m_SelectFunction();
            //Future implemetantion Audio Manager click sound
            //Program.Game.Audio.SoundSFX2D.PlaySound("buttonClick", false, (int)GameSpace.AudioSFXChannels.ui_buttons);
        }

		if (m_HoverFunction != nullptr && hoveredButton && !m_IsHovered)
        {
			m_HoverFunction();
            //Future implemetantion Audio Manager hover sound
            //Program.Game.Audio.SoundSFX2D.PlaySound("buttonHover", false, (int)GameSpace.AudioSFXChannels.ui_buttons);
			m_IsHovered = true;
        }
		else if (m_IsHovered && m_State != ElementStates::TOGGLE && hoveredButton == false)
        {
			m_IsHovered = false;
			if (m_UnHoverFunction != nullptr)
            {
				m_UnHoverFunction();
            }
        }
    }
}

LemmingsHelpers::Rect UIElement::GetRealElementZone() const 
{
	return LemmingsHelpers::Rect(	
		(int)(m_ElementZone.X * m_pParrentDock->m_ScreenScale.x), 
		(int)(m_ElementZone.Y * m_pParrentDock->m_ScreenScale.y),
		(int)(m_pParrentDock->m_ScreenScale.x * m_ElementZone.Width),
		(int)m_pParrentDock->m_ScreenScale.y * m_ElementZone.Height
	);
}

LemmingsHelpers::Rect UIElement::GetScreenZone() const 
{
	LemmingsHelpers::Rect parentZone = m_pParrentDock->GetRealElementZone();
    return LemmingsHelpers::Rect(
		(int)(m_ElementZone.X * m_pParrentDock->m_ScreenScale.x + parentZone.X), 
		(int)(m_ElementZone.Y * m_pParrentDock->m_ScreenScale.y + parentZone.Y),
		(int)(m_pParrentDock->m_ScreenScale.x * m_ElementZone.Width),
		(int)(m_pParrentDock->m_ScreenScale.y * m_ElementZone.Height)
	);
}


void UIElement::SetPosition(UINT x, UINT y)
{
	m_ElementZone.X = x;
	m_ElementZone.Y = y;
}

void UIElement::SetPosition(const D3DXVECTOR2 & pos)
{
	SetPosition((UINT)pos.x, (UINT)pos.y);
}

void UIElement::SetDimensions(UINT width, UINT height)
{
	m_ElementZone.Width = width;
	m_ElementZone.Height = height;
}