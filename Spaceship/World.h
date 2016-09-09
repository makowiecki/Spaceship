#pragma once

#include <vector>

#include "GameObject.h"
#include "MeteorsManager.h"

class World
{
public:
	World();
	~World();

	void init();
	
	void onMeteorDestroyed();

	void reset();

	void handleCollisions();

	void update(float deltaTime);

	void renderObjects(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void removeDestryedObjects();

	template<typename Type>
	GameObject* spawnObject(const DirectX::SimpleMath::Vector3& newLocation);

private:

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	using GameObjectsValueType = std::vector<std::unique_ptr<GameObject>>::value_type;

	MeteorsManager mMeteorsManager;

	bool bIsSetToReset;
};

template<typename Type>
inline GameObject * World::spawnObject(const DirectX::SimpleMath::Vector3& newLocation)
{
	std::unique_ptr<GameObject> newObject = std::make_unique<Type>(newLocation, this);

	mGameObjects.push_back(std::move(newObject));
	return mGameObjects.back().get();
}
