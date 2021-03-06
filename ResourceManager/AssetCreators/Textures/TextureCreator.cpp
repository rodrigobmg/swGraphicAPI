/**
@file TextureCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "TextureCreator.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swGraphicAPI/Resources/Textures/TextureInitData.h"

#include "MipMapGenerator.h"


namespace sw
{

// ================================ //
//
Nullable< Resource* >		TextureCreator::Create		( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< TextureInitData >() )
	{
		auto& typedInitData = static_cast< TextureInitData& >( createInfo );

		TextureInfo info;
		info.Width = typedInitData.Width;
		info.Height = typedInitData.Height;
		info.ArraySize = typedInitData.ArraySize;
		info.CPURead = typedInitData.TextureUsage.CPURead;
		info.CPUWrite = typedInitData.TextureUsage.CPUWrite;
		info.AllowShareResource = typedInitData.TextureUsage.AllowShareResource;
		info.IsCubeMap = typedInitData.IsCubeMap;
		info.GenerateMipMaps = typedInitData.MipMaps.GenerateMipMaps;
		info.TextureType = typedInitData.TextureType;
		info.Usage = typedInitData.TextureUsage.Usage;
		info.Format = typedInitData.Format;
		info.MipMapFilter = typedInitData.MipMaps.Filter;
		info.MipMapLevels = typedInitData.NumMipMapLevels();
		info.CutOffMipMaps = typedInitData.MipMaps.CutOffMipMaps;

		if( typedInitData.MipMaps.GenerateMipMaps )
		{
			MipMapGenerator generator;
			auto result = generator.Generate( typedInitData.Data, info );

			if( !result.IsValid() )
				return result.GetError();

			return ResourcesFactory::CreateTextureFromMemory( assetName, result.Get(), std::move( info ) );
		}
		else
			return ResourcesFactory::CreateTextureFromMemory( assetName, typedInitData.Data, std::move( info ) );
	}
	else if( type == TypeID::get< TextureExistingInitInfo >() )
	{
		// This initialization makes possible to add render target textures to
		// ResourceManager. We don't create anything, because Texture already exists
		// but external layers will add this asset to resources.
		auto& typedInitData = static_cast< TextureExistingInitInfo& >( createInfo );
		return typedInitData.Tex.Ptr();
	}

    return fmt::format( "[TextureCreator] IAssetCreateInfo of type [{}] not supported.", type );
}

// ================================ //
//
Nullable< Resource* >		TextureCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					TextureCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					TextureCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						TextureCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						TextureCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						TextureCreator::GetAssetType	() const
{
	return TypeID::get< Texture >();
}



}	// sw
