#pragma once

#include <vector>

#include <glibmm.h>

#include "mytypes.h"

class CWord
{
	private:
		std::vector < SMyGUniChar > letters;
		
	public:
		CWord ()
		{
		}
		
		bool testF ()
		{
			for (std::vector < SMyGUniChar >::iterator it = letters.begin(); it != letters.end(); ++it)
				if (it->f)
					return true;
					
			return false;
		}
		
		bool testXY (int x, int y)
		{
			for (std::vector < SMyGUniChar >::iterator it = letters.begin(); it != letters.end(); ++it)
				if (it->x == x && it->y == y)
					return true;
					
			return false;
		}
		
		bool push (SMyGUniChar letter)
		{
			if (letter.f && testF())
				return false;
				
			if (testXY(letter.x, letter.y))
				return false;
				
			letters.push_back(letter);
			
			return true;
		}

		Glib::ustring toUstring ()
		{
			Glib::ustring s;
			
			for (std::vector < SMyGUniChar >::iterator it = letters.begin(); it != letters.end(); ++it)
				s.push_back(it->ch);
				
			return s;
		}
};
