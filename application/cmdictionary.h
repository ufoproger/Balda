#pragma once

#include <fstream>
#include <vector>
#include <map>

#include <glibmm.h>

#include "mytypes.h"
#include "cword.h"

class CMDictionary
{
	private:
		std::map < Glib::ustring , bool > words;
		
		void readDefFile (std::ifstream &fin);		
		void readPreFile (std::ifstream &fin);
		void writePreFile (std::ofstream &fout);
		void writeDefFile (std::ofstream &fout);
		
	public:
		CMDictionary ();
		CMDictionary (const Glib::ustring &filename);
		
		void readFromFile (const Glib::ustring &filename);
		void writeToFile (const Glib::ustring &filename);
		bool findPrefix (CWord prefix, std::vector < Glib::ustring > &result);
		size_t size () const;
};
