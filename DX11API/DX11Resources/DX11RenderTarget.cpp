#pragma once

#include "Common\memory_leaks.h"
#include "DX11RenderTarget.h"

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
	m_depthStencilView( depthStencil )
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

	return newRenderTarget;
}
