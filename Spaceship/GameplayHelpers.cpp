#include "pch.h"
#include "GameplayHelpers.h"


DirectX::SimpleMath::Viewport GameplayHelpers::mViewport{};
const DirectX::SimpleMath::Matrix * GameplayHelpers::m_world_ptr{ nullptr };
const DirectX::SimpleMath::Matrix * GameplayHelpers::m_view_ptr{ nullptr };
const DirectX::SimpleMath::Matrix * GameplayHelpers::m_projection_ptr{ nullptr };


void GameplayHelpers::Init(int width, int height, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	mViewport.width = static_cast<float>(width);
	mViewport.height = static_cast<float>(height);

	Update(world, view, projection);
}

void GameplayHelpers::Update(const DirectX::SimpleMath::Matrix & world, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection)
{
	m_world_ptr = &world;
	m_view_ptr = &view;
	m_projection_ptr = &projection;
}

DirectX::SimpleMath::Vector2 GameplayHelpers::GetViewportSize()
{
	return DirectX::SimpleMath::Vector2(mViewport.width, mViewport.height);
}

DirectX::SimpleMath::Vector2 GameplayHelpers::ProjectOnScreen(const DirectX::SimpleMath::Vector3 & worldLocation)
{
	DirectX::SimpleMath::Vector3 screenPosition = mViewport.Project(worldLocation, *m_projection_ptr, *m_view_ptr, *m_world_ptr);

	return DirectX::SimpleMath::Vector2(screenPosition.x, screenPosition.y);
}

DirectX::SimpleMath::Vector3 GameplayHelpers::UnprojectOnScreen(const DirectX::SimpleMath::Vector2 & screenPosition)
{
	//mViewport.UnProject() doesn't work well

	using namespace DirectX::SimpleMath;
	
	Vector3 nearSource(screenPosition.x, screenPosition.y, 0.f);
	Vector3 farSource(screenPosition.x, screenPosition.y, 1.f);

	Vector3 nearPoint = mViewport.Unproject(nearSource, *m_projection_ptr, *m_view_ptr, *m_world_ptr);
	Vector3 farPoint = mViewport.Unproject(farSource, *m_projection_ptr, *m_view_ptr, *m_world_ptr);

	Vector3 direction = farPoint - nearPoint;
	direction.Normalize();

	Ray r(nearPoint, direction);

	Vector3 n(0.f, 0.f, 1.f);
	Plane p(n, 0.f);
	Vector3 pNormal = p.Normal();

	float denominator = pNormal.Dot(r.direction);
	float numerator = pNormal.Dot(r.position) + p.D();
	float t = (numerator / denominator);

	Vector3 pickedPosition = nearPoint + direction * t;
	return pickedPosition;
}