#pragma once
#include "GameObject.h"

class Meteor: public GameObject
{
public:
	/** Creates Meteor at newLocation in world. Initialize defaults:
	*	directionDeviation to 0.35f
	*	velocityDeviation to 1.f
	*	velocitybuff to 0
	*	random scale
	*	random init rotation and random start rotation
	*	random velocity using velocityDeviation
	*	random direction using directionDeviation and velocity
	*	color
	*	
	*	Assign RenderObjectAsset to RenderObject. So static Init() must be called earlier.
	*/
	Meteor(const DirectX::SimpleMath::Vector3& newLocation, World *world);

	/** Empty */
	virtual ~Meteor();

	/** Creates RenderObjectAsset (must be called befor any contructor */
	static void Init(ID3D11DeviceContext* deviceContext);

	/** Handles collision with other object. Adds velocity buff when collide with other Meteor otherwise gets destroyed */
	virtual void OnCollision(const GameObject& otherObject)override;

	/** Called when gets destroyed. Propagate it to world */
	virtual void OnDestroy()override;

	/** Updates object state. Move object using directionVector and rotate ot using initRotation */
	void Update(float deltaTime)override;

protected:

	DirectX::SimpleMath::Vector3 mDirectionVector; // current meteor direction (added to location on each update)
	DirectX::SimpleMath::Vector3 mInitRotation; // rotation added on each update (degrees per second)

	float mVelocityBuff; // holds current velocity buff (set in collision function when 2 Meteors collide)

	float mDirectionDeviation; // random direction X component will be from range [-mDirectionDeviation; mDirectionDeviation]
	float mVelocityDeviation; // random velocity will be from range [3.f-mVelocityDeviation; 3.f+mVelocityDeviation]

private:

	static std::shared_ptr<DirectX::GeometricPrimitive> mRenderObjectAsset; // asset used in all Meteor object to Render it
};

