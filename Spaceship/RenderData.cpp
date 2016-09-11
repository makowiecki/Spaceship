#include "pch.h"
#include "RenderData.h"


//ID3D11DeviceContext* RenderData::mDeviceContext{ nullptr };
std::unique_ptr<DirectX::GeometricPrimitive> RenderData::mSphereAsset{ nullptr };
std::unique_ptr<DirectX::GeometricPrimitive> RenderData::mCubeAsset{ nullptr };
std::unique_ptr<DirectX::GeometricPrimitive> RenderData::mConeAsset{ nullptr };

RenderData::RenderData()
{
	mRenderObject = nullptr;
}


RenderData::~RenderData()
{
}

void RenderData::Init(ID3D11DeviceContext * deviceContext)
{
	if(!deviceContext) { return; }

	mSphereAsset = DirectX::GeometricPrimitive::CreateSphere(deviceContext);
	mCubeAsset = DirectX::GeometricPrimitive::CreateCube(deviceContext);
	mConeAsset = DirectX::GeometricPrimitive::CreateCone(deviceContext);
}

void RenderData::createCube()
{
	mRenderObject = mCubeAsset.get();
}

void RenderData::createSphere()
{
	mRenderObject = mSphereAsset.get();
}

void RenderData::createCone()
{
	mRenderObject = mConeAsset.get();
}

void RenderData::Render(const DirectX::SimpleMath::Vector3 & location, const DirectX::SimpleMath::Vector3 & rotaton, const DirectX::SimpleMath::Vector3 & scale, const DirectX::SimpleMath::Color& color)
{
	using namespace DirectX::SimpleMath;

	if(!mRenderObject) { return; }

	const Matrix world = GameplayHelpers::getWorldMatrix();
	const Matrix view = GameplayHelpers::getViewMatrix();
	const Matrix projection = GameplayHelpers::getProjectionMatrix();

	Matrix local = Matrix::CreateScale(scale) * Matrix::CreateFromYawPitchRoll(rotaton.y * DirectX::XM_PI / 180.f, rotaton.x * DirectX::XM_PI / 180.f, rotaton.z * DirectX::XM_PI / 180.f) *  Matrix::CreateTranslation(location) * world;
	mRenderObject->Draw(local, view, projection, color);

}
