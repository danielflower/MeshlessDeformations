#include "Boundary.h"

using namespace Model;



//CONSTRUCTORS
Boundary::Boundary(core::aabbox3d<f32> Box) : ModelObject(ObjectType::BoundaryType)
{

	this->Box = Box;
	min = Box.MinEdge;
	max = Box.MaxEdge;

	CreateBox( max.X - min.X, max.Y - min.Y, max.Z - min.Z );

}

// Draws this node to the screen
void Boundary::render()
{
	//Globals::driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	//Globals::driver->draw3DBox( Box, video::SColor(0, 255, 0, 0) );
}

core::aabbox3d<f32> Boundary::getResizedBoundary(f32 resizeAmount) {
	core::aabbox3d<f32> newBox = core::aabbox3d<f32>(Box.MinEdge.X - resizeAmount, Box.MinEdge.Y - resizeAmount, Box.MinEdge.Z - resizeAmount, Box.MaxEdge.X + resizeAmount, Box.MaxEdge.Y + resizeAmount, Box.MaxEdge.Z + resizeAmount );
	newBox.MinEdge += getPosition();
	newBox.MaxEdge += getPosition();
	return newBox;
}

core::vector3df Boundary::getNormal(core::vector3df position, f32 distance) {
	
	core::aabbox3d<f32> Box = getResizedBoundary(-distance);

	core::vector3df normal = core::vector3df();
	if ( Box.MaxEdge.X - position.X  < 0 ) {
		normal += core::vector3df( -1.0f, 0.0f, 0.0f );
	}
	if ( Box.MinEdge.X - position.X > 0 ) {
		normal += core::vector3df( 1.0f, 0.0f, 0.0f );
	}
	if ( Box.MaxEdge.Y - position.Y  < 0 ) {
		normal += core::vector3df( 0.0f, -1.0f, 0.0f );
	}
	if ( Box.MinEdge.Y - position.Y > 0 ) {
		normal += core::vector3df( 0.0f, 1.0f, 0.0f );
	}
	if ( Box.MaxEdge.Z - position.Z  < 0 ) {
		normal += core::vector3df( 0.0f, 0.0f, -1.0f );
	}
	if ( Box.MinEdge.Z - position.Z > 0 ) {
		normal += core::vector3df( 0.0f, 0.0f, 1.0f );
	}
	return normal;
}




// adapted from code from CS777 project
void Boundary::CreateBox( f32 width, f32 height, f32 depth ) {

	scene::SMesh* mesh = new scene::SMesh();

	f32 textureWidth = width * 4.0f;
	f32 textureHeight = height;

	video::SColor color = video::SColor( 128, 99, 99, 99 );

	SMeshBuffer *sideWall = new scene::SMeshBuffer();
	sideWall->Material.Texture1 = Globals::driver->getTexture("boxSides.jpg");
	sideWall->Material.Lighting = true;

	float tu = width / textureWidth;
	float tv = height / textureHeight;
	float change = tu;


	float halfWidth = width / 2.0f;
	float halfHeight = height/2.0f;
	float halfDepth = depth/2.0f;
	float x = 0.0f;

	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth,-halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, 0.0f ) );
	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth, halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, tv ) );

	tu += change;
	x += change;

	sideWall->Vertices.push_back( video::S3DVertex( halfWidth,-halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, 0.0f ) );
	sideWall->Vertices.push_back( video::S3DVertex( halfWidth, halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, tv ) );
	tu += change;
	x += change;

	sideWall->Vertices.push_back( video::S3DVertex( halfWidth,-halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, color, x, 0.0f ) );
	sideWall->Vertices.push_back( video::S3DVertex( halfWidth, halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, color, x, tv ) );
	tu += 0.0f;
	x += change;

	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth,-halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, color, x, 0.0f ) );
	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth, halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, color, x, tv ) );

	tu += 0.0f;
	x += change;

	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth,-halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, 0.0f ) );
	sideWall->Vertices.push_back( video::S3DVertex( -halfWidth, halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, color, x, tv ) );


	sideWall->Indices.push_back( 0 );
	sideWall->Indices.push_back( 2 );
	sideWall->Indices.push_back( 1 );

	sideWall->Indices.push_back( 1 );
	sideWall->Indices.push_back( 2 );
	sideWall->Indices.push_back( 3 );

	sideWall->Indices.push_back( 2 );
	sideWall->Indices.push_back( 4 );
	sideWall->Indices.push_back( 3 );

	sideWall->Indices.push_back( 3 );
	sideWall->Indices.push_back( 4 );
	sideWall->Indices.push_back( 5 );

	sideWall->Indices.push_back( 4 );
	sideWall->Indices.push_back( 6 );
	sideWall->Indices.push_back( 5 );

	sideWall->Indices.push_back( 5 );
	sideWall->Indices.push_back( 6 );
	sideWall->Indices.push_back( 7 );

	sideWall->Indices.push_back( 6 );
	sideWall->Indices.push_back( 8 );
	sideWall->Indices.push_back( 7 );

	sideWall->Indices.push_back( 7 );
	sideWall->Indices.push_back( 8 );
	sideWall->Indices.push_back( 9 );

	// the next six indices define the lid of the box
	// TODO need to fix this so the texture is displayed properly
	sideWall->Indices.push_back( 1 );
	sideWall->Indices.push_back( 3 );
	sideWall->Indices.push_back( 5 );

	sideWall->Indices.push_back( 1 );
	sideWall->Indices.push_back( 5 );
	sideWall->Indices.push_back( 7 );

	// add the bottom to the box
	sideWall->Indices.push_back( 0 );
	sideWall->Indices.push_back( 4 );
	sideWall->Indices.push_back( 2 );

	sideWall->Indices.push_back( 0 );
	sideWall->Indices.push_back( 6 );
	sideWall->Indices.push_back( 4 );



	sideWall->recalculateBoundingBox();



	mesh->addMeshBuffer( sideWall );
	mesh->recalculateBoundingBox();

	Globals::sceneManager->addMeshSceneNode( mesh, this, 0 );

}

