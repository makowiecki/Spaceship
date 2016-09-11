#pragma once

#include <vector>

#include "GameObject.h"
#include "MeteorsManager.h"

class World
{
public:
	World();
	~World();

	void Init();
	
	void OnMeteorDestroyed();

	void Reset();

	void HandleCollisions();

	void Update(float deltaTime);

	void RenderObjects(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void RemoveDestryedObjects();

	template<typename Type>
	GameObject* SpawnObject(const DirectX::SimpleMath::Vector3& newLocation);

private:

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	using mGameObjectsValueType = std::vector<std::unique_ptr<GameObject>>::value_type;

	MeteorsManager mMeteorsManager;

	bool mIsSetToReset;
};

template<typename Type>
inline GameObject * World::SpawnObject(const DirectX::SimpleMath::Vector3& newLocation)
{
	std::unique_ptr<GameObject> newObject = std::make_unique<Type>(newLocation, this);

	mGameObjects.push_back(std::move(newObject));
	return mGameObjects.back().get();
}
