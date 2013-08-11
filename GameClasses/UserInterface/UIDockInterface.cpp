//====================== #INCLUDES ===================================
#include "UIDockInterface.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
//--------------------------------------------------------------------
#include "UIButtonWT.h"
#include "UILevelButton.h"
#include "UIToggleButton.h"
#include "UIImage.h"
#include "UITextField.h"
#include "AmountButton.h"
//====================================================================

UIDockInterface::UIDockInterface(const int x, const int y, const int width, const int height, 
								 shared_ptr<SpriteFont> pDefaultFont, const UIDockInterface * pParrent)
	: m_ElementZone(x, y, width, height)
	, m_TargetScreenSize(1920, 1080)
	, m_ScreenScale(1,1)
	, m_HorizontalOccupied(false)
	, m_VerticalOccupied(false)
	, m_pParrent(pParrent)
	, m_pDefaultFont(pDefaultFont)
	, m_Visible(true)
	, m_IsInitialized(false)
{
}

UIDockInterface::~UIDockInterface()
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		delete element.second;
	}
	m_ElementList.clear();
}

void UIDockInterface::Initialize()
{
	if(m_ElementList.size() > 0)
	{
		for(std::pair<UINT, UIElement*> element : m_ElementList)
		{
			element.second->Initialize();
		}
		m_TargetScreenSize = GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR2>(_T("TARGET_SCREEN_RESOLUTION_UI"));
		m_IsInitialized = true;
	}
}


void UIDockInterface::Draw(const GameContext &context)
{
	if(m_ElementList.size() > 0)
	{
		for(std::pair<UINT, UIElement*> element : m_ElementList)
		{
			element.second->Draw(context);
		}
	}
}
 
void UIDockInterface::Update(const GameContext &context)
{
	if(m_ElementList.size() > 0)
	{
		UpdateDimensions(context);
		for(std::pair<UINT, UIElement*> element : m_ElementList)
		{
			element.second->Update(context);
		}
	}
}

void UIDockInterface::UpdateDimensions(const GameContext &context)
{
	m_ScreenScale = D3DXVECTOR2((float)context.Window->GetBufferWidth() / m_TargetScreenSize.x,
		(float)context.Window->GetBufferHeight() / m_TargetScreenSize.y);
}

void UIDockInterface::RemoveElement(const tstring & name)
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		if(element.second->m_Name == name)
		{
			m_ElementList.erase(element.first);
			return;
		}
	}
}

UIButton * UIDockInterface::AddButton(int x, int y, const tstring & name, const tstring & asset_file,
            function<void()> select_function, bool disabled, bool toggle_on)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
    UIButton * button = new UIButton(x, y, name, this, file);
	button->SetSelectFunction(select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(toggle_on);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}

UIToggleButton * UIDockInterface::AddToggleButton(int x, int y, const tstring & name, const tstring & asset_file,
                                    function<void()> select_function, bool disabled, bool toggle_on, bool is_on)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
    UIToggleButton * button = new UIToggleButton(x, y, name, this, file);
	button->SetSelectFunction(select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(toggle_on);
	button->SetOnline(is_on);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}

UIButtonWT * UIDockInterface::AddButtonWT(int x, int y, const tstring & name, const tstring & asset_file, UINT textX, UINT textY, const tstring & text,
		const D3DXCOLOR & text_normal, const D3DXCOLOR & text_hover, const D3DXCOLOR & text_click, shared_ptr<SpriteFont> pFont, function<void()> select_function, 
		bool disabled, bool toggle_on)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
    UIButtonWT * button = new UIButtonWT(x, y, name, this, file, textX, textY,
		text,m_pDefaultFont, text_normal, text_hover, text_click);
	button->SetSelectFunction(select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(toggle_on);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}


