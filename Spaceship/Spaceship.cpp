#include "pch.h"
#include "Spaceship.h"

#include "World.h"
#include "InputManager.h"
#include "GameplayHelpers.h"

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

	InputManager::bindAction(InputManager::ActionName::LEFT, std::bind(&Spaceship::moveLeft, this, std::placeholders::_1));
	InputManager::bindAction(InputManager::ActionName::RIGHT, std::bind(&Spaceship::moveRight, this, std::placeholders::_1));
	InputManager::bindAction(InputManager::ActionName::SHOOT, std::bind(&Spaceship::shootProjectile, this, std::placeholders::_1));
}

Spaceship::~Spaceship()
{
}

void Spaceship::moveRight(float deltaTime)
{
	if(mScreenPosition.x + mVelocity*deltaTime + 20.f > GameplayHelpers::getViewportSize().x) //20.f - workaround for not having 3d blocking areas
	{
		return;
	}

	move(DirectX::SimpleMath::Vector3(mVelocity*deltaTime, 0.f, 0.f));
}

void Spaceship::moveLeft(float deltaTime)
{
	if(mScreenPosition.x - mVelocity*deltaTime - 20.f < 0) //20.f - workaround for not having 3d blocking areas
	{
		return;
	}

	move(DirectX::SimpleMath::Vector3(-mVelocity*deltaTime, 0.f, 0.f));
}

void Spaceship::shootProjectile(float deltaTime)
{
	if(mShootTimer > 1.f / mShotRate)
	{
		DirectX::SimpleMath::Vector3 projectileLocation(getLocation());
		projectileLocation.y += mProjectileSpawnOffset;

		GameObject* projectile = getWorld()->spawnObject<Projectile>(projectileLocation);
		projectile->setVelocity(mProjectileSpeed);
		projectile->setInstigator(*this);

		mShootTimer = 0.f;
	}
}

void Spaceship::setGetMeteorsDestroyedFunction(const std::function<int()>& function)
{
	mGetDestroyedMeteors = function;
}

void Spaceship::init(ID3D11DeviceContext * deviceContext, ID3D11Device* device)
{
	mRenderObjectAsset = DirectX::GeometricPrimitive::CreateCone(deviceContext, 1.f, 0.5f);
	mFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/italic.spritefont");
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
}

void Spaceship::onHit(const GameObject & otherObject)
{
	getWorld()->reset();
}

void Spaceship::update(float deltaTime)
{
	GameObject::update(deltaTime);

	mShootTimer += deltaTime;
}

void Spaceship::render(const DirectX::SimpleMath::Matrix & world, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & projection)
{
	GameObject::render(world, view, projection);

	using namespace DirectX;

	mSpriteBatch->Begin();

	mGetDestroyedMeteors();
	std::wstring textToDraw = L"Destroyed meteors: " + std::to_wstring(mGetDestroyedMeteors());

	DirectX::SimpleMath::Vector2 textPosition(mScreenPosition.x, mScreenPosition.y + 25.f);
	DirectX::SimpleMath::Vector2 origin = mFont->MeasureString(textToDraw.c_str()) / 2.f;
	DirectX::SimpleMath::Vector3 scale(0.4f, 0.4f, 0.4f);

	mFont->DrawString(mSpriteBatch.get(), textToDraw.c_str(), textPosition, DirectX::Colors::Black, 0.f, origin, scale);

	mSpriteBatch->End();
}
