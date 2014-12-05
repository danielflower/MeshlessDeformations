#include "DeformableObjectMesh.h"
#include "Globals.h"
#include "S3DVertex.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace Model;

DeformableObjectMesh::DeformableObjectMesh(core::stringw name, char *filename) : DeformableObject(ObjectType::DeformableObjectMesh) {
	
	isSelected = false;
	type=ObjectType::DeformableObjectMesh;
	beta = 0.0f;
	alpha = 0.5f;
	elasticity = 0.5f;
	this->name = name;

	core::aabbox3df boundingBox;

	std::ifstream meshstream(filename);
	std::string line,ignore;
	f32 x,y,z,ti,tj;
	int t1, t2, t3;
	core::array<vector3df> v;
	core::array<vector2df> tex_coords;
	core::array<u16> in;
	while(!meshstream.eof()) {
		meshstream >> line;
		if(line == "v") {
			meshstream >> x >> y >> z;
			core::vector3df position = vector3df(x,y,z)*10;
			v.push_back(position);
			boundingBox.addInternalPoint(position);
		} else if (line == "f") {
			meshstream >> t3 >> t2 >> t1; 
			in.push_back(t1);
			in.push_back(t2);
			in.push_back(t3);
		} else if (line == "t") {
			meshstream >> ti >> tj;
			tex_coords.push_back(vector2df(ti,tj));
		} else
		  getline(meshstream,ignore,'\n');
	}

	// generate normals and stuff 
	core::array<vector3df> n(v.size());
	n.set_used(v.size());
	vector3df v1,v2,nt;
	for(int i=0;i+2<in.size();i+=3){
		v1 = (v[in[i+1]] - v[in[i]]);
		v2 = (v[in[i+2]] - v[in[i]]);
		nt = v1.crossProduct(v2);

		n[(int)in[i]] += nt;
		n[(int)in[i+1]] += nt;
		n[(int)in[i+2]] += nt;
	}
	cout<<v.size();

	//save in simple mesh struct
	mesh = new SimpleMesh(v.size(),in.size());
	Particle *p;
	for(int i=0;i<v.size();i++) {
		n[i].normalize();
		mesh->vertices[i] = irr::video::S3DVertex(v[i],n[i],video::SColor(1,1,1,1),vector2df(0,0));
		p = new Particle(this,(float)1.0/(float)v.size()*300.0);
		p->setOriginalPosition(v[i]);
		addParticle(p);
	}
	for(int i=0;i<in.size();i++) {
		mesh->indices[i] = in[i];
	}
	mesh->material.Wireframe=false;
	mesh->material.Lighting=true;
	mesh->material.BackfaceCulling=false;
	mesh->material.NormalizeNormals=true;


	// work out the bounding radius
	vector3df span = boundingBox.MaxEdge - boundingBox.MinEdge;
	const f32 pickingProportion = 0.15f;
	pickingRadiusSquared = pickingProportion * max_( max_( span.X, span.Y ), span.Z ) / 2.0f;
	pickingRadiusSquared *= pickingRadiusSquared;
}

DeformableObjectMesh::~DeformableObjectMesh(void)
{
	delete mesh;
}

// Draws this node to the screen
void DeformableObjectMesh::render()
{
	video::IVideoDriver* driver = Globals::sceneManager->getVideoDriver();

	driver->setMaterial(mesh->material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawIndexedTriangleList(mesh->vertices, mesh->vertexCount, mesh->indices, mesh->triangleCount);

	//if (Globals::drawGoalPositions) {
	//	Globals::driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	//	aabbox3d<f32> goal = aabbox3d<f32>( goalPosition - core::vector3df(radius, radius, radius) - getPosition(), goalPosition + core::vector3df( radius, radius, radius ) - getPosition());
	//	Globals::driver->draw3DBox( goal, video::SColor(0, 255, 0, 0) );
	//}
}
