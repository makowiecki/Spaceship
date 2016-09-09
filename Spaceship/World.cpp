#include "pch.h"
#include "World.h"

#include "GameplayHelpers.h"
#include "Spaceship.h"


World::World()
	:mMeteorsManager(this)
{
}

World::~World()
{
}

void World::init()
{
	mGameObjects.clear();

	DirectX::SimpleMath::Vector3 screenCenterLocation = GameplayHelpers::unprojectOnScreen(DirectX::SimpleMath::Vector2(GameplayHelpers::getViewportSize().x / 2, 40.f));
	screenCenterLocation.z = 0.f;

	Spaceship* spaceShip = dynamic_cast<Spaceship*>(spawnObject<Spaceship>(screenCenterLocation));

	if(spaceShip)
	{
		spaceShip->setGetMeteorsDestroyedFunction(std::bind(&MeteorsManager::getDestroyedMeteorsNumber, &mMeteorsManager));
	}

	mMeteorsManager.reset();

	bIsSetToReset = false;
}

void World::onMeteorDestroyed()
{
	mMeteorsManager.meteorDestroyed();
}

void World::reset()
{
	bIsSetToReset = true;
}

void World::handleCollisions()
{
	for(size_t i = 0; i < mGameObjects.size(); i++)
	{
		for(size_t j = i + 1; j < mGameObjects.size(); j++)
		{
			if(mGameObjects[i]->collide(*mGameObjects[j]))
			{
				mGameObjects[i]->onHit(*mGameObjects[j]);
				mGameObjects[j]->onHit(*mGameObjects[i]);
			}
		}
	}
}

void World::update(float deltaTime)
{
	mMeteorsManager.update(deltaTime);

	for(const GameObjectsValueType& object : mGameObjects)
	{
		object->update(deltaTime);
	}

	handleCollisions();

	if(bIsSetToReset)
	{
		init();
	}
}

void World::renderObjects(const DirectX::SimpleMath::Matrix & world, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection)
{
	for(const GameObjectsValueType& object : mGameObjects)
	{
		object->render(world, view, projection);
	}
}

void World::removeDestryedObjects()
{
	std::vector<std::unique_ptr<GameObject>>::iterator newEnd = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::bind(&GameObject::isDestroyed, std::placeholders::_1));
	if(newEnd != mGameObjects.end())
	{
		mGameObjects.erase(newEnd, mGameObjects.end());
	}
}
