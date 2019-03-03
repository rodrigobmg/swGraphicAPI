#pragma once
/**
@file MockInputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{


/**@brief 
@ingroup MockAPI*/
class MockInputLayout : public ShaderInputLayout
{
	RTTR_ENABLE( ShaderInputLayout );
private:
protected:

	virtual			~MockInputLayout		();

public:
	explicit		MockInputLayout			();


	static sw::Nullable< MockInputLayout* >		CreateLayout		( const InputLayoutDescriptor& layoutDesc );
};

}	// sw
