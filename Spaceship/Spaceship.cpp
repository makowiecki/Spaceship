#include "pch.h"
#include "Spaceship.h"

#include "World.h"
#include "Projectile.h"

std::unique_ptr<DirectX::SpriteFont> Spaceship::mFont{ nullptr };
std::unique_ptr<DirectX::SpriteBatch> Spaceship::mSpriteBatch{ nullptr };
std::shared_ptr<DirectX::GeometricPrimitive> Spaceship::mRenderObjectAsset{ nullptr };

Spaceship::Spaceship(const DirectX::SimpleMath::Vector3& newLocation, World* world)
	:GameObject(newLocation, world),
	mProjectileSpawnOffset(1.f),
	mShootTimer(0.f)
{
	mRenderObject = mRenderObjectAsset;

	mCollisionSphere.Center = mLocation;
	mCollisionSphere.Radius = mScale.x / 2; // div by 2 because in creatin is diameter

	mDestroyOffTheScreen = false;

	mVelocity = 10.f;

	mProjectileSpeed = 10.f;
	mShotRate = 2;

	InputManager::BindAction(InputManager::ActionName::LEFT, std::bind(&Spaceship::MoveLeft, this, std::placeholders::_1));
	InputManager::BindAction(InputManager::ActionName::RIGHT, std::bind(&Spaceship::MoveRight, this, std::placeholders::_1));
	InputManager::BindAction(InputManager::ActionName::SHOOT, std::bind(&Spaceship::ShootProjectile, this, std::placeholders::_1));
}

Spaceship::~Spaceship()
{
}

void Spaceship::MoveRight(float deltaTime)
{
	if(mScreenPosition.x + mVelocity*deltaTime + 20.f > GameplayHelpers::GetViewportSize().x) //20.f - workaround for not having 3d blocking areas
	{
		return;
	}

	Move(DirectX::SimpleMath::Vector3(mVelocity*deltaTime, 0.f, 0.f));
}

void Spaceship::MoveLeft(float deltaTime)
{
	if(mScreenPosition.x - mVelocity*deltaTime - 20.f < 0) //20.f - workaround for not having 3d blocking areas
	{
		return;
	}

	Move(DirectX::SimpleMath::Vector3(-mVelocity*deltaTime, 0.f, 0.f));
}

void Spaceship::ShootProjectile(float deltaTime)
{
	if(mShootTimer > 1.f / mShotRate)
	{
		DirectX::SimpleMath::Vector3 projectileLocation(GetLocation());
		projectileLocation.y += mProjectileSpawnOffset;

		GameObject* projectile = GetWorld()->SpawnObject<Projectile>(projectileLocation);
		projectile->SetVelocity(mProjectileSpeed);
		projectile->SetInstigator(*this);

		mShootTimer = 0.f;
	}
}

void Spaceship::SetGetMeteorsDestroyedFunction(const std::function<int()>& function)
{
	mGetDestroyedMeteors = function;
}

void Spaceship::Init(ID3D11DeviceContext * deviceContext, ID3D11Device* device)
{
	mRenderObjectAsset = DirectX::GeometricPrimitive::CreateCone(deviceContext, 1.f, 0.5f);
	mFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/italic.spritefont");
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
}

void Spaceship::OnCollision(const GameObject & otherObject)
{
	GetWorld()->Reset();
}

void Spaceship::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	mShootTimer += deltaTime;
}

void Spaceship::Render(const DirectX::SimpleMath::Matrix & world, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection)
{
	GameObject::Render(world, view, projection);

	using namespace DirectX;

	//should be in HUD class
	mSpriteBatch->Begin();

	mGetDestroyedMeteors();
	std::wstring textToDraw = L"Destroyed meteors: " + std::to_wstring(mGetDestroyedMeteors());

	DirectX::SimpleMath::Vector2 textPosition(mScreenPosition.x, mScreenPosition.y + 25.f);
	DirectX::SimpleMath::Vector2 origin = mFont->MeasureString(textToDraw.c_str()) / 2.f;
	DirectX::SimpleMath::Vector3 scale(0.4f, 0.4f, 0.4f);

	mFont->DrawString(mSpriteBatch.get(), textToDraw.c_str(), textPosition, DirectX::Colors::Black, 0.f, origin, scale);

	mSpriteBatch->End();
}
