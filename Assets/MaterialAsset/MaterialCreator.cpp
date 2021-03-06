/**
@file MaterialCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/MaterialAsset/stdafx.h"

#include "MaterialCreator.h"
#include "MaterialAssetInitData.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{

// ================================ //
//
Nullable< Resource* >	    MaterialCreator::Create		    ( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
    TypeID type = createInfo.get_type();
    if( type == TypeID::get< MaterialInitData >() )
    {
        return new MaterialAsset( assetName, std::move( static_cast< MaterialInitData&& >( createInfo ) ) );
    }

    return "[MaterialCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >	    MaterialCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
    assert( !"Buffer is not cacheable" );
    return nullptr;
}

// ================================ //
//
BufferRaw					MaterialCreator::SaveToRaw	    ( const IAssetCreateInfo& createInfo )
{
    assert( !"Buffer is not cacheable" );
    return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					MaterialCreator::SaveToRaw	    ( ResourcePtr< Resource > resource )
{
    assert( !"Buffer is not cacheable" );
    return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						MaterialCreator::IsCacheable	            () const
{
    return false;
}

// ================================ //
//
bool						MaterialCreator::SupportsResourceToRaw      () const
{
    return false;
}

// ================================ //
//
TypeID						MaterialCreator::GetAssetType	            () const
{
    return TypeID::get< MaterialAsset >();
}

// ================================ //
//
MaterialCreatorPtr			MaterialCreator::CreateCreator			()
{
    return std::make_shared< MaterialCreator >();
}


}	// sw
