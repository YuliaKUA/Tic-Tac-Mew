#ifndef STANDARDCURSOR_H
#define STANDARDCURSOR_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef SFML_SYSTEM_WINDOWS
#include <windows.h>
#elif defined(SFML_SYSTEM_LINUX)
#else

#endif

namespace sf
{
	class StandardCursor
	{
	private:
#ifdef SFML_SYSTEM_WINDOWS

		HCURSOR Cursor;

#endif
	public:
		enum TYPE { NORMAL, HAND };
		StandardCursor(const TYPE t);
		void set(const WindowHandle& aWindowHandle) const;
		~StandardCursor();
	};
}

#endif 