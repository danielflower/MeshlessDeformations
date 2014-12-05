#include "DeformableObject.h"
#include "Globals.h"
#include "matrix/newmat.h"
#include "matrix/newmatap.h"
#include "matrix/tmt.h"

using namespace Model;

//CONSTRUCTORS
DeformableObject::DeformableObject(core::stringw name) : ModelObject(ObjectType::DeformableObject)
{
	beta = 0.0f;
	alpha = 0.5f;
	elasticity = 0.5f;
	this->name = name;
	finished = false;
	isSelected = false;
}

void DeformableObject::doInitialCalculations() {
	// calculate centre of mass (t_0)
	vector3df tmpSum(0.0f,0.0f,0.0f);
	float tmpMass = 0.0f;
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* particle = particles[index];
		tmpSum += particle->originalPosition * particle->weight;
		tmpMass += particle->weight;
	}
	originalCentreOfMass = tmpSum / tmpMass;   

	// update q_i
	q.clear();
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* p = particles[index];
		q.push_back(p->originalPosition - originalCentreOfMass);
	}

	// calculate A_qq
	matrix4 A_qq_inverse;
	for(int i=0;i<(int)particles.size(); i++) {
		// m_i*p*q^T
		Particle *par = particles[i];
		f32 m = par->weight;
		A_qq_inverse(0,0)+=m*q[i].X*q[i].X; A_qq_inverse(1,0)+=m*q[i].X*q[i].Y; A_qq_inverse(2,0)+=m*q[i].X*q[i].Z;
		A_qq_inverse(0,1)+=m*q[i].Y*q[i].X; A_qq_inverse(1,1)+=m*q[i].Y*q[i].Y; A_qq_inverse(2,1)+=m*q[i].Y*q[i].Z;
		A_qq_inverse(0,2)+=m*q[i].Z*q[i].X; A_qq_inverse(1,2)+=m*q[i].Z*q[i].Y; A_qq_inverse(2,2)+=m*q[i].Z*q[i].Z;
	}
	A_qq_inverse.getInverse(A_qq);

	// update q_tilde_i
	q_tilde.clear();
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* p = particles[index];
		ColumnVector t(9);
		t.element(0) = q[index].X;
		t.element(1) = q[index].Y;
		t.element(2) = q[index].Z;
		t.element(3) = q[index].X * q[index].X;
		t.element(4) = q[index].Y * q[index].Y;
		t.element(5) = q[index].Z * q[index].Z;
		t.element(6) = q[index].X * q[index].Y;
		t.element(7) = q[index].Y * q[index].Z;
		t.element(8) = q[index].Z * q[index].X;
		q_tilde.push_back(t);
	}

	// calculate A_tilde_qq
	SquareMatrix A_tilde_qq_inverse(9);
	A_tilde_qq_inverse = 0.0;
	for (u32 index = 0; index < particles.size(); index++) {
		A_tilde_qq_inverse += q_tilde[index] * q_tilde[index].t();
	}

	A_tilde_qq = SquareMatrix(9);
	A_tilde_qq = 0.0;
	try {
        A_tilde_qq = A_tilde_qq_inverse.i();
	}catch (SingularException) {
		A_tilde_qq = IdentityMatrix(9);
	}
}

void DeformableObject::addParticle(Particle* particle) {
	int nr = particles.size();
	particles.push_back( particle );
	particle->nr = nr;
	finished = false;
}

array<Particle*> DeformableObject::getParticles(void) {
	return particles;
}

matrix4 DeformableObject::calculateA_pqMatrix()
{
	matrix4 A_pq;
	for(int i=0;i<(int)particles.size(); i++) {
		// m_i*p*q^T
		Particle *par = particles[i];
		f32 m = par->weight;
		A_pq(0,0)+=m*p[i].X*q[i].X; A_pq(1,0)+=m*p[i].X*q[i].Y; A_pq(2,0)+=m*p[i].X*q[i].Z;
		A_pq(0,1)+=m*p[i].Y*q[i].X; A_pq(1,1)+=m*p[i].Y*q[i].Y; A_pq(2,1)+=m*p[i].Y*q[i].Z;
		A_pq(0,2)+=m*p[i].Z*q[i].X; A_pq(1,2)+=m*p[i].Z*q[i].Y; A_pq(2,2)+=m*p[i].Z*q[i].Z;
	}
	return A_pq.getTransposed();
}

matrix4 DeformableObject::calculateRotationMatrix(matrix4 A_pq)
{
	try {
		// sqrt() wrapped for matrix4 in globals.cpp
		matrix4 S = sqrt(A_pq.getTransposed() * A_pq);

		matrix4 Sinverse;
		if(S.getInverse(Sinverse) == false)
			std::cout << "no inverse for S" << std::endl;

		return A_pq * Sinverse;

	} catch(ConvergenceException) {
		return matrix4();
	}
}

