#include "ObjectFactory.h"
#include "Globals.h"
#include "DeformableObject.h"
#include "DeformableObjectMesh.h"


void ObjectFactory::createObjects (void) {
	// set up some objects

	{ // set up one
	Model::DeformableObject* object = new Model::DeformableObject( L"Cube One" );
	object->alpha = 0.323f;
	Globals::selectedObject = object;
	Globals::objects.push_back( object );


	Model::Particle* particle1 = new Model::Particle(object, 7, 1);
	particle1->setOriginalPosition( core::vector3df( 0.0f, 0.0f, 0.0f ) );
	object->addParticle(particle1);

	Model::Particle* particle2 = new Model::Particle(object, 7, 1);
	particle2->setOriginalPosition( core::vector3df( 20.0f, 0.0f, 0.0f ) );
	object->addParticle( particle2 );
	
	Model::Particle* particle3 = new Model::Particle(object, 7, 1);
	particle3->setOriginalPosition( core::vector3df( 20.0f, 20.0f, 0.0f ) );
	object->addParticle( particle3 );
	
	Model::Particle* particle4 = new Model::Particle(object, 7, 1);
	particle4->setOriginalPosition( core::vector3df( 0.0f, 20.0f, 0.0f ) );
	object->addParticle( particle4 );

	Model::Particle* particle5 = new Model::Particle(object, 7, 1);
	particle5->setOriginalPosition( core::vector3df( 0.0f, 0.0f, 20.0f ) );
	object->addParticle( particle5 );

	Model::Particle* particle6 = new Model::Particle(object, 7, 1);
	particle6->setOriginalPosition( core::vector3df( 20.0f, 0.0f, 20.0f ) );
	object->addParticle( particle6 );

	Model::Particle* particle7 = new Model::Particle(object, 7, 1);
	particle7->setOriginalPosition( core::vector3df( 0.0f, 20.0f, 20.0f ) );
	object->addParticle( particle7 );

	Model::Particle* particle8 = new Model::Particle(object, 7, 1);
	particle8->setOriginalPosition( core::vector3df( 20.0f, 20.0f, 20.0f ) );
	object->addParticle( particle8 );

	
	object->setVisible(true);

	}

	{ // set up another
	Model::DeformableObject* object = new Model::DeformableObject( L"Cube Two" );
	object->alpha = 0.323f;
	object->setVisible(false);
	Globals::objects.push_back( object );

	Model::Particle* particle1 = new Model::Particle(object, 7, 1);
	particle1->setOriginalPosition( core::vector3df( 70.0f, 70.0f, 0.0f ) );
	object->addParticle(particle1);

	Model::Particle* particle2 = new Model::Particle(object, 7, 1);
	particle2->setOriginalPosition( core::vector3df( 90.0f, 70.0f, 0.0f ) );
	object->addParticle( particle2 );
	
	Model::Particle* particle3 = new Model::Particle(object, 7, 1);
	particle3->setOriginalPosition( core::vector3df( 90.0f, 90.0f, 0.0f ) );
	object->addParticle( particle3 );
	
	Model::Particle* particle4 = new Model::Particle(object, 7, 1);
	particle4->setOriginalPosition( core::vector3df( 70.0f, 90.0f, 0.0f ) );
	object->addParticle( particle4 );

	Model::Particle* particle5 = new Model::Particle(object, 7, 1);
	particle5->setOriginalPosition( core::vector3df( 70.0f, 70.0f, 20.0f ) );
	object->addParticle( particle5 );

	Model::Particle* particle6 = new Model::Particle(object, 7, 1);
	particle6->setOriginalPosition( core::vector3df( 90.0f, 70.0f, 20.0f ) );
	object->addParticle( particle6 );

	Model::Particle* particle7 = new Model::Particle(object, 7, 1);
	particle7->setOriginalPosition( core::vector3df( 70.0f, 90.0f, 20.0f ) );
	object->addParticle( particle7 );

	Model::Particle* particle8 = new Model::Particle(object, 7, 1);
	particle8->setOriginalPosition( core::vector3df( 90.0f, 90.0f, 20.0f ) );
	object->addParticle( particle8 );
	
	}





	{ // set up another
		Model::DeformableObject* object = new Model::DeformableObject( L"Face" );
		object->alpha = 0.723f;
		object->setVisible(false);
		Globals::objects.push_back( object );

		Model::Particle* particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 30.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, -30.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 30.0f, 00.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -30.0f, 0.0f, 30.0f ) );
		object->addParticle(particle);


		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 21.0f, 21.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 21.0f, -21.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -21.0f, 21.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -21.0f, -21.0f, 30.0f ) );
		object->addParticle(particle);


		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 27.8f, 11.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 27.8f, -11.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -27.8f, 11.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -27.8f, -11.0f, 30.0f ) );
		object->addParticle(particle);


		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 11.0f, 27.8f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -11.0f, 27.8f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 11.0f, -27.8f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -11.0f, -27.8f, 30.0f ) );
		object->addParticle(particle);


		// eyes
		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -10.0f, 11.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 10.0f, 11.0f, 30.0f ) );
		object->addParticle(particle);

		// nose
		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 0.0f, 30.0f ) );
		object->addParticle(particle);

		// mouth
		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, -15.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -6.5f, -15.0f, 30.0f ) );
		object->addParticle(particle);
		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 6.5f, -15.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( -13.0f, -12.0f, 30.0f ) );
		object->addParticle(particle);
		particle = new Model::Particle(object, 3, 1);
		particle->setOriginalPosition( core::vector3df( 13.0f, -12.0f, 30.0f ) );
		object->addParticle(particle);
	}









	{ // set up another
		Model::DeformableObject* object = new Model::DeformableObject( L"Bi-particle" );
		object->alpha = 0.323f;
		object->setVisible(false);
		Globals::objects.push_back( object );

		Model::Particle* particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 70.0f, -50.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 21, 4);
		particle->setOriginalPosition( core::vector3df( 70.0f, 70.0f, -75.0f ) );
		object->addParticle(particle);

	}


	{ // set up another
		Model::DeformableObject* object = new Model::DeformableObject( L"Hanger" );
		object->alpha = 0.323f;
		object->setVisible(false);
		Globals::objects.push_back( object );

		Model::Particle* particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 70.0f, 50.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 40.0f, 50.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 40.0f, 60.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 40.0f, 40.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 40.0f, 30.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 7, 1);
		particle->setOriginalPosition( core::vector3df( 70.0f, 40.0f, 70.0f ) );
		object->addParticle(particle);

	}



