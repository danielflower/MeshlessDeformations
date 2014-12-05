#include "GUIManager.h"
#include "main.h"

IGUIEnvironment* GUIManager::environment;

IGUIScrollBar* GUIManager::alphaScrollbar = 0;
IGUIScrollBar* GUIManager::betaScrollbar = 0;
IGUIScrollBar* GUIManager::gravityScrollbar = 0;
IGUIScrollBar* GUIManager::timeScrollbar = 0;

IGUIScrollBar* GUIManager::elasticityScrollbar = 0;
IGUICheckBox* GUIManager::goalPositionsCheckbox = 0;
IGUICheckBox* GUIManager::visibilityCheckbox = 0;
IGUIListBox* GUIManager::modeListbox = 0;
IGUIListBox* GUIManager::objectsListbox = 0;


bool GUIManager::GUIEvent( SEvent event ) {

	IGUIElement* caller = event.GUIEvent.Caller;

	switch(event.GUIEvent.EventType)
	{
		case EGET_SCROLL_BAR_CHANGED:
			if (caller == alphaScrollbar)
			{
				if (Globals::selectedObject) {
					Globals::selectedObject->alpha = (float) alphaScrollbar->getPos() / 1000.0f;
					std::cout << Globals::selectedObject->alpha  << "\n" << std::flush;
					return true;
				}

			} else if (caller == betaScrollbar) {
				if (Globals::selectedObject) {
					Globals::selectedObject->beta = (float) betaScrollbar->getPos() / 1000.0f;
					std::cout << Globals::selectedObject->beta  << "\n" << std::flush;
					return true;
				}
			} else if (caller == timeScrollbar) {				f32 value = timeScrollbar->getPos() / 1000.0f;								if (value < 0.1f) {					Globals::stopMode = true;				} else {					Globals::stopMode = false;					Globals::device->getTimer()->setSpeed( value );				}				std::cout << value << "\n" << std::flush;

				return true;			} else if (caller == gravityScrollbar) {				Globals::gravity = gravityScrollbar->getPos() / 1000.0f;				std::cout << Globals::gravity << "\n" << std::flush;
				return true;			} else if (caller == elasticityScrollbar) {				if (Globals::selectedObject) {					Globals::selectedObject->elasticity = elasticityScrollbar->getPos()/1000.0f;					std::cout << Globals::selectedObject->elasticity << "\n" << std::flush;
					return true;				}			}
			break;
		case EGET_CHECKBOX_CHANGED:
			if (caller == goalPositionsCheckbox) {
				Globals::drawGoalPositions = goalPositionsCheckbox->isChecked();
				return true;
			} else if (caller == visibilityCheckbox) {
				if (Globals::selectedObject) {
					Globals::selectedObject->setVisible( visibilityCheckbox->isChecked() );
					return true;
				}
			}
			break;
		case EGET_LISTBOX_CHANGED:
			if (caller == modeListbox) {
				Globals::mode = (DeformationMode::DeformationMode)modeListbox->getSelected();
				return true;
			} else if (caller == objectsListbox) {
				setSelectedObject ( Globals::objects [objectsListbox->getSelected()] );
				return true;
			}
			break;
	}

	return false;
}


void GUIManager::setSelectedObject (Model::DeformableObject* object) {

	for (u16 index = 0; index < Globals::objects.size(); index ++) {
		if (Globals::objects[index] == object) {
			objectsListbox->setSelected( index );
			break;
		}

	}

	Globals::selectedObject = object;

	alphaScrollbar->setPos( (s32) (object->alpha * 1000) );
	betaScrollbar->setPos( (s32) (object->beta * 1000) );
	elasticityScrollbar->setPos( (s32) (object->elasticity * 1000) );

	visibilityCheckbox->setChecked( object->isVisible() );


}


void GUIManager::createGUIElements( IGUIEnvironment* env ) {
	GUIManager::environment = environment;

	env->addStaticText(L"Alpha:", rect<s32>(10, 10, 50, 25), true, false, 0, 0, true);
	alphaScrollbar = env->addScrollBar(true, rect<s32>(70, 10, 200, 25), 0, 0);
	alphaScrollbar->setMax(1000);
	alphaScrollbar->setPos(325);

	env->addStaticText(L"Beta:", rect<s32>(10, 25, 50, 40), true, false, 0, 0, true);
	betaScrollbar = env->addScrollBar(true, rect<s32>(70, 25, 200, 40), 0, 0);
	betaScrollbar->setMax(1000);
	betaScrollbar->setPos(0);

	env->addStaticText(L"Elasticity:", rect<s32>(10, 40, 50, 55), true, false, 0, 0, true);
	elasticityScrollbar = env->addScrollBar(true, rect<s32>(70, 40, 200, 55), 0, 0);
	elasticityScrollbar->setMax(1000);
	elasticityScrollbar->setPos( 500 );

	env->addStaticText(L"Show object", rect<s32>(35,55,200,70), true, false, 0, 0, true);
	visibilityCheckbox = env->addCheckBox( true, rect<s32>(10, 55, 30, 70), 0, 0);

	env->addStaticText(L"Gravity:", rect<s32>(10, 80, 50, 95), true, false, 0, 0, true);
	gravityScrollbar = env->addScrollBar(true, rect<s32>(70, 80, 200, 95), 0, 0);
	gravityScrollbar->setMax(500);
	gravityScrollbar->setPos(Globals::gravity*500.0f);

	env->addStaticText(L"Show goal positions", rect<s32>(35, 110,200,125), true, false, 0, 0, true);
	goalPositionsCheckbox = env->addCheckBox( Globals::drawGoalPositions, rect<s32>(10, 110, 30, 125), 0, 0);

	env->addStaticText(L"Algorithm", rect<s32>(10, 135,100,150), true, false, 0, 0, true);
	modeListbox = env->addListBox(rect<s32>(10, 150, 100, 192), 0, true);
	modeListbox->addItem( L"Basic" );
	modeListbox->addItem( L"Linear" );
	modeListbox->addItem( L"Quadratic" );
	modeListbox->setSelected( Globals::mode );

	env->addStaticText(L"Select object", rect<s32>(10, 202,100,217), true, false, 0, 0, true);
	objectsListbox = env->addListBox(rect<s32>(10, 217, 100, 320), 0, true);
	for (u16 index = 0; index < Globals::objects.size(); index ++) {
		Model::DeformableObject* object = Globals::objects [index];
		objectsListbox->addItem( object->name.c_str() );
	}
	objectsListbox->setSelected( 0 );

	f32 timeY =  95.0f;
	env->addStaticText(L"Time:", rect<s32>(10, timeY, 50, timeY+15), true, false, 0, 0, true);
	timeScrollbar = env->addScrollBar(true, rect<s32>(70, timeY, 200, timeY+15), 0, 0);
	timeScrollbar->setMax(1000);
	timeScrollbar->setPos(1000);

}