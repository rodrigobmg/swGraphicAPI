#pragma once

#include "Common/MemoryLeaks.h"
#include "DX11RenderTarget.h"
#include "../DX11Initializer/DX11ConstantsMapper.h"
#include "DX11Texture.h"

/**@brief Zwalnia zasoby DirectXa.*/
DX11RenderTarget::~DX11RenderTarget()
{
	if( m_renderTarget )
		m_renderTarget->Release();
	if( m_depthStencilView )
		m_depthStencilView->Release();
	m_renderTarget = nullptr;
	m_depthStencilView = nullptr;
}

/**@brief */
DX11RenderTarget::DX11RenderTarget( ID3D11RenderTargetView * renderTarget,
									ID3D11DepthStencilView * depthStencil,
									TextureObject* colorBuffer,
									TextureObject* depthBuffer,
									TextureObject* stencilBuffer)
	: RenderTargetObject( colorBuffer, depthBuffer, stencilBuffer ),
	m_renderTarget( renderTarget ),
	m_depthStencilView( depthStencil ),
	m_height( 0 ),
	m_width( 0 )
{}

/**Tworzy object DX11RenderTarget z bufora tylnego ekranu.

@todo Wersja troszkę niewłaściwa. RenderTarget jest już stworzony wcześniej przy zwykłej inicjalizacji DX11APIObjects.
Tutaj jest jedynie tworzony obiekt silnikowy, który potrafi to obsłużyć. Trzeba to zmienić, żeby całe tworzenie
render targetu odbywało się tutaj.

@note Wewnętrzne tekstury render targetu są ustawione na nullptr. Oznacza to, że nie można ich użyć w innych obiektach.
Zastanowić się czy to właściwe rozwiązanie i ewentualnie zmienić implementację.

@return Zwraca wskaźnik object DX11RenderTarget.*/
DX11RenderTarget* DX11RenderTarget::CreateScreenRenderTarget()
{
	DX11RenderTarget* newRenderTarget = new DX11RenderTarget( render_target, z_buffer_view, nullptr, nullptr, nullptr );
	render_target = nullptr;			// Ochrona przed podwójnym zwalnianiem obiektu.
	z_buffer_view = nullptr;			// Ochrona przed podwójnym zwalnianiem obiektu.

	auto viewPort = DX11APIObjects::get_viewport_desc();
	newRenderTarget->SetHeight( static_cast<uint16>( viewPort.Height ) );
	newRenderTarget->SetWidth( static_cast<uint16>( viewPort.Width ) );

	return newRenderTarget;
}

