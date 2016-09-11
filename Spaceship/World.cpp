#include "pch.h"
#include "World.h"

#include "Spaceship.h"


World::World()
	:mMeteorsManager(this)
{
}

World::~World()
{
}

void World::Init()
{
	mGameObjects.clear();

	DirectX::SimpleMath::Vector3 screenCenterLocation = GameplayHelpers::UnprojectOnScreen(DirectX::SimpleMath::Vector2(GameplayHelpers::GetViewportSize().x / 2, 40.f));
	screenCenterLocation.z = 0.f;

	Spaceship* spaceShip = dynamic_cast<Spaceship*>(SpawnObject<Spaceship>(screenCenterLocation));

	if(spaceShip)
	{
		spaceShip->SetGetMeteorsDestroyedFunction(std::bind(&MeteorsManager::GetDestroyedMeteorsNumber, &mMeteorsManager));
	}

	mMeteorsManager.Reset();

	mIsSetToReset = false;
}

void World::OnMeteorDestroyed()
{
	mMeteorsManager.MeteorDestroyed();
}

void World::Reset()
{
	mIsSetToReset = true;
}

void World::HandleCollisions()
{
	for(size_t i = 0; i < mGameObjects.size(); i++)
	{
		for(size_t j = i + 1; j < mGameObjects.size(); j++)
		{
			if(mGameObjects[i]->Collide(*mGameObjects[j]))
			{
				mGameObjects[i]->OnCollision(*mGameObjects[j]);
				mGameObjects[j]->OnCollision(*mGameObjects[i]);
			}
		}
	}
}

void World::Update(float deltaTime)
{
	mMeteorsManager.Update(deltaTime);

	for(const mGameObjectsValueType& object : mGameObjects)
	{
		object->Update(deltaTime);
	}

	HandleCollisions();

	if(mIsSetToReset)
	{
		Init();
	}
}

void World::RenderObjects(const DirectX::SimpleMath::Matrix & world, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection)
{
	for(const mGameObjectsValueType& object : mGameObjects)
	{
		object->Render(world, view, projection);
	}
}

void World::RemoveDestryedObjects()
{
	std::vector<std::unique_ptr<GameObject>>::iterator newEnd = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::bind(&GameObject::IsDestroyed, std::placeholders::_1));
	if(newEnd != mGameObjects.end())
	{
		mGameObjects.erase(newEnd, mGameObjects.end());
	}
}
