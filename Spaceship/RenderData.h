#pragma once

class RenderData
{
public:
	RenderData();
	RenderData(const RenderData&) = default;;
	~RenderData();

	RenderData& operator=(const RenderData&) = default;

	static void Init(ID3D11DeviceContext* deviceContext);

	void createCube();
	void createSphere();
	void createCone();

	void Render(const DirectX::SimpleMath::Vector3& location, const DirectX::SimpleMath::Vector3& rotaton, const DirectX::SimpleMath::Vector3& scale, const DirectX::SimpleMath::Color& color);

private:

	//std::unique_ptr<DirectX::GeometricPrimitive> mRenderObject;
	DirectX::GeometricPrimitive *mRenderObject;

	static std::unique_ptr<DirectX::GeometricPrimitive> mSphereAsset;
	static std::unique_ptr<DirectX::GeometricPrimitive> mCubeAsset;
	static std::unique_ptr<DirectX::GeometricPrimitive> mConeAsset;
};

