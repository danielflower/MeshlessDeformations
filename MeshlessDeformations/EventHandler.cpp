#include "EventHandler.h"
#include "Particle.h"

bool EventHandler::OnEvent(SEvent event)
{ 
	
	if(event.EventType == EET_KEY_INPUT_EVENT){      
		return this->keyboardEvent(event);
	}
	
	if (event.EventType == EET_GUI_EVENT) {
		return GUIManager::GUIEvent( event );
	}


	if (event.EventType == EET_MOUSE_INPUT_EVENT) {
		
		core::position2d< s32 > mousePosition(event.MouseInput.X, event.MouseInput.Y);
		
		if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN ) {

			selectedSceneNode = (Model::ModelObject*)Globals::sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB( mousePosition, ObjectType::SelectableObject );


			if (selectedSceneNode) {
				startPosition = selectedSceneNode->getPosition();
				lastObjectPosition = selectedSceneNode->getPosition();

				oneBeforeLastObjectPosition = lastObjectPosition;
				currentSelected= selectedSceneNode;
				currentSelected->isSelected = true;

				core::vector3df normal = Globals::camera->getPosition() - Globals::camera->getTarget();
				normal.normalize();
				movePlane = core::plane3d<f32>( startPosition, normal );

				if (selectedSceneNode->is( ObjectType::ParticleType ) ) {
					Model::Particle* particle = (Model::Particle*) selectedSceneNode;
					GUIManager::setSelectedObject( particle->owner );


					Model::DeformableObjectMesh *mesh = (Model::DeformableObjectMesh*) particle->owner;
					selectedParticles.clear();
					for (u32 i = 0; i < particle->owner->particles.size(); i++) {
						Model::Particle* myPar = particle->owner->particles [i];
						if (particle->position.getDistanceFromSQ(myPar-> position) < mesh->pickingRadiusSquared) {
							myPar->isSelected = true;
							selectedParticles.push_back(myPar);

						}
					}


				}

			}

		} else if (event.MouseInput.Event == EMIE_MOUSE_MOVED) {

			if (currentSelected && currentSelected->is (ObjectType::ParticleType)) {
				Model::Particle* particle = (Model::Particle*) currentSelected;

				core::line3d<f32> line = Globals::sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePosition, Globals::camera );
					
//				f32 parameter = (currentSelected->getPosition().Z - line.start.Z)/line.getVector().Z;
//				core::vector3df newPosition = line.start + line.getVector() * parameter;

				core::vector3df newPosition;
				movePlane.getIntersectionWithLine( line.start, line.getVector(), newPosition );

				if(particle->owner->is(ObjectType::DeformableObjectMesh)) {

					Model::DeformableObjectMesh *mesh = (Model::DeformableObjectMesh*) particle->owner;

					particle->owner->isSelected = true;

					core::vector3df translation = newPosition - particle->position;
					
					for (u32 i = 0; i < selectedParticles.size(); i++) {
						Model::Particle* myPar = selectedParticles [i];

						core::vector3df temp = myPar->position + translation;
						if(myPar->canMoveTo(temp)) {
							myPar->position += translation;
							myPar->setPosition(myPar->position );
						}
					}

					if (particle->canMoveTo (newPosition)) {
			
						oneBeforeLastObjectPosition = lastObjectPosition;
						lastObjectPosition = newPosition;
					}


				} else {
					

					if (particle->canMoveTo (newPosition)) {
						currentSelected->setPosition ( newPosition );
						((Model::Particle *)currentSelected)->position = newPosition;

						oneBeforeLastObjectPosition = lastObjectPosition;
						lastObjectPosition = newPosition;
					}
				
				}

			}

		} else if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP) {

			if (currentSelected && currentSelected->is (ObjectType::ParticleType)) {
				Model::Particle* particle = (Model::Particle*) currentSelected;


				core::line3d<f32> line = Globals::sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates( mousePosition, Globals::camera );
					
				//f32 parameter = (currentSelected->getPosition().Z - line.start.Z)/line.getVector().Z;
				//core::vector3df newPosition = line.start + line.getVector() * parameter;

				core::vector3df newPosition;
				movePlane.getIntersectionWithLine( line.start, line.getVector(), newPosition );

				core::vector3df velocity = (newPosition - oneBeforeLastObjectPosition)/Globals::timeElapsed;

				particle->velocity = velocity;

				for (u32 i = 0; i < selectedParticles.size(); i++) {
					Model::Particle* myPar = selectedParticles [i];
					myPar->velocity = velocity;
					myPar->isSelected = false;
				}
				selectedParticles.clear();

				particle->owner->isSelected = false;

			}


			if (currentSelected) {
				currentSelected->isSelected = false;
				currentSelected =0;
			}
		}


	}



	return false;

}


bool EventHandler::keyboardEvent( SEvent event ) {


	if (event.KeyInput.PressedDown) {
		return false;
	}

	switch(event.KeyInput.Key) {
		case KEY_ESCAPE: {

			Globals::device->closeDevice();
			Globals::camera->OnPostRender(Globals::device->getTimer()->getTime());
			return true; 
		}
		case KEY_PAUSE: {

			Globals::stopMode = ! Globals::stopMode;
			return true; 
		}


		break;
	}

	return false;
}
