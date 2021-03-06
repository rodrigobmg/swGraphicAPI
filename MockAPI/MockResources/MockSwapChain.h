#pragma once


#include "swGraphicAPI/Resources/SwapChain.h"




namespace sw
{


class MockSwapChain : public SwapChain
{
	RTTR_ENABLE( SwapChain )
private:
public:
	explicit				MockSwapChain	( RenderTarget* screenRT );
	virtual					~MockSwapChain	();

	virtual void			Present			( int syncInterval )					override;
	virtual void			Resize			( uint16 newWidth, uint16 newHeight )	override;

public:
	static MockSwapChain*	CreateScreenSwapChain	( RenderTarget* screenRT );
};

}	// sw
