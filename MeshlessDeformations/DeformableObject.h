#if !defined(DeformableObject_h)
#define DeformableObject_h

#include <irrlicht.h>
#include "Globals.h"
#include "ModelObject.h"
#include "Particle.h"
#include "matrix/newmat.h"



using namespace irr;
using namespace core;


namespace Model
{

	class DeformableObject : public ModelObject
	{
		

		public:

			//PROPERTIES
			vector3df originalCentreOfMass;
			vector3df currentCentreOfMass;
			f32 alpha;
			f32 beta;
			f32 elasticity;
			core::stringw name;


			//CONSTRUCTOR
			DeformableObject(core::stringw name);

			//METHODS
			void addParticle(Particle* particle);
			array<Particle*> getParticles(void);

			// updates the position of this particle
			void updateGoalPositions(f32 timeElapsed);
			virtual void update(f32 timeElapsed);
			// calculate A_pq
			matrix4 calculateA_pqMatrix();
			matrix4 calculateRotationMatrix(matrix4 A_pq);

			array<Particle*> particles;

			bool isSelected;
			virtual void setVisible(bool isVisible);

		private:
			bool finished;
			array<vector3df> q;
			array<vector3df> p;
			matrix4 A_qq;

			// quadratic deformation
			array<ColumnVector> q_tilde;
			array<ColumnVector> p_tilde;
			SquareMatrix A_tilde_qq;

			void updateCurrentCenterOfMass();
			void doInitialCalculations();
	};
}


#endif // end if!defined for this header
