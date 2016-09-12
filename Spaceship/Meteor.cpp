#include "pch.h"
#include "Meteor.h"

#include "World.h"

std::shared_ptr<DirectX::GeometricPrimitive> Meteor::mRenderObjectAsset{ nullptr };

Meteor::Meteor(const DirectX::SimpleMath::Vector3& newLocation, World *world)
	:GameObject(newLocation, world),
	mDirectionDeviation(0.35f),
	mVelocityDeviation(1.f),
	mVelocityBuff(0.f)
{
	mRenderObject = mRenderObjectAsset;
		
	const float randSize = Random::GetRandom(0.75f, 2.f);
	const float lowerBound = randSize - 0.45f;
	const float upperBound = randSize + 0.45f;
	SetScale(DirectX::SimpleMath::Vector3(Random::GetRandom(lowerBound, upperBound), Random::GetRandom(lowerBound, upperBound), Random::GetRandom(lowerBound, upperBound)));

	SetRotation(DirectX::SimpleMath::Vector3(Random::GetRandom(0.25f, 360.f), Random::GetRandom(0.25f, 360.f), Random::GetRandom(0.25f, 360.f)));

	mRenderObjectColor = DirectX::Colors::RosyBrown;

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
	GameObject::OnCollision(otherObject);

	const Meteor *otherMeteor = dynamic_cast<const Meteor*>(&otherObject);

	if(!otherMeteor)
	{
		Destroy();
	}
	else // move if collide by other meteor
	{
		const float thisLocationY = GetLocation().y;
		const float otherLocationY = otherObject.GetLocation().y;

		if(thisLocationY < otherLocationY) //this is below other
		{
			mVelocityBuff += 2.5f;
		}
	}
}

void Meteor::OnDestroy()
{
	GameObject::OnDestroy();

	GetWorld()->OnMeteorDestroyed();
}

void Meteor::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	mVelocityBuff -= 3.f * deltaTime; //for max 3 seconds (possibly a class property)
	mVelocityBuff = std::max(mVelocityBuff, 1.f); // min value (possibly a class property)
	mVelocityBuff = std::min(mVelocityBuff, 2.5f); // max value (possibly a class property)

	Move(mDirectionVector * deltaTime * mVelocityBuff);
	Rotate(mInitRotation * deltaTime);
}
