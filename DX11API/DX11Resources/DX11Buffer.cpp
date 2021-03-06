/**
@file DX11Buffer.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11Buffer.h"
#include "DX11Initializer/DX11ConstantsMapper.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11Buffer >( "sw::DX11Buffer" );
}


namespace sw
{

// ================================ //
//
DX11Buffer::DX11Buffer			( const AssetPath& name, const BufferInfo& descriptor, ID3D11Buffer* buff )
	: Buffer( name, descriptor.ElementSize, descriptor.NumElements ), m_buffer( buff )
	, m_descriptor( descriptor )
{
	if( IsDebugLayerEnabled() )
	{
		std::string nameStr = name.String();
		SetDebugName( m_buffer.Get(), nameStr );
	}
}

// ================================ //
//
DX11Buffer::~DX11Buffer()
{
	m_buffer = nullptr;
}


// ================================ //
//
sw::Nullable< Buffer* >				DX11Buffer::CreateFromMemory	( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo )
{
	ResourceBinding bindFlag;
	if( bufferInfo.BufferType == BufferType::VertexBuffer )
		bindFlag = ResourceBinding::RB_VertexBuffer;
	else if( bufferInfo.BufferType == BufferType::IndexBuffer )
		bindFlag = ResourceBinding::RB_IndexBuffer;
	else if( bufferInfo.BufferType == BufferType::ConstantBuffer )
		bindFlag = ResourceBinding::RB_ConstantsBuffer;

	// Wype�niamy deskryptor bufora
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = DX11ConstantsMapper::Get( bufferInfo.Usage );
	bufferDesc.BindFlags = DX11ConstantsMapper::Get( bindFlag );
	bufferDesc.ByteWidth = bufferInfo.NumElements * bufferInfo.ElementSize;

	D3D11_SUBRESOURCE_DATA* initDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA initData;
	if( data )
	{
		// Je�eli bufor nie istnieje to do funkcji tworz�cej bufor powinni�my poda� nullptr.
		ZeroMemory( &initData, sizeof( initData ) );
		initData.pSysMem = data;
		initDataPtr = &initData;
	}

	HRESULT result;
	ID3D11Buffer* newBuffer;
	result = device->CreateBuffer( &bufferDesc, initDataPtr, &newBuffer );
	if( FAILED( result ) )
		return "[DX11Buffer] Buffer creation failed.";

	DX11Buffer* newBufferObject = new DX11Buffer( name, bufferInfo, newBuffer );
	return newBufferObject;
}


/**@brief Kopiuje pami�� bufora i zwraca w MemoryChunku.

Funkcja zwraca zawarto�� bufora. Pami�� jest kopiowana dwukrotnie.
Najpierw na GPU do tymczasowego bufora, a potem po zmapowaniu na pami�� RAM,
odbywa si� kopiowanie do MemoryChunka.

@todo Nie trzeba by wykonywa� kopiowania na GPU, gdyby bufor by� stworzony z flag�
D3D11_USAGE_STAGING lub D3D11_USAGE_DEFAULT. Trzeba sprawdzi� flagi i robi� kopiowanie tylko, gdy to konieczne.

@attention Funkcja nie nadaje si� do wykonania wielow�tkowego. U�ywa DeviceContextu do kopiowania danych
w zwi�zku z czym wymaga synchronizacji z innymi funkcjami renderuj�cymi.
*/
MemoryChunk									DX11Buffer::CopyData()
{
	// Trzeba stworzy� nowy bufor
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	//bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;		// Przy fladze usage::staging nie mo�na bindowa� zasobu do potoku graficznego.
	bufferDesc.ByteWidth = m_elementSize * m_elementCount;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	HRESULT result;
	ID3D11Buffer* newBuffer;
	result = device->CreateBuffer( &bufferDesc, nullptr, &newBuffer );
	if( FAILED( result ) )
		return MemoryChunk();

	// Kopiowanie zawarto�ci mi�dzy buforami
	device_context->CopyResource( newBuffer, m_buffer.Get() );

	D3D11_MAPPED_SUBRESOURCE data;
	result = device_context->Map( newBuffer, 0, D3D11_MAP::D3D11_MAP_READ, 0, &data );
	if( FAILED( result ) )
		return MemoryChunk();

	MemoryChunk memoryChunk;
	memoryChunk.MemoryCopy( (int8*)data.pData, m_elementSize * m_elementCount );

	device_context->Unmap( newBuffer, 0 );
	newBuffer->Release();

	return std::move( memoryChunk );
}


}	// sw

