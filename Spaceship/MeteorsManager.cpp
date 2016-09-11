#include "pch.h"
#include "MeteorsManager.h"

#include "Meteor.h"
#include "World.h"

MeteorsManager::MeteorsManager(World *world)
	:mWorldReference(world)
{
	Reset();
}


MeteorsManager::~MeteorsManager()
{
}

World * MeteorsManager::GetWorld() const
{
	return mWorldReference;
}

void MeteorsManager::MeteorDestroyed()
{
	++mDestroyedMeteorsCounter;

	RecalculateSpawnRate();
}

int MeteorsManager::GetDestroyedMeteorsNumber() const
{
	return mDestroyedMeteorsCounter;
}

void MeteorsManager::Reset()
{
	mDestroyedMeteorsCounter = 0;
	mCreatedMeteorsCounter = 0;
	mMeteorsSpawnRate = 1;
	mSpawnTimer = 0.f;
}

void MeteorsManager::Update(float deltaTime)
{
	mSpawnTimer += deltaTime;

	if(mSpawnTimer > 1.f / mMeteorsSpawnRate)
	{
		SpawnMeteor();
		mSpawnTimer = 0.f;
	}
}

void MeteorsManager::SpawnMeteor()
{
	using namespace DirectX::SimpleMath;

	float randomX = Random::GetRandom(50.f, GameplayHelpers::GetViewportSize().x - 50.f);
	Vector3 meteorLocation = GameplayHelpers::UnprojectOnScreen(Vector2(randomX, GameplayHelpers::GetViewportSize().y - 10.f));
	meteorLocation.z = 0.f;

	GetWorld()->SpawnObject<Meteor>(meteorLocation);

	++mCreatedMeteorsCounter;
}

void MeteorsManager::RecalculateSpawnRate()
{
	mMeteorsSpawnRate = static_cast<int>(std::log(mDestroyedMeteorsCounter) / std::log(1.5f));

	mMeteorsSpawnRate = mMeteorsSpawnRate > 0 ? mMeteorsSpawnRate : 1;
}
