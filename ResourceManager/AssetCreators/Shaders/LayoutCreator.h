#pragma once
/**
@file LayoutCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"


namespace sw
{



/**@brief Creator for input layout.*/
class LayoutCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		LayoutCreator		() = default;
	virtual			~LayoutCreator		() = default;

public:

	virtual ResourceObject*			Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual ResourceObject*			LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< ResourceObject > resource )									override;

	virtual bool					SupportsResourceToRaw	() override;
	virtual TypeID					GetAssetType			() override;

public:

};



}	// sw
