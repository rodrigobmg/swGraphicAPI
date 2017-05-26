#pragma once
/**@file ResourceObject.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik zawiera deklaracj� i definicj� klasy ResourceObject s�u��c�
do zliczania odwo�a� do obiektu.*/

#include "swCommonLib/Common/EngineObject.h"


class ResourceObject;

typedef uint32 ResourceID;

namespace sw
{
	template< class ResourceType > class ResourceContainer;
}


/**@brief Class Restricts access to some functions only for chosen classes.*/
template< typename ResType >
class ResourceAccessKey
{
	friend class nResourceManager;
	friend class sw::ResourceContainer< ResType >;

private:
	ResourceAccessKey() = default;							///< Only friend class can create key.
	ResourceAccessKey( const ResourceAccessKey& ) {}		///< Only friend class can create key.
	ResourceAccessKey( const ResourceAccessKey&& ) {}		///< Only friend class can create key.
public:
};



/**@brief Base class for all assets and resources. It supports reference counting.
@ingroup GraphicAPI

Resource can be referenced from multiple actors or other assets. All references should remember to increment and decrement
reference counter to avoid deletion. Use class ResourcePtr for this purpose.

@todo Zliczanie referencji w ResourceObject nie nadaje si� do wielow�tkowo�ci. Poprawi� w odpowiednim momencie.
*/
class ResourceObject	: public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND;
	friend class ObjectDeleter< ResourceObject >;

private:
	unsigned int			m_objectReferences;	///< Liczba asset�w, kt�re sie odwo�uj�. @todo To powinien by� std::atomic_uint, ale wtedy nie kompiluje si� z CLRem.
	ResourceID				m_uniqueId;			///< Unikalny identyfikator zasobu.

protected:
	virtual ~ResourceObject() = default;		///<Nie ka�dy mo�e skasowa� obiekt

public:
	/**Ustawia zerow� liczb� odwo�a�.*/
	ResourceObject( ResourceID id )
	{
		m_objectReferences = 0;
		m_uniqueId = id;
	}

	/**@todo Add ResourceAccessKey*/
	inline void			SetID( ResourceID id ) { m_uniqueId = id; }	///<Ustawia identyfikator obiektu

	///sprawdza czy mo�na zwolni� zmienn�
	inline bool			CanDelete( unsigned int& objectRef );
	inline bool			CanDelete();

	inline void			Delete	( ResourceAccessKey< ResourceObject > ) { delete this; }

	/**Funkcje s�u��ce do zarz�dzania odwo�aniami.
	Nale�y pilnowa�, aby wszystkie funkcje, kt�re modyfikuj� jakiekolwiek przypisania obiekt�w
	do tekstur, materia��w i meshy, modyfikowa�y r�wnie� ilo�� odwo�a�.
	U�ytkownik silnika powinien mie� udost�pnion� wartstw� po�redniczac�, �eby nie musia�
	pami�ta� o odwo�aniach.*/
	inline void			AddAssetReference()		{ ++m_objectReferences; }	///< Dodaje odwo�anie plikowe do assetu
	inline void			AddObjectReference()	{ ++m_objectReferences; }	///< Dodaje odwo�anie bezpo�rednie obiektu do assetu
	inline void			DeleteAssetReference()	{ --m_objectReferences; }	///< Kasuje odwo�anie plikowe do assetu
	inline void			DeleteObjectReference()	{ --m_objectReferences; }	///< Kasuje odwo�anie bezpo�rednie obiektu do assetu

	inline ResourceID	GetID()			{ return m_uniqueId; }		///< Zwraca identyfikator nadany assetowi

	virtual std::string GetResourceName() const = 0;				///< Zwraca nazw� zasobu. To mo�e by� nazwa pliku, na podstawie kt�rego stworzono zas�b, ale zasadniczo interpretacja jest dowolna.

public:

	virtual bool		IsCacheable		() { return false;  }
};




//----------------------------------------------------------------------------------------------//
//									ResourceObject											//
//----------------------------------------------------------------------------------------------//

//==============================================================================================//



/**@brief Funkcja informuje czy obiekt s� obiektu, kt�re odwo�uj� si� do assetu.

@param[out] file_ref W zmiennej zostanie umieszczona liczba referencji plikowych.
@param[out] other_ref W zmiennej zostanie umieszczona liczba referencji bezpo�rednich od obiekt�w.
@return Zwraca warto�� logiczn� m�wi�c� czy asset nadaje si� do usuni�cia.
*/
inline bool ResourceObject::CanDelete( unsigned int& objectRef )
{
	objectRef = m_objectReferences;

	if( m_objectReferences == 0 )
		return true;
	return false;
}

/**@brief Funkcja informuje czy obiekt s� obiektu, kt�re odwo�uj� si� do assetu.

@return Zwraca warto�� logiczn� m�wi�c� czy asset nadaje si� do usuni�cia.
*/
inline bool ResourceObject::CanDelete()
{
	if( m_objectReferences == 0 )
		return true;
	return false;
}
