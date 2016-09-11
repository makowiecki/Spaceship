#pragma once

class GameplayHelpers
{
public:
	GameplayHelpers()=delete;
	GameplayHelpers(const GameplayHelpers&)=delete;
	GameplayHelpers& operator= (const GameplayHelpers&) = delete;
	~GameplayHelpers()=delete;

	static void Init(int width, int height, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	static void Update(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection); //keep in track actual matrixes

	static DirectX::SimpleMath::Vector2 GetViewportSize();

	static DirectX::SimpleMath::Vector2 ProjectOnScreen(const DirectX::SimpleMath::Vector3 & worldLocation/*, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection*/);

	static DirectX::SimpleMath::Vector3 UnprojectOnScreen(const DirectX::SimpleMath::Vector2 & screenPosition/*, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection*/);

private:
		
	static DirectX::SimpleMath::Viewport mViewport;

	static const DirectX::SimpleMath::Matrix *m_world_ptr;
	static const DirectX::SimpleMath::Matrix *m_view_ptr;
	static const DirectX::SimpleMath::Matrix *m_projection_ptr;
};

