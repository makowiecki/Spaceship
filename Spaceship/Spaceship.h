#pragma once
#include "GameObject.h"

#include <functional>

class Spaceship: public GameObject
{
public:
	/** Creates Spaceship at newLocation in world. Initialize defaults:
	*	projectileSpawnOffset
	*	shootTimer
	*	scale
	*	destroy OffTheScreen to false
	*	velocity
	*	projectileSpeed
	*	shotRate
	*	binds functions to InputManager actions
	*	
	*	Assign RenderObjectAsset to RenderObject. So static Init() must be called earlier.
	*/
	Spaceship(const DirectX::SimpleMath::Vector3& newLocation, World* world);

	/** Empty */
	virtual ~Spaceship();

	/** Moves spaceship to right (using velocity) and blocks movement if it reaches screen border */
	void MoveRight(float deltaTime);

	/** Moves spaceship to left (using velocity) and blocks movement if it reaches screen border */
	void MoveLeft(float deltaTime);

	/** If time from last shoot is greater then 1.shotRate spawns Projectile using mProjectileSpawnOffset */
	void ShootProjectile(float deltaTime);

	/** Assign funtion that will be called to get current destroyed meteors */
	void SetGetMeteorsDestroyedFunction(const std::function<int()>& function);

	/** Creates RenderObjectAsset (must be called befor any contructor */
	static void Init(ID3D11DeviceContext* deviceContext, ID3D11Device* device);

	/** Handles collision with other object. Always reset world */
	virtual void OnCollision(const GameObject& otherObject)override;

	/** Updates object state. */
	void Update(float deltaTime)override;

	/** Render object , also draw string below spaceship with number of destroyed meteors */
	virtual void Render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)override;

protected:

	float mProjectileSpeed; // will be assigned to projection on its spawn
	int mShotRate; // projectiles per second

	float mProjectileSpawnOffset; // offet from spaceship location where Projectile will be spawn

	float mShootTimer; // timer to keep keep in track shot rate

	std::function<int()> mGetDestroyedMeteors; // function that will be called to get current destroyed meteors

	static std::unique_ptr<DirectX::SpriteFont> mFont; // font used to draw current destroyed meteors number
	static std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch; // SpriteBatch used to draw current destroyed meteors number

private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset; // asset used in all Spaceship object to Render it
};

