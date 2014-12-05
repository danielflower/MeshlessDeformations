#if !defined(DEFORMABLEOBJECTMESH_H)
#define DEFORMABLEOBJECTMESH_H

#include <irrlicht.h>
#include "DeformableObject.h"


using namespace irr;
using namespace core;
using namespace scene;


class SimpleMesh {
public:
	SimpleMesh(int num_vertices, int num_indices) {
		vertices = new irr::video::S3DVertex[num_vertices];
		indices = new u16[num_indices];
		vertexCount = num_vertices;
		triangleCount = num_indices/3;
	}
	~SimpleMesh() {
		delete vertices;
		delete indices;
	}
	int vertexCount;
	int triangleCount;
	irr::video::S3DVertex *vertices;
	u16 *indices;
	video::SMaterial material;
};

namespace Model
{

class DeformableObjectMesh : public DeformableObject
{
public:

	DeformableObjectMesh(core::stringw name, char *filename);
	~DeformableObjectMesh(void);

	virtual void render();
	//virtual void update(f32 timeElapsed);

	SimpleMesh *mesh;
	f32 pickingRadiusSquared;

};

}

#endif