/* goodbye, Squasher
	{ // set up the weight
		Model::DeformableObject* object = new Model::DeformableObject( L"Squasher" );
		object->alpha = 1.0f;
		object->setVisible(false);
		Globals::objects.push_back( object );

		Model::Particle* particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -20.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -10.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 10.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 20.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);



		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -20.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -10.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 10.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 20.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);



		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -20.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( -10.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 10.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 24);
		particle->setOriginalPosition( core::vector3df( 20.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);




	}
*/


	{ // set up the weight
		Model::DeformableObject* object = new Model::DeformableObject( L"Modern Art" );
		object->alpha = 0.5f;
		object->setVisible(false);
		Globals::objects.push_back( object );


		Model::Particle* particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 80.0f, 0.0f ) );
		object->addParticle(particle);


		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( -20.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( -10.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 10.0f, 110.0f, 0.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 20.0f, 110.0f, 0.0f ) );
		object->addParticle(particle);



		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( -20.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( -10.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 10.0f, 110.0f, 10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 20.0f, 110.0f, 20.0f ) );
		object->addParticle(particle);



		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 100.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 100.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 0.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 10.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);

		particle = new Model::Particle(object, 4, 1);
		particle->setOriginalPosition( core::vector3df( 20.0f, 90.0f, -10.0f ) );
		object->addParticle(particle);




	}







    // setup a mesh 
	{
	Model::DeformableObject* object = new Model::DeformableObjectMesh( L"Duck" , "resources/duck.dcmesh");
	object->alpha = 0.372f;
	object->setVisible(false);
	Globals::objects.push_back( object );
	}

}
