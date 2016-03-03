#include "DX11ConstantsMapper.h"

#include "Common/MemoryLeaks.h"

/**@see ResourceUsage.*/
D3D11_USAGE DX11ResourceUsage[] =
{	
	D3D11_USAGE::D3D11_USAGE_DEFAULT,
	D3D11_USAGE::D3D11_USAGE_DYNAMIC,
	D3D11_USAGE::D3D11_USAGE_IMMUTABLE,
	D3D11_USAGE::D3D11_USAGE_STAGING
};

/**@see PrimitiveTopology.*/
D3D_PRIMITIVE_TOPOLOGY DX11PrimitiveTopology[]
{
  D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
  D3D_PRIMITIVE_TOPOLOGY_LINELIST,
  D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
  D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
  D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
  D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
  D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
  D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
  D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ
};

/**@see TextureType*/
D3D11_RTV_DIMENSION DX11TextureType[ 9 ]
{
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_UNKNOWN,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_BUFFER,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE1D,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE1DARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DMS,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE3D,
};

D3D11_DSV_DIMENSION DX11TextureTypeToDSV[ 9 ]
{
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1D,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1DARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
};

D3D11_SRV_DIMENSION DX11TextureTypeToSRV[ 9 ]
{
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_UNKNOWN,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFER,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE1D,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE1DARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DMS,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE3D,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURECUBE,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURECUBEARRAY,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFEREX,
};

/**@see ResourceBinding.*/
D3D11_BIND_FLAG	DX11ResourceBinding[ 10 ]
{
	D3D11_BIND_VERTEX_BUFFER,
	D3D11_BIND_INDEX_BUFFER,
	D3D11_BIND_CONSTANT_BUFFER,
	D3D11_BIND_SHADER_RESOURCE,
	D3D11_BIND_STREAM_OUTPUT,
	D3D11_BIND_RENDER_TARGET,
	D3D11_BIND_DEPTH_STENCIL,
	D3D11_BIND_UNORDERED_ACCESS,
	//DirectX 11.1
	//D3D11_BIND_DECODER,
	//D3D11_BIND_VIDEO_ENCODER
	D3D11_BIND_UNORDERED_ACCESS,
	D3D11_BIND_UNORDERED_ACCESS
};

/**@see DepthStencilFormat.*/
DXGI_FORMAT DX11DepthStencilFormat[ 4 ]
{
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_D24_UNORM_S8_UINT,
	DXGI_FORMAT_D16_UNORM
};

DXGI_FORMAT DX11DepthStencilTypeless[ 4 ]
{
	DXGI_FORMAT_R32G8X24_TYPELESS,
	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_R16_TYPELESS
};

DXGI_FORMAT DX11DepthOnly[ 4 ]
{
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_R16_UNORM
};

DXGI_FORMAT DX11StencilOnly[ 4 ]
{
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	DXGI_FORMAT_UNKNOWN
};

