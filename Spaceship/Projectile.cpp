#include "pch.h"
#include "Projectile.h"


std::shared_ptr<DirectX::GeometricPrimitive> Projectile::mRenderObjectAsset{ nullptr };

Projectile::Projectile(const DirectX::SimpleMath::Vector3& newLocation, World* world)
	:GameObject(newLocation, world)
{
	mRenderObject = mRenderObjectAsset;

	SetScale(DirectX::SimpleMath::Vector3(0.4f, 0.6f, 0.5f));
	mRenderObjectColor = DirectX::Colors::Red;

	mVelocity = 5.f;
}

Projectile::~Projectile()
{
}

void Projectile::Init(ID3D11DeviceContext * deviceContext)
{
	mRenderObjectAsset = DirectX::GeometricPrimitive::CreateSphere(deviceContext);
}

void Projectile::OnCollision(const GameObject & otherObject)
{
	Destroy();
}

void Projectile::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	Move(DirectX::SimpleMath::Vector3(0.f, mVelocity * deltaTime, 0.f));
}
