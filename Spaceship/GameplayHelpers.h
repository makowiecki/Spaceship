#pragma once

/** Provides static function useful during gameplay. */
class GameplayHelpers
{
public:
	GameplayHelpers()=delete;
	GameplayHelpers(const GameplayHelpers&)=delete;
	GameplayHelpers& operator= (const GameplayHelpers&) = delete;
	~GameplayHelpers()=delete;

	/** Initializes all private members, must me called */
	static void Init(int width, int height, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	/** Updates all private members, should be call on every update otherwise can cause crash */
	static void Update(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection); //keep in track actual matrixes

	/** Returns current Viewport Size */
	static DirectX::SimpleMath::Vector2 GetViewportSize();

	/** Returns screen position projected from worldLocation */
	static DirectX::SimpleMath::Vector2 ProjectOnScreen(const DirectX::SimpleMath::Vector3 & worldLocation);

	/** Returns world location from screenPosition */
	static DirectX::SimpleMath::Vector3 UnprojectOnScreen(const DirectX::SimpleMath::Vector2 & screenPosition);

private:
		
	static DirectX::SimpleMath::Viewport mViewport;

	static const DirectX::SimpleMath::Matrix *m_world_ptr; // ptr to world matrix, by default null (should be init and updated)
	static const DirectX::SimpleMath::Matrix *m_view_ptr; // ptr to ciew matrix, by default null (should be init and updated)
	static const DirectX::SimpleMath::Matrix *m_projection_ptr; // ptr to projection matrix, by default null (should be init and updated)
};

