#pragma once
/**
@file DX11Buffer.h
@author nieznanysprawiciel
@copyright Plik jest częścią silnika graficznego SWEngine.
*/


#include "GraphicAPI\MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"

/**@brief Implementacja bufora w DirectX11.
@ingroup DX11API*/
class DX11Buffer	:	public BufferObject, public DX11APIObjects
{
private:
	ID3D11Buffer*				m_buffer;
protected:
	~DX11Buffer();
public:
	DX11Buffer( unsigned int element_size, unsigned int elementCount, ID3D11Buffer* buff );

	inline ID3D11Buffer*		Get() { return m_buffer; }

	static DX11Buffer*			CreateFromMemory(	const void* buffer,
													unsigned int elementSize,
													unsigned int vertCount,
													ResourceBinding bindFlag,
													ResourceUsage usage = ResourceUsage::RESOURCE_USAGE_STATIC );

	virtual MemoryChunk			CopyData		() override;
};

