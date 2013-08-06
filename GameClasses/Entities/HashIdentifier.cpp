//====================== #INCLUDES ===================================
#include "HashIdentifier.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

HashIdentifier::HashIdentifier(const tstring & value, UINT identifier)
	: Value(value)
	, Identifier(identifier)
{
	GenerateKey();
}

HashIdentifier::~HashIdentifier()
{
	// Do nothing
}

HashIdentifier::HashIdentifier(const HashIdentifier& yRef)
{
	*this = yRef;
}

HashIdentifier& HashIdentifier::operator=(const HashIdentifier& yRef)
{
	if(this == &yRef)
	{
		return *this;
	}

	Key = yRef.Key;
	Value = yRef.Value;
	Identifier = yRef.Identifier;

	return *this;
}

bool HashIdentifier::operator==(const HashIdentifier& rhs) const
{
	return Key == rhs.Key;
}

bool HashIdentifier::operator!=(const HashIdentifier& rhs) const
{
	return !(*this == rhs);
}

bool HashIdentifier::operator<(const HashIdentifier& rhs) const
{
	return Key < rhs.Key;
}

bool HashIdentifier::operator>(const HashIdentifier& rhs) const
{
	return Key > rhs.Key;
}

bool HashIdentifier::operator<=(const HashIdentifier& rhs) const
{
	return (*this) < rhs || (*this) == rhs;
}

bool HashIdentifier::operator>=(const HashIdentifier& rhs) const
{
	return (*this) > rhs || (*this) == rhs;
}


void HashIdentifier::SetValue(const tstring & value)
{
	Value = value;
	GenerateKey();
}

void HashIdentifier::SetIdentifier(UINT identifier)
{
	Identifier = identifier;
	GenerateKey();
}

void HashIdentifier::GenerateKey()
{
	Key = Identifier;
	Key = Key << 32;
	Key += LemmingsHelpers::GenerateHash(Value);
}