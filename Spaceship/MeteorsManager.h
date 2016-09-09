#pragma once

class World;

class MeteorsManager
{
public:
	MeteorsManager(World *world);
	~MeteorsManager();

	World* getWorld()const;

	void meteorDestroyed();
	int getDestroyedMeteorsNumber()const;

	void reset();

	void update(float deltaTime);

private:

	int mDestroyedMeteorsCounter;
	int mCreatedMeteorsCounter;

	int mMeteorsSpawnRate; //meteors per second

	float mSpawnTimer;

	World *mWorldReference;

	void spawnMeteor();

	void recalculateSpawnRate();
};

