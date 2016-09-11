#pragma once
#include "GameObject.h"

class Projectile: public GameObject
{
public:
	Projectile(const DirectX::SimpleMath::Vector3& newLocation, World* world);
	virtual ~Projectile();

	static void Init(ID3D11DeviceContext* deviceContext);

	virtual void OnCollision(const GameObject& otherObject)override;

	virtual void Update(float deltaTime)override;
	
private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset;
};

