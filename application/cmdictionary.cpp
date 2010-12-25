#include "cmdictionary.h"

void CMDictionary::readDefFile (std::ifstream &fin)
{
	std::string line;
	
	while (fin >> line)
	{
		Glib::ustring uline(Glib::ustring(line).lowercase()), us;
		
		for (int i = 0; i < uline.length() - 1; ++i)
		{
			us.push_back(uline[i]);
			
			if (!words[us])
				words[us] = false;
		}
		
		words[uline] = true;
	}
}

void CMDictionary::readPreFile (std::ifstream &fin)
{
	std::string line;
	bool f;
	
	while (fin >> line >> f)
		words[Glib::ustring(line)] = f;		
}

void CMDictionary::writePreFile (std::ofstream &fout)
{
	for (std::map < Glib::ustring , bool >::iterator it = words.begin(); it != words.end(); ++it)
		fout << it->first.lowercase().raw() << " " << it->second << std::endl;
}

void CMDictionary::writeDefFile (std::ofstream &fout)
{
	for (std::map < Glib::ustring , bool >::iterator it = words.begin(); it != words.end(); ++it)
		if (it->second)
			fout << it->first.lowercase().raw() << std::endl;
}

CMDictionary::CMDictionary ()
{
}

CMDictionary::CMDictionary (const Glib::ustring &filename)
{
	readFromFile(filename);
}

void CMDictionary::readFromFile (const Glib::ustring &filename)
{
	std::ifstream fin(filename.c_str());
	
	if (!fin.is_open())
		return;

	if (filename.substr(0, 4) == Glib::ustring("pre_"))
		readPreFile(fin);
	else
		readDefFile(fin);
}

void CMDictionary::writeToFile (const Glib::ustring &filename)
{
	std::ofstream fout(filename.c_str());
	
	if (filename.substr(0, 4) == Glib::ustring("pre_"))
		writePreFile(fout);
	else
		writeDefFile(fout);
}

bool CMDictionary::findPrefix (CWord prefix, std::vector < Glib::ustring > &result)
{
	Glib::ustring s_prefix(prefix.toUstring());
	std::map < Glib::ustring , bool >::iterator it = words.find(s_prefix);
	
	if (it == words.end())
		return false;
		
	if (it->second && prefix.testF())
		result.push_back(s_prefix);
	
	return true;
}

size_t CMDictionary::size () const
{
	return words.size();
}
