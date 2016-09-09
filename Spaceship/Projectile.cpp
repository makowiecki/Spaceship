#include "pch.h"
#include "Projectile.h"


std::shared_ptr<DirectX::GeometricPrimitive> Projectile::mRenderObjectAsset{ nullptr };

Projectile::Projectile(const DirectX::SimpleMath::Vector3& newLocation, World* world)
	:GameObject(newLocation, world)
{
	mRenderObject = mRenderObjectAsset;

	mScale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);
	mRenderObjectColor = DirectX::Colors::Red;

	mCollisionSphere.Center = mLocation;
	mCollisionSphere.Radius = mScale.x / 2; // div by 2 because in creatin is diameter

	mVelocity = 5.f;
}


Projectile::~Projectile()
{
}

void Projectile::init(ID3D11DeviceContext * deviceContext)
{
	mRenderObjectAsset = DirectX::GeometricPrimitive::CreateSphere(deviceContext);
}

void Projectile::onHit(const GameObject & otherObject)
{
	destroy();
}

void Projectile::update(float deltaTime)
{
	GameObject::update(deltaTime);

	move(DirectX::SimpleMath::Vector3(0.f, mVelocity * deltaTime, 0.f));
}