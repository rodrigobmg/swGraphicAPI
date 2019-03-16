/**
@file ResourcesFactory.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "MockInitializer/MockInitializer.h"

#include "MockVertexShader.h"
#include "MockPixelShader.h"
#include "MockComputeShader.h"
#include "MockBuffer.h"
#include "MockTexture.h"
#include "MockRenderTarget.h"
#include "MockInputLayoutDescriptor.h"
#include "MockInputLayout.h"
#include "MockSwapChain.h"
#include "MockPipelineState.h"





typedef sw::MockTexture				TextureObject;
typedef sw::MockVertexShader		VertexShaderObject;
typedef sw::MockPixelShader			PixelShaderObject;
typedef sw::MockBuffer				BufferObject;
typedef sw::MockComputeShader		ComputeShaderObject;
typedef sw::MockDepthStencilState	DepthStencilStateObject;
typedef sw::MockRasterizerState		RasterizerStateObject;
typedef sw::MockBlendingState		BlendingStateObject;




namespace sw
{


// ================================ //
//
Texture*						ResourcesFactory::CreateTextureFromMemory		( const MemoryChunk& texData, sw::TextureInfo&& texInfo )
{
	return TextureObject::CreateFromMemory( texData, std::move( texInfo ) );
}

// ================================ //
//
sw::Nullable< VertexShader* >		ResourcesFactory::CreateVertexShader			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	return VertexShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< PixelShader* >		ResourcesFactory::CreatePixelShader				( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	return PixelShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< ComputeShader* >		ResourcesFactory::CreateComputeShader			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	return ComputeShaderObject::CreateFromCode( fileName, code, entrypoint );
}

// ================================ //
//
sw::Nullable< ShaderInputLayout* >	ResourcesFactory::CreateInputLayout				( const InputLayoutDescriptor& layoutDesc )
{
	return sw::MockInputLayout::CreateLayout( layoutDesc );
}

// ================================ //
//
sw::Nullable< Texture* >			ResourcesFactory::CreateTextureFromMemory		( const BufferRaw& texData, sw::TextureInfo&& texInfo )
{
	return TextureObject::CreateFromMemory( texData, std::move( texInfo ) );
}


/**@brief Tworzy obiekt vertex shadera.

@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od kt�rej ma si� rozpocz�� wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
VertexShader*		ResourcesFactory::CreateVertexShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	auto shader = VertexShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief Tworzy obiekt vertex shadera oraz layout wierzcho�ka.

@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od kt�rej ma si� rozpocz�� wykonanie programu shadera.
@param[out] layout Zwraca obiekt layoutu.
@param[in] layoutDesc Deskryptor opisuj�cy layout.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
VertexShader*		ResourcesFactory::CreateVertexShaderFromFile	( const std::wstring& fileName,
																	  const std::string& shaderName,
																	  ShaderInputLayout** layout,
																	  InputLayoutDescriptor* layoutDesc,
																	  const char* shaderModel/* = "vs_4_0"*/ )
{
	auto shader = VertexShaderObject::CreateFromFile( fileName, shaderName, layout, layoutDesc, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief Creates BlendingState.*/
sw::Nullable< BlendingState* >		ResourcesFactory::CreateBlendingState		( const BlendingInfo& info )
{
	return BlendingStateObject::Create( info );
}

/**@brief Creates RasterizerState*/
sw::Nullable< RasterizerState* >	ResourcesFactory::CreateRasterizerState		( const RasterizerStateInfo& info )
{
	return RasterizerStateObject::Create( info );
}

/**@brief Creates DepthStencilState.*/
sw::Nullable< DepthStencilState* >	ResourcesFactory::CreateDepthStencilState	( const DepthStencilInfo& info )
{
	return DepthStencilStateObject::Create( info );
}


/**@brief Tworzy obekt pixel shadera.
@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od kt�rej ma si� rozpocz�� wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
PixelShader*		ResourcesFactory::CreatePixelShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	auto shader = PixelShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
	if( shader )
	{
		shader->SetFileName( fileName );
		shader->SetShaderName( shaderName );
	}
	return shader;
}

/**@brief */
GeometryShader*		ResourcesFactory::CreateGeometryShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return nullptr;
}

/**@brief */
EvaluationShader*	ResourcesFactory::CreateEvaluationShaderFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return nullptr;
}

/**@brief */
ControlShader*		ResourcesFactory::CreateControlShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return nullptr;
}

/**@brief Tworzy obekt compute shadera.
@param[in] fileName Nazwa pliku z kodem shadera.
@param[in] shaderName Nazwa funkcji, od kt�rej ma si� rozpocz�� wykonanie programu shadera.
@param[in] shaderModel Shader model.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.*/
ComputeShader*		ResourcesFactory::CreateComputeShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return ComputeShaderObject::CreateFromFile( fileName, shaderName, shaderModel );
}


/**@brief Tworzy bufor na podstawie sanych w pami�ci.

@param[in] name Buffer name or file path.
@param[in] data Pointer to initialization data. Memory can be released after call.
@param[in] bufferInfo Buffer descriptor.
@return Zwraca wska�nik na obiekt bufora lub nullptr w przypadku niepowodzenia.*/
sw::Nullable< Buffer* >					ResourcesFactory::CreateBufferFromMemory		( const std::wstring& name, const uint8* data, const BufferInfo& bufferInfo )
{
	return BufferObject::CreateFromMemory( name, data, bufferInfo );
}

/**Tworzy object RenderTargetObject z bufora tylnego ekranu.

@return Zwraca object RenderTargetObject.*/
RenderTargetObject*						ResourcesFactory::CreateScreenRenderTarget		()
{
	return sw::MockRenderTarget::CreateScreenRenderTarget();
}

// ================================ //
//
SwapChain*								ResourcesFactory::CreateScreenSwapChain			( RenderTargetObject* screenRT )
{
	return sw::MockSwapChain::CreateScreenSwapChain( screenRT );
}

// ================================ //
//
IGraphicAPIInitializer*					ResourcesFactory::CreateAPIInitializer			()
{
	return new sw::MockInitializer();
}

/**Tworzy obiekt deskryptora layoutu.*/
InputLayoutDescriptor*					ResourcesFactory::CreateInputLayoutDescriptor	( const std::wstring& layoutName )
{
	return new sw::MockInputLayoutDescriptor( layoutName );
}

// ================================ //
//
RenderTargetObject*						ResourcesFactory::CreateRenderTarget			( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	return sw::MockRenderTarget::CreateRenderTarget( name, renderTargetDescriptor );
}


}	// sw


