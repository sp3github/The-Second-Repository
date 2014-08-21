#include "DM2231_Model.h"

DM2231_Model::DM2231_Model(void)
{
}

DM2231_Model::~DM2231_Model(void)
{
}

// Update the model
void DM2231_Model::Update(void)
{
	Vector3D<float> MouseVector(theMouseInfo.MousePos);
	//Vector3D<float> HeroVector(theHero.GetX(),theHero.GetY());

	for(auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
	{
		CEntity *go = (*it);
		cout<<"ENTITY X:"<<go->GetX()<<" Y: "<<go->GetY()<<endl;
	}

	//float difVec = MouseVector.Dot(HeroVector);
	//float Scalar = difVec / MouseVector.Magnitude() * HeroVector.Magnitude();
	//theHero.HeroRotation = acos(Scalar); 

	//cout<<"The Rotation"<<theHero.HeroRotation<<endl;
}
