#include "Globals.h"


irr::core::matrix4 volumeNormalize(irr::core::matrix4 A) {

	Matrix A_calc(3,3);
	for(int j=0;j<3;j++) {
		for(int i=0;i<3;i++) { 
			A_calc.element(j,i) = A(i,j);
		}
	}

	double det = Determinant(A_calc);
	double cbrt = pow( fabs(det), 1./3 );
	cbrt = ( det < 0 ) ? -cbrt : cbrt; 
	A_calc = A_calc / cbrt;

	for(int j=0;j<3;j++) {
		for(int i=0;i<3;i++) {
			A(i,j) = A_calc.element(j,i);
		}
	}

	return A;
}

irr::core::matrix4 sqrt(irr::core::matrix4 A) {

//1- [E D] = eig(A); sqrtm(A) = E * sqrt(D) * E' where D is a diagonal matrix.
//> sqrt(D) is formed by taking the square root of the diagonal entries in D.


	SymmetricMatrix M(3);
	DiagonalMatrix D(3);
	Matrix E(3,3);

	for(int j=0;j<3;j++) {
		for(int i=j;i<3;i++) { 
			M.element(j,i) = A(i,j);
		}
	}

	Jacobi(M,D,E);

	for(int i=0;i<3;i++)
		D.element(i,i) = sqrt(D.element(i,i));

	Matrix S = E * D * E.t() ; 

	for(int j=0;j<3;j++) {
		for(int i=0;i<3;i++) {
			A(i,j) = S.element(j,i);
			//std::cout << "i:" << i << ",j:" << j << " > " << A(j,i) ;
		}
		//std::cout << std::endl;
	}
	return A;
}

// reflection with normal  
core::vector3df getReflected( core::vector3df vector, core::vector3df normal ) { 
	f32 length = (f32)vector.getLength();
	vector.normalize();
	normal.normalize(); 
	
	return (vector - normal * 2.0f * (vector.dotProduct( normal))) * length; 
}

scene::ISceneManager* Globals::sceneManager = 0;

video::IVideoDriver* Globals::driver = 0;
f32 Globals::gravity = 0.7f;f32 Globals::drag = 0.005f;f32 Globals::timeElapsed = 0.0f;bool Globals::drawGoalPositions = true;
bool Globals::stopMode = false;
bool Globals::useShadows = false;

DeformationMode::DeformationMode Globals::mode = DeformationMode::Basic;

Model::DeformableObject* Globals::selectedObject = 0;
core::array<Model::DeformableObject*> Globals::objects = core::array<Model::DeformableObject*>();

IrrlichtDevice* Globals::device = 0;

scene::ICameraSceneNode* Globals::camera = 0;

Model::Boundary* Globals::boundary = 0;

void Globals::init(IrrlichtDevice* device) {
	Globals::device = device;
	sceneManager= device->getSceneManager();
	camera = sceneManager->getActiveCamera();
	driver =device->getVideoDriver();
}

Globals::Globals() {
}
