#pragma once

#include <vector>

#include <glibmm.h>

#include "cmdictionary.h"
#include "mytypes.h"
#include "cword.h"

class CBalda
{
private:
	CMDictionary dictionary;
	
	static bool compare_len (const Glib::ustring &a, const Glib::ustring &b);
	static bool compare (const Glib::ustring &a, const Glib::ustring &b);
	void walk (std::vector < std::vector < SMyGUniChar > > &char_map, int x, int y, CWord word, std::vector < Glib::ustring > &result);

public:
	CBalda ();
	CBalda (const CMDictionary &_dictionary);	
	
	std::vector < Glib::ustring > calc (const std::vector < std::vector < SMyGUniChar > > &_char_map);
};
