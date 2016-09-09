#include "pch.h"
#include "GameObject.h"

#include "GameplayHelpers.h"


GameObject::GameObject(const DirectX::SimpleMath::Vector3& newLocation, World* world)
	:mDestroyed(false),
	mVelocity(0.f),
	mReferenceToWorld(world),
	mScale(1.f, 1.f, 1.f),
	mDestroyOffTheScreen(true),
	mInstigator(nullptr)
{
	setLocation(newLocation);

	mRenderObjectColor = DirectX::Colors::White;
}

GameObject::~GameObject()
{
}

void GameObject::setLocation(const DirectX::SimpleMath::Vector3 & newLocation)
{
	mLocation = newLocation;
	mCollisionSphere.Center = mLocation;
}

void GameObject::move(const DirectX::SimpleMath::Vector3 & offset)
{
	mLocation += offset;
	mCollisionSphere.Center = mLocation;
}

const DirectX::SimpleMath::Vector3 & GameObject::getLocation() const
{
	return mLocation;
}

void GameObject::setRotation(const DirectX::SimpleMath::Vector3 & newRotation)
{
	mRotation = newRotation;
}

void GameObject::rotate(const DirectX::SimpleMath::Vector3 & rotation)
{
	mRotation += rotation;
}

const DirectX::SimpleMath::Vector3 & GameObject::getRotation() const
{
	return mRotation;
}

void GameObject::setScale(const DirectX::SimpleMath::Vector3 & newScale)
{
	mScale = newScale;
}

void GameObject::addScale(const DirectX::SimpleMath::Vector3 & addedScale)
{
	mScale += addedScale;
}

const DirectX::SimpleMath::Vector3 & GameObject::getScale() const
{
	return mScale;
}

World * GameObject::getWorld() const
{
	return mReferenceToWorld;
}

void GameObject::destroy()
{
	mDestroyed = true;
	onDestroy();
}

bool GameObject::isDestroyed() const
{
	return mDestroyed;
}

void GameObject::setVelocity(float newVelocity)
{
	mVelocity = std::max(0.f, newVelocity);
}

void GameObject::addVelocity(float value)
{
	mVelocity += value;
}

float GameObject::getVelocity() const
{
	return mVelocity;
}

bool GameObject::collide(const GameObject & object)
{
	if(&object == mInstigator ||
	   object.mInstigator == this)
	{
		return false;
	}

	return mCollisionSphere. Intersects(object.mCollisionSphere);
}

void GameObject::onHit(const GameObject & otherObject)
{
}

void GameObject::onDestroy()
{
}

void GameObject::update(float deltaTime)
{
	mScreenPosition = GameplayHelpers::projectOnScreen(mLocation);

	if(mDestroyOffTheScreen)
	{
		if(mScreenPosition.x > GameplayHelpers::getViewportSize().x ||
		   mScreenPosition.x  < 0.f ||
		   mScreenPosition.y  > GameplayHelpers::getViewportSize().y ||
		   mScreenPosition.y < 0.f)
		{
			destroy();
			return;
		}
	}
}

void GameObject::render(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	if(!mRenderObject) { return; }

	Matrix local = Matrix::CreateScale(mScale) * Matrix::CreateFromYawPitchRoll(mRotation.y * DirectX::XM_PI / 180.f, mRotation.x * DirectX::XM_PI / 180.f, mRotation.z * DirectX::XM_PI / 180.f) *  Matrix::CreateTranslation(mLocation) * world;
	mRenderObject->Draw(local, view, projection, mRenderObjectColor);
}

void GameObject::setInstigator(GameObject & instigator)
{
	mInstigator = &instigator;
}
