#if !defined(GUIManager_h)
#define GUIManager_h
#include "irrlicht.h"
#include "Globals.h"
#include "DeformableObject.h"



using namespace irr;
using namespace gui;using namespace core;
class GUIManager {
public:

	static void createGUIElements(IGUIEnvironment* env);
	static bool GUIEvent( SEvent event );

	static IGUIEnvironment* environment;
	static IGUIScrollBar* alphaScrollbar;
	static IGUIScrollBar* betaScrollbar;
	static IGUIScrollBar* elasticityScrollbar;

	static IGUIScrollBar* gravityScrollbar;
	static IGUIScrollBar* timeScrollbar;

	static IGUICheckBox* goalPositionsCheckbox;
	static IGUICheckBox* visibilityCheckbox;


	static IGUIListBox* modeListbox;
	static IGUIListBox* objectsListbox;

	static void setSelectedObject (Model::DeformableObject* object);


private:
	GUIManager();
};
#endif // end if!defined for this header