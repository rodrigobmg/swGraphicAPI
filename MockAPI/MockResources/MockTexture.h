#pragma once
/**
@file MockTexture.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/MeshResources.h"

#include "swCommonLib/Common/Buffers/BufferRaw.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"



namespace sw
{



/**@brief
@ingroup MockAPI*/
class MockTexture : public Texture
{
	RTTR_ENABLE( Texture )
private:

	TextureInfo								m_descriptor;

protected:

	virtual			~MockTexture			();

public:
	explicit								MockTexture				( const AssetPath& name, TextureInfo&& texInfo );

	virtual bool							UpdateData				( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx ) override;
	virtual MemoryChunk						CopyData				() const override;
	virtual const TextureInfo&				GetDescriptor			() const override;

	static MockTexture*						CreateFromMemory		( const MemoryChunk& texData, TextureInfo&& texInfo );
	static sw::Nullable< MockTexture* >		CreateFromMemory		( const AssetPath& name, const BufferRaw& texData, TextureInfo&& texInfo );



private:
	void		Construct	();
};

}	// sw