UILevelButton * UIDockInterface::AddButtonLevel(const int x, const int y, const tstring & name,
	const tstring & level_name, const tstring & button_image, const UINT level_id, const UINT highscore, const UINT best_time, function<void()> select_function, bool disabled)
{
	UILevelButton * button = new UILevelButton(x, y, name, this, level_name, button_image, level_id, highscore, best_time, select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(false);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}

AmountButton * UIDockInterface::AddAmountButton(int x, int y, const tstring & name, const tstring & asset_file, int amount, shared_ptr<SpriteFont> pFont, function<void()> select_function, 
	bool disabled, bool toggle_on)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
	AmountButton * button = new AmountButton(x, y, name, this, file, amount, pFont);
	button->SetSelectFunction(select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(toggle_on);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}

AmountButton * UIDockInterface::AddAmountButton(int x, int y, const tstring & name, const tstring & asset_file, int amount, function<void()> select_function, 
	bool disabled, bool toggle_on)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
	AmountButton * button = new AmountButton(x, y, name, this, file, amount, m_pDefaultFont);
	button->SetSelectFunction(select_function);
    button->SetDisabled(disabled);
    button->SetToggleOn(toggle_on);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), button));
    return button;
}

//void UIDockInterface::AddDropDown(int x, int y, tstring name, tstring asset_file, function<void(int)> select_function, int elements,
//                                float control_delay, int selected_element, bool disabled, bool toggle_on)
//{
//    UIDropDown * dropDown = new UIDropDown(x, y, name, this, asset_file, elements, control_delay, selected_element);
//    dropDown->SetDropDownFunction(select_function);
//    dropDown->SetDisabled(disabled);
//    dropDown->SetToggleOn(toggle_on);
//    m_ElementList.push_back(dropDown);
//}

void UIDockInterface::AddTextField(int x, int y, int width, int height, const tstring & name,
                            const tstring & text, const D3DXCOLOR & text_color)
{
	UITextField * text_field = new UITextField(x, y, width, name, this, text, m_pDefaultFont, text_color);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), text_field));
}

void UIDockInterface::AddTextField(int x, int y, int width, int height, const tstring & name,
                            const tstring & text, const D3DXCOLOR & text_color, shared_ptr<SpriteFont> pFont)
{
	UITextField * text_field = new UITextField(x, y, width, name, this, text, pFont, text_color);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), text_field));
}

void UIDockInterface::AddImage(int x, int y, const tstring & name, const tstring & asset_file)
{
	tstring file(asset_file);
	ConvertToResourcePath(file);
    UIImage * image = new UIImage(x, y, name, this, file);
	m_ElementList.insert(std::pair<UINT, UIElement*>(LemmingsHelpers::GenerateHash(name), image));
}

//void UIDockInterface::AddSlider(int x, int y, tstring name, tstring asset_background, tstring asset_carrot, int min_carrot,
//                            int max_carrot, int carrot_height_cor, SlideModes slide_mode, function<void(float)> function, bool disabled = false)
//{
//	LemmingsHelpers::Rect rectangle();
//    //either a slider is horizontal or vertical, depending on that the boundaries is calculated differently.
//    switch(slide_mode)
//    {
//        case UISlider.SlideModes.slide_horizontal:
//            rectangle = new Rectangle(min_carrot, carrot_height_cor, max_carrot - min_carrot, 1);
//            break;
//        case UISlider.SlideModes.slide_vertical:
//            rectangle = new Rectangle(carrot_height_cor, min_carrot, 1, max_carrot - min_carrot);
//            break;
//    }
//    UISlider * slider = new UISlider(x, y, name, this, asset_background, asset_carrot, rectangle, function, slide_mode);
//    slider->SetDisabled(disabled);
//	m_ElementList.push_back(slider);
//}
//
//void UIDockInterface::AddControllerSlider(int x, int y, tstring name, tstring asset_background, tstring asset_carrot, int min_carrot,
//                            int max_carrot, int carrot_height_cor, UISlider.SlideModes slide_mode, ScalarDelegate function,
//                            float movement_scale_incrementation, float control_delay, float start_value, bool disabled)
//{
//	LemmingsHelpers::Rect rectangle();
//    //slider is either horizontal or vertical, depending on that the boundaries in which the 
//    //carrot can move is calculated differently.
//    switch (slide_mode)
//    {
//        case UISlider.SlideModes.slide_horizontal:
//            rectangle = new Rectangle(min_carrot, carrot_height_cor, max_carrot - min_carrot, 1);
//            break;
//        case UISlider.SlideModes.slide_vertical:
//            rectangle = new Rectangle(carrot_height_cor, min_carrot, 1, max_carrot - min_carrot);
//            break;
//    }
//    UIControllerSlider * slider = new UIControllerSlider(x, y, name, this, asset_background, asset_carrot, rectangle, 
//        function, slide_mode, movement_scale_incrementation, control_delay);
//    slider->SetDisabled(disabled);
//    slider->SetScalar(start_value);
//	m_ElementList.push_back(slider);
//}
//
//UICounter * UIDockInterface::AddCounter(tstring assetFile, int x, int y, tstring name, UIDockInterface parrent, int numbersToShow)
//{
//    UICounter * counter = new UICounter(assetFile, x, y, name, parrent, numbersToShow);
//	m_ElementList.push_back(counter);
//    return counter;
//}

