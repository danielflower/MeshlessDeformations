#include "Particle.h"
#include "DeformableObject.h"
#include "DeformableObjectMesh.h"
#include "Globals.h"

using namespace Model;

video::SMaterial Particle::boundingBoxMaterial = video::SMaterial();
video::SMaterial Particle::boundingBoxMaterialSelected = video::SMaterial();

//CONSTRUCTORS
Particle::Particle(DeformableObject *owner, f32 radius, f32 weight) : ModelObject(ObjectType::ParticleType)
{
	this->owner = owner;
	this->radius = radius;
	this->weight = weight;

	originalPosition = core::vector3df(0.0f, 0.0f, 0.0f);

	scene::IAnimatedMesh* earthMesh = Globals::sceneManager->getMesh("earth.x");

	if (Globals::useShadows) {
		scene::IAnimatedMeshSceneNode* earth = Globals::sceneManager->addAnimatedMeshSceneNode( earthMesh, this, 0 );

		earth->setScale( core::vector3df(radius,radius,radius) );
		earth->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
		earth->addShadowVolumeSceneNode();
		Globals::sceneManager->setShadowColor(video::SColor(150,0,0,0));

	} else {



		scene::IMesh* earth = Globals::sceneManager->getMeshManipulator()->createMeshWithTangents(earthMesh->getMesh(0));
		Globals::sceneManager->getMeshManipulator()->scaleMesh( earth, core::vector3df(radius,radius,radius));
		Globals::sceneManager->addMeshSceneNode( earth, this, 0 );
	}

	ModelObject::Box = core::aabbox3d<f32>(-radius,-radius,-radius, radius, radius, radius );

	boundingBoxMaterialSelected.AmbientColor = video::SColor( 128, 255, 0, 0 );
	boundingBoxMaterial.AmbientColor = video::SColor( 128, 0, 0, 0 );


}

Particle::Particle(DeformableObject *owner, f32 weight) : ModelObject(ObjectType::ParticleType){
	this->owner = owner;
	this->radius = 2.0;
	this->weight = weight;
}

// Determine whether we should draw this node, and the children nodes
void Particle::OnPreRender()
{
	if (owner->isVisible() && !owner->is(ObjectType::DeformableObjectMesh)) {
		// Draw this node
		SceneManager->registerNodeForRendering(this);


		// Draw the children nodes
		ISceneNode::OnPreRender();

	}

}


// Draws this node to the screen
void Particle::render()
{
	if (Globals::drawGoalPositions && !owner->is(ObjectType::DeformableObjectMesh)) {
		Globals::driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		aabbox3d<f32> goal = aabbox3d<f32>( goalPosition - core::vector3df(radius, radius, radius) - getPosition(), goalPosition + core::vector3df( radius, radius, radius ) - getPosition());
		if (this->owner == Globals::selectedObject) {
			Globals::driver->setMaterial( boundingBoxMaterialSelected );
		} else {
			Globals::driver->setMaterial( boundingBoxMaterial );
		}
		Globals::driver->draw3DBox( goal, video::SColor(0, 255, 0, 0) );
	}
}

vector3df Particle::getForces()
{
	core::vector3df force = core::vector3df(0.f, 0.0f, 0.0f);
	// add gravity
	force +=  core::vector3df(0, -Globals::gravity*1000, 0) * this->weight;
	// add drag
	force += velocity * -Globals::drag;

	// external forces
	//force += particle->externalForce;
	//particle->externalForce = core::vector3df();

	return force;
}

bool Particle::canMoveTo ( const vector3df &newPosition ) {
	return getCollidedObject (newPosition) == 0;
}

ModelObject* Particle::getCollidedObject ( const vector3df &newPosition ) {
	if ( !Globals::boundary->getResizedBoundary( -radius ).isPointInside( newPosition ) ) {
		return Globals::boundary;
	}
	//check for particle-to-particle collisions
	for (u16 index = 0; index < Globals::objects.size(); index ++) {
		Model::DeformableObject* other = Globals::objects [index];
		if (this->owner==other || !other->isVisible()) {
			continue;
		}
		array<Particle*> particles = other-> getParticles();

		for (u16 particleindex = 0; particleindex < particles.size(); particleindex ++) {
			Particle* particle = particles [particleindex];

			f32 distance = (f32) particle->getPosition().getDistanceFrom(newPosition);
			if (distance < this->radius + particle->radius) {
				return particle;
			}

		}

	}
	return 0;
}


// The Particle is only in charge of updating its position according to its 
// actual velocity. The velocity is only updated by the Object it belongs to.
// Not sure if Reflection from Borders works this way.
void Particle::update(f32 timeElapsed) {

	if (isSelected) {
		// the user currently has this particle picked up with their mouse,
		// so let's not change anything but grab its current position for 
		// calculations
		velocity = ( getPosition() - position) / timeElapsed;
		if(!owner->is(ObjectType::DeformableObjectMesh)) {
		    return;
		}
	}

	if(!isSelected) {
		vector3df force = getForces();
		// v_i(t + h) = v_i(t) + \alpha \frac{g_i(t) - x_i(t)}{h}
		velocity = velocity + ((goalPosition - roofPosition) / timeElapsed) * 
			(owner->alpha) + (force/weight)*timeElapsed ;

		vector3df translation;
		translation = velocity * timeElapsed;

		// check for collisions
		ModelObject* collidedWith = getCollidedObject (position + translation);
		if (collidedWith) {

			if (collidedWith->is(ObjectType::BoundaryType)) {
				vector3df normal = Globals::boundary->getNormal(position, radius );
				velocity = getReflected( velocity, normal ) * (1-owner->elasticity);
			}else {
				Particle* other = (Particle*) collidedWith;
				vector3df normal = this->getPosition() - other->getPosition();
				velocity = getReflected( velocity, normal ) * (1-owner->elasticity);
				other->velocity = -velocity;

			}

		} else {

			position = position + translation;
		}
		setPosition(position);
	}


	if(owner->is(ObjectType::DeformableObjectMesh)) {
		Model::DeformableObjectMesh *deform_mesh = (Model::DeformableObjectMesh *) owner;
		deform_mesh->mesh->vertices[nr].Pos = position;

		return;
	}
}



