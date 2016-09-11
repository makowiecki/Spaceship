#include "pch.h"
#include "Random.h"

#include <random>

int Random::GetRandom(int rangeBegin, int rangeEnd)
{
	static std::random_device rd;
	static std::default_random_engine generator(rd());

	std::uniform_int_distribution<int> distribution(rangeBegin, rangeEnd);

	return distribution(generator);
}

float Random::GetRandom(float rangeBegin, float rangeEnd)
{
	static std::random_device rd;
	static std::default_random_engine generator(rd());

	std::uniform_real_distribution<float> distribution(rangeBegin, rangeEnd);

	return distribution(generator);
}