void DeformableObject::updateGoalPositions(f32 timeElapsed) {

	// calc roofPosition only based on external forces 
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* par = particles[index];
		par->velocityRoof = par->velocity + par->getForces() * timeElapsed;
		par->roofPosition = par->position + par->velocityRoof * timeElapsed ;
	}	

	vector3df tmpSum(0.0f,0.0f,0.0f);
	float tmpMass = 0.0f;
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* par = particles[index];
		tmpSum += par->roofPosition * par->weight;
		tmpMass += par->weight;
	}
	currentCentreOfMass = tmpSum / tmpMass;

	// update p_i
	p.clear();
	for (u32 index = 0; index < particles.size(); index++) {
		Particle* par = particles[index];
		p.push_back(par->roofPosition - currentCentreOfMass);
	}

	if (Globals::mode == DeformationMode::Basic) {
		// 1. Rigid Body Dynamics 
		matrix4 A_pq = calculateA_pqMatrix();
		matrix4 R = calculateRotationMatrix(A_pq);

		// calculate goal positions and integrate
		for (u32 i = 0; i < particles.size(); i++) {
			vector3df goalPosition = q[i];
			R.rotateVect(goalPosition);
			goalPosition = goalPosition + currentCentreOfMass;

			if(particles[i]->canMoveTo(goalPosition)) { 
				particles[i]->goalPosition = goalPosition;
			}
		}
	} else if (Globals::mode == DeformationMode::Linear) {
		// 2. Linear Deformations
		matrix4 A_pq = calculateA_pqMatrix();
		matrix4 R = calculateRotationMatrix(A_pq);
		matrix4 A = volumeNormalize(A_pq * A_qq);
		matrix4 Transform;
		for (int i=0; i<16; i++) {
			A.M[i] *= beta;
			R.M[i] *= (1-beta);
			Transform.M[i] = R.M[i] + A.M[i];
		}

		// calculate goal positions and integrate
		for (u32 i = 0; i < particles.size(); i++) {
			vector3df goalPosition = q[i];
			Transform.rotateVect(goalPosition);
			goalPosition = goalPosition + currentCentreOfMass;

			if(particles[i]->canMoveTo(goalPosition)) { 
				particles[i]->goalPosition = goalPosition;
			}
		}
	} else if (Globals::mode == DeformationMode::Quadratic) {
		// 3. Quadratic deformation
		Matrix T_tilde = Matrix(3,9); T_tilde = 0.0;

		p_tilde.clear();
		for (u32 index = 0; index < particles.size(); index++) {
			Particle* par = particles[index];
			ColumnVector t(3);
			t.element(0) = par->roofPosition.X - currentCentreOfMass.X;
			t.element(1) = par->roofPosition.Y - currentCentreOfMass.Y;
			t.element(2) = par->roofPosition.Z - currentCentreOfMass.Z;
			p_tilde.push_back(t);
		}
		Matrix A_tilde_pq(3, 9);
		A_tilde_pq = 0.0;
		for (u32 index = 0; index < particles.size(); index++) {
			A_tilde_pq += p_tilde[index] * q_tilde[index].t();
		}
		Matrix A_tilde(3, 9);
		A_tilde = 0.0;
		A_tilde = (A_tilde_pq * A_tilde_qq);


		Matrix A_tilde_square(9, 9);
		A_tilde_square = IdentityMatrix(9);
		for(int j=0;j<3;j++) {
			for(int i=0;i<9;i++) { 
				A_tilde_square.element(j, i) = A_tilde.element(j, i);
			}
		}
		double det = Determinant(A_tilde_square);
		double cbrt = pow( fabs(det), 1.0/9.0 );
		cbrt = ( det < 0 ) ? -cbrt : cbrt;
		A_tilde = A_tilde / cbrt;

		matrix4 A_pq = calculateA_pqMatrix();
		matrix4 R = calculateRotationMatrix(A_pq);
		Matrix R_tilde = Matrix(3,9);
		R_tilde = 0.0;
		for(int j=0;j<3;j++) {
			for(int i=0;i<3;i++) { 
				R_tilde.element(j, i) = R(j, i);
			}
		}
		matrix4 A = volumeNormalize(A_pq * A_qq);
		T_tilde = beta * A_tilde + (1-beta) * R_tilde;

		// calculate goal positions and integrate
		for (u32 i = 0; i < particles.size(); i++) {
			ColumnVector goalN(3);
			goalN = T_tilde * q_tilde[i];
			vector3df goalPosition = vector3df(goalN.element(0), goalN.element(1), goalN.element(2))  + currentCentreOfMass;
			
			if(particles[i]->canMoveTo(goalPosition)) { 
				particles[i]->goalPosition = goalPosition;
			}
		}
	}
}

void DeformableObject::update(f32 timeElapsed) {

	if(!finished) {
		doInitialCalculations();
		finished = true;
	}

	updateGoalPositions(timeElapsed);

	for (u32 i = 0; i < particles.size(); i++) {
		Particle* particle = particles [i];
		if (!Globals::stopMode) {
			particle->update(timeElapsed);
		}
	}
}

void DeformableObject::setVisible(bool isVisible){
	ISceneNode::setVisible(isVisible);

	for (u32 i = 0; i < particles.size(); i++) {
		Particle* particle = particles [i];
		if (isVisible) {
			particle->setID(particle->getID() | ObjectType::SelectableObject);
		} else {
			particle->setID(particle->getID() ^ ObjectType::SelectableObject);
		}
	}
		
}