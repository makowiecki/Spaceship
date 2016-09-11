#pragma once

class World;

class MeteorsManager
{
public:
	MeteorsManager(World *world);
	~MeteorsManager();

	World* GetWorld()const;

	void MeteorDestroyed();
	int GetDestroyedMeteorsNumber()const;

	void Reset();

	void Update(float deltaTime);

private:

	int mDestroyedMeteorsCounter;
	int mCreatedMeteorsCounter;

	int mMeteorsSpawnRate; //meteors per second

	float mSpawnTimer;

	World *mWorldReference;

	void SpawnMeteor();

	void RecalculateSpawnRate();
};