/**@brief Tworzy render target o podanych w parametrach.

@todo W przyszłości powinna być możliwość tworzenia tekstur innych niż 2D. Poza tym renderować
powinno się móc do dowolnego poziomu mipmap. Decyzja powinna być podejmowana w runtimie, więc
trzeba chyba stworzyć wiele widoków (???). Przydatne to jest w przypadku Environmental mappingu.
Jeżeli obiekt jest mocno oddalony, to nie ma co renderować mu mapy z dużą rozdzielczością.

@return Zwraca render target lub nullptr, jeżeli tworzenie nie powiodło się lub podano niepoprawne parametry.*/
DX11RenderTarget* DX11RenderTarget::CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	if( !ValidateDescriptor( renderTargetDescriptor ) )
		return nullptr;

	HRESULT result;

	ID3D11Texture2D* colorBuffer = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;

	unsigned int arraySize = 1;
	if( renderTargetDescriptor.textureType == TextureType::TEXTURE_TYPE_TEXTURE2D_ARRAY || renderTargetDescriptor.textureType == TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE_ARRAY )
		arraySize = renderTargetDescriptor.arraySize;


	D3D11_TEXTURE2D_DESC renderTargetTexDesc;
	renderTargetTexDesc.Width				= renderTargetDescriptor.textureWidth;
	renderTargetTexDesc.Height				= renderTargetDescriptor.textureHeight;
	renderTargetTexDesc.MipLevels			= 1;
	renderTargetTexDesc.Usage				= DX11ConstantsMapper::Get( renderTargetDescriptor.usage );
	renderTargetTexDesc.ArraySize			= arraySize;
	
	renderTargetTexDesc.SampleDesc.Count	= 1;
	renderTargetTexDesc.SampleDesc.Quality	= 0;
	if( renderTargetDescriptor.textureType == TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE || renderTargetDescriptor.textureType == TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE_ARRAY )
	{
		renderTargetTexDesc.SampleDesc.Count	= renderTargetDescriptor.numSamples;
		renderTargetTexDesc.SampleDesc.Quality	= renderTargetDescriptor.samplesQuality;
	}
	
	renderTargetTexDesc.MiscFlags = 0;
	if( renderTargetDescriptor.isCubeMap )
		renderTargetTexDesc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
	if( renderTargetDescriptor.allowShareResource )
		renderTargetTexDesc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED ;
	renderTargetTexDesc.CPUAccessFlags = 0;
	if( renderTargetDescriptor.CPURead )
		renderTargetTexDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
	if( renderTargetDescriptor.CPUWrite )
		renderTargetTexDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;

	// Wartości specyficzne dla bufora colorów.
	renderTargetTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	renderTargetTexDesc.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.colorBuffFormat );

	result = device->CreateTexture2D( &renderTargetTexDesc, nullptr, &colorBuffer );
	if( result == S_OK )
	{
		// Wartości specyficzne dla bufora głębokości.
		renderTargetTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTexDesc.Format = DX11ConstantsMapper::ConvertTypeless( renderTargetDescriptor.depthStencilFormat );

		result = device->CreateTexture2D( &renderTargetTexDesc, nullptr, &depthStencilBuffer );
		if( result == S_OK )
		{
			ID3D11RenderTargetView*		renderTargetView;
			ID3D11DepthStencilView*		depthStencilView;

			D3D11_RENDER_TARGET_VIEW_DESC		renderTargetViewDescriptor;
			D3D11_DEPTH_STENCIL_VIEW_DESC		depthStencilViewDescriptor;
			D3D11_SHADER_RESOURCE_VIEW_DESC		shaderViewDescriptor;
			renderTargetViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.colorBuffFormat );
			renderTargetViewDescriptor.ViewDimension = DX11ConstantsMapper::Get( renderTargetDescriptor.textureType );
			depthStencilViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.depthStencilFormat );
			depthStencilViewDescriptor.ViewDimension = DX11ConstantsMapper::ConvertDSV( renderTargetDescriptor.textureType );
			depthStencilViewDescriptor.Flags = 0;			// Bufor głębokości lub stencilu do odczytu i zapisu.
			shaderViewDescriptor.ViewDimension = DX11ConstantsMapper::ConvertSRV( renderTargetDescriptor.textureType );

			switch( renderTargetViewDescriptor.ViewDimension )
			{
			case D3D11_RTV_DIMENSION_TEXTURE2D:
				renderTargetViewDescriptor.Texture2D.MipSlice = 0;
				depthStencilViewDescriptor.Texture2D.MipSlice = 0;
				shaderViewDescriptor.Texture2D.MipLevels = -1;
				shaderViewDescriptor.Texture2D.MostDetailedMip = 0;
				break;
			case D3D11_RTV_DIMENSION_TEXTURE2DARRAY:
				renderTargetViewDescriptor.Texture2DArray.MipSlice = 0;
				renderTargetViewDescriptor.Texture2DArray.FirstArraySlice = 0;
				renderTargetViewDescriptor.Texture2DArray.ArraySize = arraySize;
				depthStencilViewDescriptor.Texture2DArray.MipSlice = 0;
				depthStencilViewDescriptor.Texture2DArray.FirstArraySlice = 0;
				depthStencilViewDescriptor.Texture2DArray.ArraySize = arraySize;
				shaderViewDescriptor.Texture2DArray.ArraySize = arraySize;
				shaderViewDescriptor.Texture2DArray.FirstArraySlice = 0;
				shaderViewDescriptor.Texture2DArray.MipLevels = -1;
				shaderViewDescriptor.Texture2DArray.MostDetailedMip = 0;
				break;
			case D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY:
				renderTargetViewDescriptor.Texture2DArray.FirstArraySlice = 0;
				renderTargetViewDescriptor.Texture2DArray.ArraySize = 1;
				depthStencilViewDescriptor.Texture2DArray.FirstArraySlice = 0;
				depthStencilViewDescriptor.Texture2DArray.ArraySize = 1;
				shaderViewDescriptor.Texture2DMSArray.ArraySize = arraySize;
				shaderViewDescriptor.Texture2DMSArray.FirstArraySlice = 0;
				break;
			case D3D11_RTV_DIMENSION_TEXTURE2DMS:
				break;		// Nic nie trzeba robić.
			}

			result = device->CreateRenderTargetView( colorBuffer, &renderTargetViewDescriptor, &renderTargetView );
			if( result == S_OK )
			{
				result = device->CreateDepthStencilView( depthStencilBuffer, &depthStencilViewDescriptor, &depthStencilView );
				if( result == S_OK )
				{
					ID3D11ShaderResourceView*	depthBufferResourceView = nullptr;
					ID3D11ShaderResourceView*	stencilBufferResourceView = nullptr;
					ID3D11ShaderResourceView*	colorBufferResourceView = nullptr;

					shaderViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.colorBuffFormat );
					result = device->CreateShaderResourceView( colorBuffer, &shaderViewDescriptor, &colorBufferResourceView );
					if( result == S_OK )
					{
						shaderViewDescriptor.Format = DX11ConstantsMapper::ConvertDepthOnly( renderTargetDescriptor.depthStencilFormat );
						result = device->CreateShaderResourceView( depthStencilBuffer, &shaderViewDescriptor, &depthBufferResourceView );
						if( result == S_OK )
						{
							shaderViewDescriptor.Format = DX11ConstantsMapper::ConvertStencilOnly( renderTargetDescriptor.depthStencilFormat );
							if( shaderViewDescriptor.Format != DXGI_FORMAT_UNKNOWN )
								result = device->CreateShaderResourceView( depthStencilBuffer, &shaderViewDescriptor, &stencilBufferResourceView );
							if( result == S_OK )
							{
								TextureObject* colorBufferTex = new DX11Texture( name + RENDER_TARGET_COLOR_BUFFER_NAME, colorBufferResourceView );
								TextureObject* depthBufferTex = new DX11Texture( name + RENDER_TARGET_DEPTH_BUFFER_NAME, depthBufferResourceView );
								TextureObject* stencilBufferTex = nullptr;
								if( stencilBufferResourceView != nullptr )
									stencilBufferTex = new DX11Texture( name + RENDER_TARGET_STENCIL_BUFFER_NAME, stencilBufferResourceView );

								DX11RenderTarget* newRenderTarget = new DX11RenderTarget( renderTargetView, depthStencilView, colorBufferTex, depthBufferTex, stencilBufferTex );
								newRenderTarget->SetHeight( renderTargetDescriptor.textureHeight );
								newRenderTarget->SetWidth( renderTargetDescriptor.textureWidth );

								colorBuffer->Release();
								depthStencilBuffer->Release();
								return newRenderTarget;
							}
							depthBufferResourceView->Release();
						}
						colorBufferResourceView->Release();
					}
					depthStencilView->Release();
				}
				renderTargetView->Release();
			}
			depthStencilBuffer->Release();
		}
		colorBuffer->Release();
	}
	return nullptr;
}

bool DX11RenderTarget::ValidateDescriptor( const RenderTargetDescriptor& renderTargetDescriptor )
{
	TextureType RTType = renderTargetDescriptor.textureType;
	if( RTType == TextureType::TEXTURE_TYPE_TEXTURE1D ||
		RTType == TextureType::TEXTURE_TYPE_TEXTURE1D_ARRAY ||
		RTType == TextureType::TEXTURE_TYPE_TEXTURE3D ||
		RTType == TextureType::TEXTURE_TYPE_BUFFER )
		return false;

	return true;
}
