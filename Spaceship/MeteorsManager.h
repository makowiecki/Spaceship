#pragma once

class World;

class MeteorsManager
{
public:
	/** Create new Manager */
	MeteorsManager(World *world);

	/** Empty */
	~MeteorsManager();

	/** Return pointer to world in which the Meteors will be spawned */
	World* GetWorld()const;

	/** Function should be called when meteor is destroyed */
	void MeteorDestroyed();

	/** Return number of destroyed meteors */
	int GetDestroyedMeteorsNumber()const;

	/** Reset manager */
	void Reset();

	/** Spawns meteor at given rate */
	void Update(float deltaTime);

private:

	int mDestroyedMeteorsCounter; // number of destroyed meteors
	int mCreatedMeteorsCounter; // number of created meteors

	int mMeteorsSpawnRate; // how many meteors create per second 

	float mSpawnTimer; // timer to keep keep in track spawn rate

	World *mWorldReference; // reference to world in which the Meteors will be spawned

	void SpawnMeteor(); // create Meteor in random location (but always at the top of the screen)

	void RecalculateSpawnRate(); // calculates new spawn rate using logarithmic function
};

