#include "pch.h"
#include "GameObject.h"


GameObject::GameObject(const DirectX::SimpleMath::Vector3& newLocation, World* world)
	:mDestroyed(false),
	mVelocity(0.f),
	mReferenceToWorld(world),
	mDestroyOffTheScreen(true),
	mInstigator(nullptr)
{
	SetLocation(newLocation);
	SetScale(DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f));

	mRenderObjectColor = DirectX::Colors::White;
}

GameObject::~GameObject()
{
}

void GameObject::SetLocation(const DirectX::SimpleMath::Vector3 & newLocation)
{
	mLocation = newLocation;

	mCollisionBox.Center = mLocation;
}

void GameObject::Move(const DirectX::SimpleMath::Vector3 & offset)
{
	mLocation += offset;

	mCollisionBox.Center = mLocation;
}

const DirectX::SimpleMath::Vector3 & GameObject::GetLocation() const
{
	return mLocation;
}

void GameObject::SetRotation(const DirectX::SimpleMath::Vector3 & newRotation)
{
	mRotation = newRotation;

	mCollisionBox.Orientation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(mRotation.y * DirectX::XM_PI / 180.f, mRotation.x * DirectX::XM_PI / 180.f, mRotation.z * DirectX::XM_PI / 180.f);
}

void GameObject::Rotate(const DirectX::SimpleMath::Vector3 & rotation)
{
	mRotation += rotation;

	mCollisionBox.Orientation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(mRotation.y * DirectX::XM_PI / 180.f, mRotation.x * DirectX::XM_PI / 180.f, mRotation.z * DirectX::XM_PI / 180.f);
}

const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return mRotation;
}

void GameObject::SetScale(const DirectX::SimpleMath::Vector3 & newScale)
{
	mScale = newScale;

	mCollisionBox.Extents = DirectX::SimpleMath::Vector3(mScale.x / 2.f, mScale.y / 2.f, mScale.z / 2.f);
}

void GameObject::AddScale(const DirectX::SimpleMath::Vector3 & addedScale)
{
	mScale += addedScale;

	mCollisionBox.Extents = DirectX::SimpleMath::Vector3(mScale.x / 2.f, mScale.y / 2.f, mScale.z / 2.f);
}

const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return mScale;
}

World * GameObject::GetWorld() const
{
	return mReferenceToWorld;
}

void GameObject::Destroy()
{
	mDestroyed = true;
	OnDestroy();
}

bool GameObject::IsDestroyed() const
{
	return mDestroyed;
}

void GameObject::SetVelocity(float newVelocity)
{
	mVelocity = std::max(0.f, newVelocity);
}

void GameObject::AddVelocity(float value)
{
	mVelocity += value;
}

float GameObject::GetVelocity() const
{
	return mVelocity;
}

bool GameObject::Collide(const GameObject & object)
{
	if(&object == mInstigator ||
	   object.mInstigator == this)
	{
		return false;
	}

	return mCollisionBox.Intersects(object.mCollisionBox);
}

void GameObject::OnCollision(const GameObject & otherObject)
{
}

void GameObject::OnDestroy()
{
}

void GameObject::Update(float deltaTime)
{
	mScreenPosition = GameplayHelpers::ProjectOnScreen(mLocation);

	if(mDestroyOffTheScreen)
	{
		if(mScreenPosition.x > GameplayHelpers::GetViewportSize().x ||
		   mScreenPosition.x  < 0.f ||
		   mScreenPosition.y  > GameplayHelpers::GetViewportSize().y ||
		   mScreenPosition.y < 0.f)
		{
			Destroy();
			return;
		}
	}
}

void GameObject::Render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	if(!mRenderObject) { return; }

	Matrix local = Matrix::CreateScale(mScale) * Matrix::CreateFromYawPitchRoll(mRotation.y * DirectX::XM_PI / 180.f, mRotation.x * DirectX::XM_PI / 180.f, mRotation.z * DirectX::XM_PI / 180.f) *  Matrix::CreateTranslation(mLocation) * world;
	mRenderObject->Draw(local, view, projection, mRenderObjectColor);
}

void GameObject::SetInstigator(GameObject & instigator)
{
	mInstigator = &instigator;
}
