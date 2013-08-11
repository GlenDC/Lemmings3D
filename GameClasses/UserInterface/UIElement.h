#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "Graphics/SpriteBatch.h"
#include "../Helpers/Rectangle.h"
#include <vector>
#include <functional>
#include <memory>
//====================================================================

class UIDockInterface;

//====================== UIElement Class ============================
// Description:
//		An element which will be placed inside a zone of the userinterface.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class UIElement
{
public:
	enum class ElementStates : unsigned char
	{
		IDLE = 0,
		HOVER = 1,
		CLICK = 2,
		TOGGLE = 3,
		DISABLED = 4
	};
	virtual ~UIElement(); //default destructor

	// return true when the element can toggle AND the state is toggled
	bool IsToggledOn() const { return m_CanToggle && m_State == ElementStates::TOGGLE; }
	// returns true if the state is disabled
	bool IsDisabled() const { return m_State == ElementStates::DISABLED; }
	float GetAlphaValue() const { return m_AlphaValue; }

	virtual void Initialize();
	virtual void Draw(const GameContext &context) const;
	virtual void Update(const GameContext &context);

	virtual void Translate(const D3DXVECTOR2 & translation){}

	//toggle between online and offline
	virtual float ToggleOffline() { m_IsOffline = !m_IsOffline; return 0; }

	//set elemant visible or invisible
	void SetVisible(bool visible) { m_IsVisible = visible; }
	//set element disabled / enabled
	virtual void SetDisabled(bool disabled) 
		{ m_State = disabled ? ElementStates::DISABLED : ElementStates::IDLE; }
	//toggle on an element;
	void SetToggleOn(bool toggledOn) { m_State = toggledOn && m_CanToggle ?
		ElementStates::TOGGLE : ElementStates::IDLE; }
	//excectue the select function if its not equal to null
	virtual void Select() { if(m_SelectFunction != nullptr) m_SelectFunction(); }
	//Set alpha vale of element
	void SetAlphaValue(float alphaValue) { m_AlphaValue = alphaValue; }
	//set the Select Function
	void SetSelectFunction(function<void()> select_function) { m_SelectFunction = select_function; }
	//set the Hover Function
	void SetHoverFunction(function<void()> hover_function) { m_HoverFunction = hover_function; }
	//set the UnHover Function
	void SetUnHoverFunction(function<void()> unhover_function) { m_UnHoverFunction = unhover_function; }
	//set position
	void SetPosition(UINT x, UINT y);
	void SetPosition(const D3DXVECTOR2 & pos);
	//set dimensions
	void SetDimensions(UINT width, UINT height);

protected:
	UIElement(const int x, const int y, const int width, const int height, const tstring & name, const UIDockInterface * pParrent);
	// rectangle getter to parse the real position and dimensions of the element 
	// taking scaling based on the screenresoltuion into account
	LemmingsHelpers::Rect GetRealElementZone() const;
	// rectangle getter to parse the real position and dimensions of the element 
	// taking scaling based on the screenresoltuion into account and 
	// adding the parents position to its position
	LemmingsHelpers::Rect GetScreenZone() const;
	// initial dimensions and position of the element
	LemmingsHelpers::Rect m_ElementZone;
	// name of the element
	tstring m_Name;
	// variable containing the state of the element
	ElementStates m_State;
	// select function to be called when calling the element
	function<void()> m_SelectFunction;
    // hover function to be called when hovering the element
    function<void()> m_HoverFunction;
    // unhover function be called when unhovering the element
    function<void()> m_UnHoverFunction;
	// returns true if the element can toggle
	bool m_CanToggle;
	// returns true if the element is offline
	bool m_IsOffline;
	// returns true when the element is hovered
	bool m_IsHovered;
	// if true, the element is visible and will be drawn
	bool m_IsVisible;
	// docktinerface where the element is added to
	const UIDockInterface * m_pParrentDock;
	// alpha value of element
	float m_AlphaValue;

	static const int MAX_ELEMENT_STATES;

	friend class UIDockInterface;

private:
	UIElement(const UIElement& yRef);									
	UIElement& operator=(const UIElement& yRef);
};