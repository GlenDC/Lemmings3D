//====================== #INCLUDES ===================================
//====================================================================

//====================== PlayerController Class =================================
// Description:
//		Playercontroller class, reason to make a seperete class to use 
//		as a composition within the ControlManager class is so that
//		We can change the control's fast + seperate the complete logic
//		some more from the core input to the game meaning
// Last Modification: 04/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

private:
	// Disabling default copy constructor and default assignment operator.
	PlayerController(const PlayerController& yRef);									
	PlayerController& operator=(const PlayerController& yRef);
};