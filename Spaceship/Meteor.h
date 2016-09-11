#pragma once
#include "GameObject.h"

class Meteor: public GameObject
{
public:
	Meteor(const DirectX::SimpleMath::Vector3& newLocation, World *world);
	virtual ~Meteor();

	static void Init(ID3D11DeviceContext* deviceContext);

	virtual void OnCollision(const GameObject& otherObject)override;

	void Update(float deltaTime)override;

protected:

	DirectX::SimpleMath::Vector3 mDirectionVector;
	DirectX::SimpleMath::Vector3 mInitRotation; // degrees per second

	float mDirectionDeviation;
	float mVelocityDeviation;

private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset;
};

