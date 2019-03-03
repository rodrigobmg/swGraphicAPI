/**
@file DX11VertexShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11VertexShader.h"

#include "DX11InputLayoutDescriptor.h"
#include "DX11InputLayout.h"

#include "DX11Compiler.h"

#include "swCommonLib/Common/MemoryLeaks.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< DX11VertexShader >( "DX11VertexShader" );
}


// ================================ //
//
DX11VertexShader::DX11VertexShader( ID3D11VertexShader* shader )
{
	m_vertexShader = shader;
}

// ================================ //
//
DX11VertexShader::~DX11VertexShader()
{
	if( m_vertexShader )
		m_vertexShader->Release();
	m_vertexShader = nullptr;
}


// ================================ //
//
bool			DX11VertexShader::ReloadFromFile		()
{

	return false;
}

// ================================ //
//
bool			DX11VertexShader::ReloadFromBinFile		()
{

	return false;
}

// ================================ //
//
void			DX11VertexShader::SaveShaderBinFile		( const std::wstring& file_name )
{


}

// ================================ //
//
sw::Nullable< DX11VertexShader* >			DX11VertexShader::CreateFromCode			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	sw::CompilationConfig config( ShaderType::VertexShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto result = sw::DX11Compiler::CreateVertexShader( code, entrypoint, config );

	if( !result.IsValid() )
	{
#ifdef _DEBUG
		OutputDebugStringA( result.GetErrorReason().c_str() );
#endif
		return result;
	}

	result.Get()->SetFileName( fileName );
	result.Get()->SetShaderName( entrypoint );

	return result;
}

// ================================ //
//
DX11VertexShader*		DX11VertexShader::CreateFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	sw::CompilationConfig config( ShaderType::VertexShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto result = sw::DX11Compiler::CreateVertexShader( fileName, shaderName, config );

#ifdef _DEBUG

	if( !result.IsValid() )
	{
		OutputDebugStringA( result.GetErrorReason().c_str() );
		return nullptr;
	}

#endif

	return result.Get();

}

/**@brief Tworzy obiekt DX11VertexShader oraz DX11InputLayout na podstawie pliku. Zwraca również layout dla podanej struktury wierzchołka.
Nie należy używać tej funkcji, jeżeli layout nie jest rzeczywiście potrzebny. Trzeba pamietać o zwolnieniu
go, kiedy przestanie być potrzebny.

W przypadku błędów kompilacji w trybie debug są one przekierowane do okna Output.

Na razie obsługuje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z którego zostanie wczytany shader
@param[in] shaderName Nazwa funkcji, która jest punktem poczatkowym wykonania shadera
@param[out] layout W zmiennej umieszczany jest wskaźnik na layout wierzchołka. Należy pamiętać o zwolnieniu go kiedy będzie niepotrzebny.
@param[in] layoutDesc Deskryptor opisujacy tworzony layout.
@param[in] shaderModel Łańcuch znaków opisujący shader model.
@return Zwraca wskaźnik na obiekt VertexShader lub nullptr w przypadku niepowodzenia.*/
DX11VertexShader* DX11VertexShader::CreateFromFile		( const std::wstring& fileName,
															const std::string& shaderName,
															ShaderInputLayout** layout,
															InputLayoutDescriptor* layoutDesc,
															const char* shaderModel/* = "vs_4_0" */)
{
	sw::CompilationConfig config( ShaderType::VertexShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto compiledBlob = sw::DX11Compiler::CompileShader( fileName, shaderName, config );

	if( !compiledBlob.IsValid() )
	{
		OutputDebugStringA( compiledBlob.GetErrorReason().c_str() );
		return nullptr;
	}

	// Create layout
	if( !layoutDesc )
		return nullptr;

	auto& compiledShader = compiledBlob.Get();

	DX11InputLayoutDescriptor* dx11LayoutDesc = static_cast< DX11InputLayoutDescriptor* >( layoutDesc );
	ID3D11InputLayout* DX11layoutInterface = nullptr;

	D3D11_INPUT_ELEMENT_DESC* layoutDescPtr = dx11LayoutDesc->GetDescriptorPtr();
	Size layoutNumElements = dx11LayoutDesc->GetNumElements();

	HRESULT result = device->CreateInputLayout( layoutDescPtr,
												(UINT)layoutNumElements,
												compiledShader->GetBufferPointer(),
												compiledShader->GetBufferSize(),
												&DX11layoutInterface );

	if( FAILED( result ) )
	{
		layout = nullptr;
		return nullptr;
	}

	ID3D11VertexShader* vertexShader = nullptr;
	result = device->CreateVertexShader( compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &vertexShader );

	if( FAILED( result ) )
	{
		layout = nullptr;
		return nullptr;
	}

	// Tworzymy obiekt nadający się do użycia w silniku i zwracamy wskaźnik na niego
	DX11VertexShader* newShader = new DX11VertexShader( vertexShader );
	*layout = new DX11InputLayout( DX11layoutInterface );
	return newShader;
}

// ================================ //
//
DX11VertexShader*			DX11VertexShader::CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel)
{

	return nullptr;
}

