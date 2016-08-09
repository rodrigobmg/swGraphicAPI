#pragma once

#include "../DX11Initializer/DX11APIObjects.h"
#include "GraphicAPI\MeshResources.h"


/**@brief Implementacja tekstury w DirectX 11.
@ingroup DX11API*/
class DX11Texture	:	public TextureObject, public DX11APIObjects
{
private:
	ID3D11ShaderResourceView*				m_textureView;
	ID3D11Texture2D*						m_texture;
protected:
	~DX11Texture();
public:
	DX11Texture( const std::wstring& path, ID3D11ShaderResourceView* tex );
	DX11Texture( ID3D11Texture2D* tex, ID3D11ShaderResourceView* texView );


	inline ID3D11ShaderResourceView*		Get() { return m_textureView; }

	bool									SaveToFile				( const std::string& filePath ) override;

	static DX11Texture*						CreateFromFile			( const std::wstring& fileName );
	static DX11Texture*						CreateFromMemory		( const MemoryChunk& texData, TextureInfo&& texInfo );
};

