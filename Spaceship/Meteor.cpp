#include "pch.h"
#include "Meteor.h"

#include "World.h"

std::shared_ptr<DirectX::GeometricPrimitive> Meteor::mRenderObjectAsset{ nullptr };

Meteor::Meteor(const DirectX::SimpleMath::Vector3& newLocation, World *world)
	:GameObject(newLocation, world),
	mDirectionDeviation(0.35f),
	mVelocityDeviation(1.f)
{
	mRenderObject = mRenderObjectAsset;
		
	float randSize = Random::GetRandom(0.75f, 2.f);
	float lowerBound = randSize - 0.45f;
	float upperBound = randSize + 0.45f;
	mScale = DirectX::SimpleMath::Vector3(Random::GetRandom(lowerBound, upperBound), Random::GetRandom(lowerBound, upperBound), Random::GetRandom(lowerBound, upperBound));

	mRotation = DirectX::SimpleMath::Vector3(Random::GetRandom(0.25f, 360.f), Random::GetRandom(0.25f, 360.f), Random::GetRandom(0.25f, 360.f));

	mRenderObjectColor = DirectX::Colors::RosyBrown;

	mCollisionSphere.Center = mLocation;
	mCollisionSphere.Radius = mScale.x / 2; // because size is from left to right and radius is from center

	mVelocity = 3.f;
	mVelocity += Random::GetRandom(-mVelocityDeviation, mVelocityDeviation);

	mDirectionVector = DirectX::SimpleMath::Vector3(Random::GetRandom(-mDirectionDeviation, mDirectionDeviation), -mVelocity, 0.f);
	mInitRotation =  DirectX::SimpleMath::Vector3(Random::GetRandom(0.25f, 36.f), Random::GetRandom(0.25f, 36.f), Random::GetRandom(0.25f, 36.f));
}

Meteor::~Meteor()
{
}

void Meteor::Init(ID3D11DeviceContext * deviceContext)
{
	mRenderObjectAsset = DirectX::GeometricPrimitive::CreateCube(deviceContext, 1.f);
}

void Meteor::OnCollision(const GameObject & otherObject)
{
	const Meteor *otherMeteor = dynamic_cast<const Meteor*>(&otherObject);

	if(!otherMeteor)
	{
		GetWorld()->OnMeteorDestroyed();
		Destroy();
	}
	else // bounce if hit other meteor
	{

	}
}

void Meteor::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	Move(mDirectionVector * deltaTime);
	Rotate(mInitRotation * deltaTime);
}