/**@see ResourceFormat.*/
DXGI_FORMAT DX11ResourceFormat[] =
{
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_R32G32B32A32_TYPELESS,
	DXGI_FORMAT_R32G32B32A32_FLOAT,
	DXGI_FORMAT_R32G32B32A32_UINT,
	DXGI_FORMAT_R32G32B32A32_SINT,
	DXGI_FORMAT_R32G32B32_TYPELESS,
	DXGI_FORMAT_R32G32B32_FLOAT,
	DXGI_FORMAT_R32G32B32_UINT,
	DXGI_FORMAT_R32G32B32_SINT,
	DXGI_FORMAT_R16G16B16A16_TYPELESS,
	DXGI_FORMAT_R16G16B16A16_FLOAT,
	DXGI_FORMAT_R16G16B16A16_UNORM,
	DXGI_FORMAT_R16G16B16A16_UINT,
	DXGI_FORMAT_R16G16B16A16_SNORM,
	DXGI_FORMAT_R16G16B16A16_SINT,
	DXGI_FORMAT_R32G32_TYPELESS,
	DXGI_FORMAT_R32G32_FLOAT,
	DXGI_FORMAT_R32G32_UINT,
	DXGI_FORMAT_R32G32_SINT,
	DXGI_FORMAT_R32G8X24_TYPELESS,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	DXGI_FORMAT_R10G10B10A2_TYPELESS,
	DXGI_FORMAT_R10G10B10A2_UNORM,
	DXGI_FORMAT_R10G10B10A2_UINT,
	DXGI_FORMAT_R11G11B10_FLOAT,
	DXGI_FORMAT_R8G8B8A8_TYPELESS,
	DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
	DXGI_FORMAT_R8G8B8A8_UINT,
	DXGI_FORMAT_R8G8B8A8_SNORM,
	DXGI_FORMAT_R8G8B8A8_SINT,
	DXGI_FORMAT_R16G16_TYPELESS,
	DXGI_FORMAT_R16G16_FLOAT,
	DXGI_FORMAT_R16G16_UNORM,
	DXGI_FORMAT_R16G16_UINT,
	DXGI_FORMAT_R16G16_SNORM,
	DXGI_FORMAT_R16G16_SINT,
	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R32_UINT,
	DXGI_FORMAT_R32_SINT,
	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_D24_UNORM_S8_UINT,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	DXGI_FORMAT_R8G8_TYPELESS,
	DXGI_FORMAT_R8G8_UNORM,
	DXGI_FORMAT_R8G8_UINT,
	DXGI_FORMAT_R8G8_SNORM,
	DXGI_FORMAT_R8G8_SINT,
	DXGI_FORMAT_R16_TYPELESS,
	DXGI_FORMAT_R16_FLOAT,
	DXGI_FORMAT_D16_UNORM,
	DXGI_FORMAT_R16_UNORM,
	DXGI_FORMAT_R16_UINT,
	DXGI_FORMAT_R16_SNORM,
	DXGI_FORMAT_R16_SINT,
	DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT_R8_UNORM,
	DXGI_FORMAT_R8_UINT,
	DXGI_FORMAT_R8_SNORM,
	DXGI_FORMAT_R8_SINT,
	DXGI_FORMAT_A8_UNORM,
	DXGI_FORMAT_R1_UNORM,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
	DXGI_FORMAT_R8G8_B8G8_UNORM,
	DXGI_FORMAT_G8R8_G8B8_UNORM,
	DXGI_FORMAT_BC1_TYPELESS,
	DXGI_FORMAT_BC1_UNORM,
	DXGI_FORMAT_BC1_UNORM_SRGB,
	DXGI_FORMAT_BC2_TYPELESS,
	DXGI_FORMAT_BC2_UNORM,
	DXGI_FORMAT_BC2_UNORM_SRGB,
	DXGI_FORMAT_BC3_TYPELESS,
	DXGI_FORMAT_BC3_UNORM,
	DXGI_FORMAT_BC3_UNORM_SRGB,
	DXGI_FORMAT_BC4_TYPELESS,
	DXGI_FORMAT_BC4_UNORM,
	DXGI_FORMAT_BC4_SNORM,
	DXGI_FORMAT_BC5_TYPELESS,
	DXGI_FORMAT_BC5_UNORM,
	DXGI_FORMAT_BC5_SNORM,
	DXGI_FORMAT_B5G6R5_UNORM,
	DXGI_FORMAT_B5G5R5A1_UNORM,
	DXGI_FORMAT_B8G8R8A8_UNORM,
	DXGI_FORMAT_B8G8R8X8_UNORM,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
	DXGI_FORMAT_B8G8R8A8_TYPELESS,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
	DXGI_FORMAT_B8G8R8X8_TYPELESS,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
	DXGI_FORMAT_BC6H_TYPELESS,
	DXGI_FORMAT_BC6H_UF16,
	DXGI_FORMAT_BC6H_SF16,
	DXGI_FORMAT_BC7_TYPELESS,
	DXGI_FORMAT_BC7_UNORM,
	DXGI_FORMAT_BC7_UNORM_SRGB,
	// DirectX 11.1
	//DXGI_FORMAT_AYUV,
	//DXGI_FORMAT_Y410,
	//DXGI_FORMAT_Y416,
	//DXGI_FORMAT_NV12,
	//DXGI_FORMAT_P010,
	//DXGI_FORMAT_P016,
	//DXGI_FORMAT_420_OPAQUE,
	//DXGI_FORMAT_YUY2,
	//DXGI_FORMAT_Y210,
	//DXGI_FORMAT_Y216,
	//DXGI_FORMAT_NV11,
	//DXGI_FORMAT_AI44,
	//DXGI_FORMAT_IA44,
	//DXGI_FORMAT_P8,
	//DXGI_FORMAT_A8P8,
	//DXGI_FORMAT_B4G4R4A4_UNORM,
	//DXGI_FORMAT_P208,
	//DXGI_FORMAT_V208,
	//DXGI_FORMAT_V408
	// Zastąpione unknownami
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN
};

