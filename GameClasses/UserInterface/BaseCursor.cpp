//====================== #INCLUDES ===================================
#include "BaseCursor.h"
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Managers/ContentManager.h"
//--------------------------------------------------------------------
#include "../Lib/Debug.h"
#include "../Lib/GlobalParameters.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
//====================================================================

BaseCursor::BaseCursor() // Default constructor
	:m_Position(0,0)
	,m_OldCursorPosition(0,0)
	,m_CursorState(CursorStates::cursor_normal)
	,m_MouseSpeed(1.0f)
	,m_MouseCursorBorderScreen(1)
	,m_LeftClicked(false)
{
	//nothing to create
}

BaseCursor::~BaseCursor() // Default destructor
{
}

void BaseCursor::Initialize()
{
	ShowCursor(false);

	m_Position = GraphicsDevice::GetInstance()->GetWindowDimensions() / 2.0f;
    //To Do: Set the window carrot to m_Position @ Screen
    m_OldCursorPosition = m_Position;
    //Load global parameters and save in variables ( performance reasons )
	m_MouseSpeed = GlobalParameters::GetParameters()->GetParameter<float>(_T("CURSOR_SPEED"));
	m_MouseCursorBorderScreen = GlobalParameters::GetParameters()->GetParameter<int>(_T("CURSOR_SCROLL_BORDER"));

	//ToDo: Create/Load MouseCursor
	m_NormalTexture.pTexture = ContentManager::Load<ID3D10ShaderResourceView>(GlobalParameters::GetParameters()->GetParameter<tstring>(_T("UI_DIRECTORY")) + _T("LemmingsCursor.png"));
	m_NormalTexture.Color = D3DXCOLOR(1,1,1,1);
	m_NormalTexture.UVY = 0.25f;
}

void BaseCursor::Update(const GameContext & context)
{
	m_LeftClicked = false;
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_LEFT_PRESSED))
	{
		m_LeftClicked = true;
	}
	else if(context.Input->IsActionTriggered((int)InputControls::MOUSE_LEFT_DOWN))
	{
		m_NormalTexture.OffsetY = 0.25f;
	}
	else if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_DOWN))
	{
		m_NormalTexture.OffsetY = 0.50f;
	}
	else
	{
		m_NormalTexture.OffsetY = 0;
	}

	D3DXVECTOR2 cursorPosition((float)context.Input->GetMousePosition().x, (float)context.Input->GetMousePosition().y);
    if (m_OldCursorPosition != cursorPosition)
    {
		SetPosition(m_Position);
		/*int differenceX = (int)GraphicsDevice::GetInstance()->GetWindowDimensions().x - (m_MouseCursorBorderScreen * 2);
        int differenceY = (int)GraphicsDevice::GetInstance()->GetWindowDimensions().y - (m_MouseCursorBorderScreen * 2);
        if ((float)abs(m_OldCursorPosition.x - cursorPosition.x) > GraphicsDevice::GetInstance()->GetWindowDimensions().x / 2)
		{
            m_OldCursorPosition.x = cursorPosition.x;
		}
        else if (cursorPosition.x < m_MouseCursorBorderScreen)
        {
			
			SetCursorPos((int)cursorPosition.x + differenceX - 10, (int)cursorPosition.y);
        }
        else if (cursorPosition.x > (int)GraphicsDevice::GetInstance()->GetWindowDimensions().x - m_MouseCursorBorderScreen)
        {
			SetCursorPos((int)cursorPosition.x - differenceX + 10, (int)cursorPosition.y);
        }
        if ((float)abs(m_OldCursorPosition.y - cursorPosition.y) > GraphicsDevice::GetInstance()->GetWindowDimensions().y / 3)
            m_OldCursorPosition.y = cursorPosition.y;
        else if (cursorPosition.y < m_MouseCursorBorderScreen)
        {
            SetCursorPos((int)cursorPosition.x, (int)cursorPosition.y + differenceY - 10);
        }
        else if (cursorPosition.y > GraphicsDevice::GetInstance()->GetWindowDimensions().y - m_MouseCursorBorderScreen)
        {
            SetCursorPos((int)cursorPosition.x, (int)cursorPosition.y - differenceY + 10);
        }*/

        /*m_Position -= m_OldCursorPosition - cursorPosition;*/

		m_Position = D3DXVECTOR2((float)context.Input->GetMousePosition().x - 22.5f, (float)context.Input->GetMousePosition().y - 22.5f);
        m_OldCursorPosition = cursorPosition;
        m_MouseSpeed = GlobalParameters::GetParameters()->GetParameter<float>(_T("CURSOR_SPEED"));
    }
    else
    {
		m_MouseSpeed *=GlobalParameters::GetParameters()->GetParameter<float>(_T("MOUSE_SPEED_ACCELERATION"));
		D3DXVECTOR2 movement = context.Input->GetThumbstickPosition();
        movement.y *= -1;
		movement *= (float)context.GameTime.ElapsedSeconds()/100 * m_MouseSpeed;
        m_Position += movement;
    }
	m_Position.x = Clamp<float>(m_Position.x, -22.5f, GraphicsDevice::GetInstance()->GetWindowDimensions().x - 22.5f);
	m_Position.y = Clamp<float>(m_Position.y, -22.5f, GraphicsDevice::GetInstance()->GetWindowDimensions().y - 22.5f);

	//m_NormalTexture.OffsetX = (m_Position.x/1280.0f) * -40.0f;
	//m_NormalTexture.OffsetY = (m_Position.y/720.0f) * -20.0f;
	//Debug::Output(_T("MousePosition"), m_Position, true);
}

void BaseCursor::Draw(const GameContext & context)
{
    //To Do draw texture
	SpriteBatch::Draw(m_NormalTexture);
}


void BaseCursor::SetState(const CursorStates state)
{
    m_CursorState = state;
}

void BaseCursor::SetPosition(const D3DXVECTOR2 & pos)
{
	D3DXMATRIX mouseTranslation, mouseScale;
	D3DXMatrixTranslation(&mouseTranslation, pos.x, pos.y, 0.005f);
	D3DXMatrixScaling(&mouseScale, 1.0f, 0.25f, 1.0f);
	m_NormalTexture.Transform = mouseScale * mouseTranslation;
}