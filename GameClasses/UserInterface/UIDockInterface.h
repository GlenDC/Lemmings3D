#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Helpers/SpriteFont.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "Graphics/SpriteBatch.h"
#include "../Helpers/Rectangle.h"
#include <vector>
#include <functional>
#include "UIElement.h"

#include <memory>
//====================================================================

class AmountButton;
class UIButton;
class UILevelButton;
class UIToggleButton;
class UIButtonWT;
class UITextField;
class UISlider;
class UIControllerSlider;
class UICounter;
class UISpritesheet;

//====================== UIDockInterface Class ============================
// Description:
//		This is a part of the userinterface. Elements are collected within
//		this interface. Their position is relative to this dock, their
//		scale is relative to the screen scale and the target resolution.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

	//delegate function that returns scalar value via the parameter
    //public delegate void ScalarDelegate(float scalar);

class UIDockInterface
{
public:
    // constructor creating the element list, the pos and dimension 
    // rectangle and setting the variables to a initialization value.
	UIDockInterface(const int x, const int y, const int width, const int height, 
		shared_ptr<SpriteFont> pDefaultFont,  const UIDockInterface * pParrent = nullptr);

	~UIDockInterface();
	
    // initialize all elements
    // load the content of all the elements in this dockinterface
	void Initialize();
    // draw all the elements in the ui dockinterface
	void Draw(const GameContext &context);
    // update all the elements in the uidockinterface
    // and calculate the new scaling value based on 
    // the current screensize and the target screen size
	void Update(const GameContext &context);
    // calculate the new scaling value based on the current screenscale
    // and the target screensize.
    void UpdateDimensions(const GameContext &context);

    // remove an element in the element list 
    // of this ui dock using it's name
    void RemoveElement(const tstring & name);

    // Create a button which is controllable via a carrot 
	UIButton * AddButton(int x, int y, const tstring & name, const tstring & asset_file,
            function<void()> select_function, bool disabled = false, bool toggle_on = false);
    // Create a toggle button. e.g: on/off, checkbox, ...
    UIToggleButton * AddToggleButton(int x, int y, const tstring & name, const tstring & asset_file,
                                    function<void()> select_function, bool disabled = false, bool toggle_on = false,
                                    bool is_on = true);
    // Create a button with a textfield on top of it (child class of a normal button)
	UIButtonWT * AddButtonWT(int x, int y, const tstring & name, const tstring & asset_file, UINT textX, UINT textY, const tstring & text,
		const D3DXCOLOR & text_normal, const D3DXCOLOR & text_hover, const D3DXCOLOR & text_click, shared_ptr<SpriteFont> pFont, function<void()> select_function, 
		bool disabled = false, bool toggle_on = false);
    // Create a button to start the game (level). 
	UILevelButton * AddButtonLevel(const int x, const int y, const tstring & name,
		const tstring & level_name, const tstring & button_image, const UINT level_id, const UINT highscore, const UINT best_time, function<void()> select_function, bool disabled);
    // Create an Amount Buttons
	AmountButton * AddAmountButton(int x, int y, const tstring & name, const tstring & asset_file, int amount, shared_ptr<SpriteFont> pFont, function<void()> select_function, 
		bool disabled = false, bool toggle_on = false);
    // Create an Amount Buttons with default font
	AmountButton * AddAmountButton(int x, int y, const tstring & name, const tstring & asset_file, int amount, function<void()> select_function, 
		bool disabled = false, bool toggle_on = false);
    // Create a dropdown menu with a fixed amount of elements
   /* void AddDropDown(int x, int y, tstring name, tstring asset_file, function<void(int)> select_function, int elements,
                                float control_delay, int selected_element = 0, bool disabled = false, bool toggle_on = false);*/
    // Create a textfield with default font
    void AddTextField(int x, int y, int width, int height, const tstring & name,
                            const tstring & text, const D3DXCOLOR & text_color);
    // Create a textfield
    void AddTextField(int x, int y, int width, int height, const tstring & name,
                            const tstring & text, const D3DXCOLOR & text_color, shared_ptr<SpriteFont> pFont);
    // Create an image
    void AddImage(int x, int y, const tstring & name, const tstring & asset_file);
    // Create a spritesheet
    void AddSpritesheet(int x, int y, const tstring & name, const tstring & asset_file, UINT frames_x, UINT frames_y, float animation_speed);
    // Slider for menu's that work with a mouse.
   /* void AddSlider(int x, int y, tstring name, tstring asset_background, tstring asset_carrot, int min_carrot,
                            int max_carrot, int carrot_height_cor, SlideModes slide_mode, function<void(float)> function, bool disabled = false);*/
    // Slider for menu's that work with keyboard / controller
    /*void AddControllerSlider(int x, int y, tstring name, tstring asset_background, tstring asset_carrot, int min_carrot,
                            int max_carrot, int carrot_height_cor, UISlider.SlideModes slide_mode, ScalarDelegate function,
                            float movement_scale_incrementation, float control_delay, float start_value, bool disabled = false);*/
    // Add a counter (that represents a number via a fixed ammount of numbers)
    //UICounter * AddCounter(tstring assetFile, int x, int y, tstring name, UIDockInterface parrent, int numbersToShow);

