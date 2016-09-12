#pragma once

class World;

class GameObject
{
public:
	GameObject(const DirectX::SimpleMath::Vector3& newLocation, World* world);
	virtual ~GameObject();

	void SetLocation(const DirectX::SimpleMath::Vector3& newLocation);
	void Move(const DirectX::SimpleMath::Vector3& offSet);
	const DirectX::SimpleMath::Vector3& GetLocation()const;

	void SetRotation(const DirectX::SimpleMath::Vector3& newRotation);
	void Rotate(const DirectX::SimpleMath::Vector3& rotation);
	const DirectX::SimpleMath::Vector3& GetRotation()const;

	void SetScale(const DirectX::SimpleMath::Vector3& newScale);
	void AddScale(const DirectX::SimpleMath::Vector3& addedScale);
	const DirectX::SimpleMath::Vector3& GetScale()const;
	
	World* GetWorld()const;

	void Destroy();
	bool IsDestroyed()const;

	void SetVelocity(float newVelocity);
	void AddVelocity(float value);
	float GetVelocity()const;

	void SetInstigator(GameObject &instigator);

	bool Collide(const GameObject& object);

	virtual void OnCollision(const GameObject& otherObject);
	virtual void OnDestroy();

	virtual void Update(float deltaTime)=0;
	
	virtual void Render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
		
protected:

	DirectX::SimpleMath::Color mRenderObjectColor;

	DirectX::SimpleMath::Vector2 mScreenPosition;

	bool mDestroyed;

	bool mDestroyOffTheScreen;

	float mVelocity;

	GameObject *mInstigator;

	std::shared_ptr<DirectX::GeometricPrimitive> mRenderObject;
	
private:

	DirectX::SimpleMath::Vector3 mLocation;
	DirectX::SimpleMath::Vector3 mRotation;
	DirectX::SimpleMath::Vector3 mScale;

	DirectX::BoundingOrientedBox mCollisionBox;

	World* mReferenceToWorld;
};

