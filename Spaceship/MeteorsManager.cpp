#include "pch.h"
#include "MeteorsManager.h"

#include "GameplayHelpers.h"
#include "Random.h"

#include "Meteor.h"
#include "World.h"

MeteorsManager::MeteorsManager(World *world)
	:mWorldReference(world)
{
	reset();
}


MeteorsManager::~MeteorsManager()
{
}

World * MeteorsManager::getWorld() const
{
	return mWorldReference;
}

void MeteorsManager::meteorDestroyed()
{
	++mDestroyedMeteorsCounter;

	recalculateSpawnRate();
}

int MeteorsManager::getDestroyedMeteorsNumber() const
{
	return mDestroyedMeteorsCounter;
}

void MeteorsManager::reset()
{
	mDestroyedMeteorsCounter = 0;
	mCreatedMeteorsCounter = 0;
	mMeteorsSpawnRate = 1;
	mSpawnTimer = 0.f;
}

void MeteorsManager::update(float deltaTime)
{
	mSpawnTimer += deltaTime;

	if(mSpawnTimer > 1.f / mMeteorsSpawnRate)
	{
		spawnMeteor();
		mSpawnTimer = 0.f;
	}
}

void MeteorsManager::spawnMeteor()
{
	using namespace DirectX::SimpleMath;

	float randomX = Random::getRandom(50.f, GameplayHelpers::getViewportSize().x - 50.f);
	Vector3 meteorLocation = GameplayHelpers::unprojectOnScreen(Vector2(randomX, GameplayHelpers::getViewportSize().y - 10.f));
	meteorLocation.z = 0.f;

	getWorld()->spawnObject<Meteor>(meteorLocation);

	++mCreatedMeteorsCounter;
}

void MeteorsManager::recalculateSpawnRate()
{
	mMeteorsSpawnRate = static_cast<int>(std::log(mDestroyedMeteorsCounter) / std::log(1.5f));

	mMeteorsSpawnRate = mMeteorsSpawnRate > 0 ? mMeteorsSpawnRate : 1;
}
