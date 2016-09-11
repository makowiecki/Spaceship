#pragma once

class GameplayHelpers
{
public:
	GameplayHelpers()=delete;
	GameplayHelpers(const GameplayHelpers&)=delete;
	GameplayHelpers& operator= (const GameplayHelpers&) = delete;
	~GameplayHelpers()=delete;

	static void init(int width, int height, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	static void update(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection); //keep in track actual matrixes

	static DirectX::SimpleMath::Vector2 getViewportSize();

	static const DirectX::SimpleMath::Matrix& getWorldMatrix();
	static const DirectX::SimpleMath::Matrix& getViewMatrix();
	static const DirectX::SimpleMath::Matrix& getProjectionMatrix();

	static DirectX::SimpleMath::Vector2 projectOnScreen(const DirectX::SimpleMath::Vector3 & worldLocation);

	static DirectX::SimpleMath::Vector3 unprojectOnScreen(const DirectX::SimpleMath::Vector2 & screenPosition);

private:
		
	static DirectX::SimpleMath::Viewport mViewport;

	static const DirectX::SimpleMath::Matrix *m_world_ptr;
	static const DirectX::SimpleMath::Matrix *m_view_ptr;
	static const DirectX::SimpleMath::Matrix *m_projection_ptr;
};

