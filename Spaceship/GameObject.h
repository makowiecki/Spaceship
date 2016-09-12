#pragma once

class World;

/** Base class for all objects on screen. Contains data for rendering, collisions and basic behaivor */
class GameObject
{
public:
	/** Creates GameObject at newLocation in world. Initialize defaults:
	*	no velocity
	*	object is destroyed when goes off screen
	*	no instigator
	*	no rotation and 1.f scale on all axes 
	*	white color
	*/
	GameObject(const DirectX::SimpleMath::Vector3& newLocation, World* world);

	/** Empty */
	virtual ~GameObject();

	/** Set current object and collsion box locations */
	void SetLocation(const DirectX::SimpleMath::Vector3& newLocation);

	/** Move object and collsion box locations by offset */
	void Move(const DirectX::SimpleMath::Vector3& offSet);

	/** Return current object location */
	const DirectX::SimpleMath::Vector3& GetLocation()const;

	/** Set current object and collsion box rotation (in degrees) */
	void SetRotation(const DirectX::SimpleMath::Vector3& newRotation);

	/** Rotate object and collsion box by rotation vector (in degrees) */
	void Rotate(const DirectX::SimpleMath::Vector3& rotation);
	
	/** Return current object rotation (in degrees) */
	const DirectX::SimpleMath::Vector3& GetRotation()const;

	/** Set current object and collsion box scale */
	void SetScale(const DirectX::SimpleMath::Vector3& newScale);

	/** Add addedScale to object and collision box scale */
	void AddScale(const DirectX::SimpleMath::Vector3& addedScale);

	/** Return current object scale */
	const DirectX::SimpleMath::Vector3& GetScale()const;
	
	/** Return pointer to world in which the object was spawned */
	World* GetWorld()const;

	/** Destroy object and call OnDestroy() function */
	void Destroy();

	/** Check if object was set to be destroyed */
	bool IsDestroyed()const;

	/** Set objects new velocity */
	void SetVelocity(float newVelocity);

	/** Add value to objects currnet velocity */
	void AddVelocity(float value);

	/** Return object current velocity */
	float GetVelocity()const;
	
	/** Set object instigator, object won't collide with its instigator (should be called on spawn) */
	void SetInstigator(GameObject &instigator);

	/** Check collision with other object (using collision box) */
	bool Collide(const GameObject& object);

	/** Should be called when collision occur */
	virtual void OnCollision(const GameObject& otherObject);

	/** Called when Destroy() cunction ends */
	virtual void OnDestroy();

	/** Updates object state. Destroy object of ot goues out off screen and mDestroyOffTheScreen is true (must be called from child classes) */
	virtual void Update(float deltaTime)=0;
	
	/** Render object  (must be called from child classes) */
	virtual void Render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
		
protected:

	DirectX::SimpleMath::Color mRenderObjectColor; // Color used in Render function

	DirectX::SimpleMath::Vector2 mScreenPosition; // Object scrreen position calculated in Update function

	bool mDestroyed; // flag indicating if object was set to be destroyed

	bool mDestroyOffTheScreen; // flag indicating if object must be destroyed of it goes out off screen

	float mVelocity; // current object velocity

	GameObject *mInstigator; // object instigator

	std::shared_ptr<DirectX::GeometricPrimitive> mRenderObject; // render object used in Render function
	
private:

	DirectX::SimpleMath::Vector3 mLocation; // current actor location
	DirectX::SimpleMath::Vector3 mRotation; // current actor rotation
	DirectX::SimpleMath::Vector3 mScale; // current actor scale

	DirectX::BoundingOrientedBox mCollisionBox; // object collsion box

	World* mReferenceToWorld; // reference to world where actor was created
};

