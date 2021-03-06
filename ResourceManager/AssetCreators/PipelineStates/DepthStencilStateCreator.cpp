/**
@file DepthStencilStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "DepthStencilStateCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"
#include "swCommonLib/Common/Converters.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"


namespace sw
{

// ================================ //
//
Nullable< Resource* >		DepthStencilStateCreator::Create		( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< DepthStencilInfo >() )
		return ResourcesFactory::CreateDepthStencilState( assetName, static_cast< DepthStencilInfo& >( createInfo ) );

    return fmt::format( "[DepthStencilStateCreator] IAssetCreateInfo of type [{}] not supported.", type );
}

// ================================ //
//
Nullable< Resource* >		DepthStencilStateCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					DepthStencilStateCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					DepthStencilStateCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						DepthStencilStateCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						DepthStencilStateCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						DepthStencilStateCreator::GetAssetType	() const
{
	return TypeID::get< DepthStencilState >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//



}	// sw
