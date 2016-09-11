#pragma once
#include "GameObject.h"

#include <functional>

class Spaceship: public GameObject
{
public:
	Spaceship(const DirectX::SimpleMath::Vector3& newLocation, World* world);
	virtual ~Spaceship();

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void ShootProjectile(float deltaTime);

	void SetGetMeteorsDestroyedFunction(const std::function<int()>& function);

	static void Init(ID3D11DeviceContext* deviceContext, ID3D11Device* device);

	virtual void OnCollision(const GameObject& otherObject)override;

	void Update(float deltaTime)override;

	virtual void Render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)override;

protected:

	float mProjectileSpeed;
	int mShotRate; //projectiles per second

	float mProjectileSpawnOffset;

	float mShootTimer;

	std::function<int()> mGetDestroyedMeteors;

	static std::unique_ptr<DirectX::SpriteFont> mFont;
	static std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;

private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset;
};

