#pragma once

class World;

class GameObject
{
public:
	GameObject(const DirectX::SimpleMath::Vector3& newLocation, World* world);
	virtual ~GameObject();

	void setLocation(const DirectX::SimpleMath::Vector3& newLocation);
	void move(const DirectX::SimpleMath::Vector3& offset);
	const DirectX::SimpleMath::Vector3& getLocation()const;

	void setRotation(const DirectX::SimpleMath::Vector3& newRotation);
	void rotate(const DirectX::SimpleMath::Vector3& rotation);
	const DirectX::SimpleMath::Vector3& getRotation()const;

	void setScale(const DirectX::SimpleMath::Vector3& newScale);
	void addScale(const DirectX::SimpleMath::Vector3& addedScale);
	const DirectX::SimpleMath::Vector3& getScale()const;
	
	World* getWorld()const;

	void destroy();
	bool isDestroyed()const;

	void setVelocity(float newVelocity);
	void addVelocity(float value);
	float getVelocity()const;

	void setInstigator(GameObject &instigator);

	bool collide(const GameObject& object);

	virtual void onHit(const GameObject& otherObject);
	virtual void onDestroy();

	virtual void update(float deltaTime)=0;
	
	virtual void render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	
protected:

	DirectX::SimpleMath::Vector3 mLocation;
	DirectX::SimpleMath::Vector3 mRotation;
	DirectX::SimpleMath::Vector3 mScale;

	DirectX::SimpleMath::Color mRenderObjectColor;

	DirectX::SimpleMath::Vector2 mScreenPosition;

	bool mDestroyed;

	bool mDestroyOffTheScreen;

	float mVelocity;

	GameObject *mInstigator;

	RenderData mRenderData;

	std::shared_ptr<DirectX::GeometricPrimitive> mRenderObject;
	DirectX::BoundingSphere mCollisionSphere;
	
private:

	World* mReferenceToWorld;
};