void UIDockInterface::SetTextField(const tstring & name, const tstring & text)
{
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		dynamic_cast<UITextField*>(element->second)->SetText(text);
	}
}

void UIDockInterface::SetButtonTextField(const tstring & name, const tstring & text)
{
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		dynamic_cast<UIButtonWT*>(element->second)
		->SetText(text);
	}
}

void UIDockInterface::SetControllerSlider(const tstring & name, float scalar)
{
	/*dynamic_cast<UIControllerSlider*>(m_ElementList[LemmingsHelpers::GenerateHash(name)])
		->SetScalar(scalar);*/
}

void UIDockInterface::SetElementVisible(const tstring & name, bool visible)
{
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		element->second->SetVisible(visible);
	}
}

void UIDockInterface::SetElementDisabled(const tstring & name, bool disabled)
{
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		element->second->SetDisabled(disabled);
	}
}

bool UIDockInterface::CursorInZone(int cursorX, int cursorY)
{
	LemmingsHelpers::Rect rectangle = GetElementZone();
    return cursorX > rectangle.X &&
        cursorX < rectangle.X + rectangle.Width &&
        cursorY > rectangle.Y &&
        cursorY < rectangle.Y + rectangle.Height;
}

bool UIDockInterface::CursorInZone(const D3DXVECTOR2 & cursorPos)
{
	return CursorInZone((int)cursorPos.x, (int)cursorPos.y);
}

void UIDockInterface::ToggleElement(const tstring & name)
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		element.second->SetToggleOn(false);
	}
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		element->second->SetToggleOn(true);
	}
}

void UIDockInterface::SelectElement(const tstring & name)
{
	UINT value = LemmingsHelpers::GenerateHash(name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		element->second->Select();
	}
}

bool UIDockInterface::SelectFirstElement()
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		if(!element.second->IsDisabled())
		{
			element.second->Select();
			return true;
		}
	}
    return false;
}

float UIDockInterface::ToggleSlider(const tstring & slider_name)
{
	UINT value = LemmingsHelpers::GenerateHash(slider_name);
	auto element = m_ElementList.find(value);
	if(element != m_ElementList.end())
	{
		return element->second->ToggleOffline();
	}
	return 0;
}

void UIDockInterface::DisableAllElements()
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		element.second->SetDisabled(true);
	}
}

void UIDockInterface::EnableAllElements()
{
	for(std::pair<UINT, UIElement*> element : m_ElementList)
	{
		element.second->SetDisabled(false);
	}
}

void UIDockInterface::SetParrent(const UIDockInterface * pParrent)
{
	m_pParrent = pParrent;
}

LemmingsHelpers::Rect UIDockInterface::GetRealElementZone() const
{
	 return LemmingsHelpers::Rect(	
		 m_ElementZone.X, m_ElementZone.Y,
		(int)(m_ScreenScale.x * m_ElementZone.Width),
		(int)(m_ScreenScale.y * m_ElementZone.Height)
	);
}

LemmingsHelpers::Rect UIDockInterface::GetElementZone() const
{
	 return m_ElementZone;
}

void UIDockInterface::SetPosition(int x, int y)
{
	m_ElementZone.X = x;
	m_ElementZone.Y = y;
}

void UIDockInterface::SetPosition(const D3DXVECTOR2 & position)
{
	m_ElementZone.X = (int)position.x;
	m_ElementZone.Y = (int)position.y;
}

void UIDockInterface::ConvertToResourcePath(tstring & file)
{
	tstringstream strstr;
	strstr << GlobalParameters::GetParameters()->GetParameter<tstring>(_T("UI_DIRECTORY"));
	strstr << file;
	file = strstr.str();
}