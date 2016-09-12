#pragma once

#include <vector>

#include "GameObject.h"
#include "MeteorsManager.h"

class World
{
public:
	/** Only creates MeteorManager. Init must be called to properly construct World */
	World();

	/** Empty */
	~World();

	/** Creates Spaceship abd reset meteorManager */
	void Init();
	
	/** Should be called when meteor is destroyed */
	void OnMeteorDestroyed();

	/** Restet world (set flag, accual reset should be done at the end of update)*/
	void Reset();

	/** Check collision every gameObject in this world */
	void HandleCollisions();

	/** Update meteorManager, all gameObjects, handleCollisions and if flag set, reset world */
	void Update(float deltaTime);

	/** Render all gameObject in this world */
	void RenderObjects(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	/** Accual object destruction (remove from world) */
	void RemoveDestryedObjects();

	/** Spawn different type of GameObject and add it to this world */
	template<typename Type>
	GameObject* SpawnObject(const DirectX::SimpleMath::Vector3& newLocation);

private:

	std::vector<std::unique_ptr<GameObject>> mGameObjects; // hold every game object in this world
	using mGameObjectsValueType = std::vector<std::unique_ptr<GameObject>>::value_type; // useful alias for vector value type

	MeteorsManager mMeteorsManager; // meteor manager used to spawn meteors

	bool mIsSetToReset; // flag indicating wheater this world was set to be rest or not
};

template<typename Type>
inline GameObject * World::SpawnObject(const DirectX::SimpleMath::Vector3& newLocation)
{
	std::unique_ptr<GameObject> newObject = std::make_unique<Type>(newLocation, this);

	mGameObjects.push_back(std::move(newObject));
	return mGameObjects.back().get();
}
