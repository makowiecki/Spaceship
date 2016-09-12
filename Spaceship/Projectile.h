#pragma once
#include "GameObject.h"

class Projectile: public GameObject
{
public:
	/** Creates Projectile at newLocation in world. Initialize defaults:
	*	scale
	*	color
	*	velocity
	*	
	*	Assign RenderObjectAsset to RenderObject. So static Init() must be called earlier.
	*/
	Projectile(const DirectX::SimpleMath::Vector3& newLocation, World* world);

	/** Empty */
	virtual ~Projectile();

	/** Creates RenderObjectAsset (must be called befor any contructor */
	static void Init(ID3D11DeviceContext* deviceContext);

	/** Handles collision with other object. Always gets destroyed */
	virtual void OnCollision(const GameObject& otherObject)override;

	/** Updates object state. Move object using velocity (always up) */
	virtual void Update(float deltaTime)override;
	
private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset; // asset used in all Projectile object to Render it
};