	LemmingsHelpers::Rect GetRealElementZone() const;
	LemmingsHelpers::Rect GetElementZone() const;
    
    // Set the position of the ui dock inteface after creating the dock.
	void SetPosition(int x, int y);
	void SetPosition(const D3DXVECTOR2 & position);
    // set the horizontal user input either occupied or free it.
	void SetHorizontalOccupied(bool occupied) { m_HorizontalOccupied = occupied; }
    // set the vertical user input either occupied or free it.
	void SetVerticalOccupied(bool occupied) { m_VerticalOccupied = occupied; }
    // Change the text of a textfield via its name
    void SetTextField(const tstring & name, const tstring & text);
    // Change the text of a button's textfield (UIButtonWT)
    void SetButtonTextField(const tstring & name, const tstring & text);
    // Manualy set the position of a carrot of the slider
    void SetControllerSlider(const tstring & name, float scalar);
    // either hide an element or show it
    void SetElementVisible(const tstring & name, bool visible);
    // disable/enable an element
    void SetElementDisabled(const tstring & name, bool disabled);
    // Check if a cursor is in the zone of the dockinterface
	bool CursorInZone(int cursorX, int cursorY);
	bool CursorInZone(const D3DXVECTOR2 & cursorPos);
    // toggle an element. 
    void ToggleElement(const tstring & name);
    // select an element. (== execute it's select function, if it's not null)
    void SelectElement(const tstring & name);
    // Select the first element in the list.
    bool SelectFirstElement();
    // Set a slider off, so that it's at 0 and its carrot can't be moved anymore
    float ToggleSlider(const tstring & slider_name);
    // Set all elements disabled.
    void DisableAllElements();
    // Set all elements enabled.
    void EnableAllElements();
    // Set the parrent uidockinterface of this dockinterface
    void SetParrent(const UIDockInterface * pParrent);
	// Set Visible dock
	void SetVisible(bool visible) { m_Visible = visible; }

	bool IsInitialized() const { return m_IsInitialized; }

	shared_ptr<SpriteFont> GetDefaultFont() const { return m_pDefaultFont; }

protected:
    // list of elements. It contains all the elements in this UI part
    map<UINT,UIElement*> m_ElementList;
    // Complete zone, used for point in rectangle test (3d -> 2d -> 3d)
    LemmingsHelpers::Rect m_ElementZone;
    // the target screensize (2D dimensions)
    // where the UI content is for designed. 
    // e.g.: if its designed for 1920x1080 and the screensize
    //       is 1280x720 than the UI elements will be scaled down.
	D3DXVECTOR2 m_TargetScreenSize;
    // Scalar value for both the x and y direction that will be 
    // used in every element to scale them and place them
    // at the correct relative screenpsoitions.
    D3DXVECTOR2 m_ScreenScale;
    // If it's true, than you should not take Movement().x 
    // into account, because this action is probably needed
    // in some element. Double booking is BAD!
    // <remarks> How can we make this automatic?! </remarks>
    bool m_HorizontalOccupied;
    // If it's true, than you should not take Movement().y 
    // into account, because this action is probably needed
    // in some element. Double booking is BAD!
    // <remarks> How can we make this automatic?! </remarks>
    bool m_VerticalOccupied;
	//is true if 'the UI dock is initialized
	bool m_IsInitialized;
    // As a dockinterface can also be a child from another
    // Dockinterface, here this wil lbe taken into account.
	const UIDockInterface * m_pParrent;
    // Font to be used for this dockInterface
	shared_ptr<SpriteFont> m_pDefaultFont;
	//if false, compleet dock doesnt get drawn!
	bool m_Visible;

	void ConvertToResourcePath(tstring & file);

	friend class UIElement;
	friend class UIButtonWT;
	friend class AmountButton;
};