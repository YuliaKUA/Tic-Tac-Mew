#include "StandardCursor.h"

#ifdef SFML_SYSTEM_WINDOWS

sf::StandardCursor::StandardCursor(const sf::StandardCursor::TYPE t)
{
	switch (t)
	{
	case sf::StandardCursor::HAND:
		Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	case sf::StandardCursor::NORMAL:
		Cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	}
}

void sf::StandardCursor::set(const sf::WindowHandle& aWindowHandle) const
{
	SetClassLongPtr(aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}

sf::StandardCursor::~StandardCursor() {}

#elif 

#endif