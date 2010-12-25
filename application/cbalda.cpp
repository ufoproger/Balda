#include "cbalda.h"
		
bool CBalda::compare_len (const Glib::ustring &a, const Glib::ustring &b)
{
	return (a.length() == b.length()) ? (a > b) : (a.length() > b.length());
}

bool CBalda::compare (const Glib::ustring &a, const Glib::ustring &b)
{
	return (a == b);
}

void CBalda::walk (std::vector < std::vector < SMyGUniChar > > &char_map, int x, int y, CWord word, std::vector < Glib::ustring > &result)
{
	if (char_map[x][y].f && char_map[x][y].ch == Glib::ustring(".")[0])
	{
		Glib::ustring letters("йцукенгшщзхъфывапролджэюбьтимсчя");
	
		for (int i = 0; i < 32; ++i)
		{
			char_map[x][y].ch = letters[i];					
			walk(char_map, x, y, word, result);
		}
	}
	else
	{
		if (!word.push(char_map[x][y]) || !dictionary.findPrefix(word, result))
			return;
	
		int mov_x[4] = {0, -1, 0, 1};
		int mov_y[4] = {1, 0, -1, 0};

		for (int k = 0; k < 4; ++k)
		{
			int _x = x + mov_x[k];
			int _y = y + mov_y[k];
	
			if (_x < 0 || _x > 4 || _y < 0 || _y > 4)
				continue;
	
			walk(char_map, _x, _y, word, result);
		}
	}
}

CBalda::CBalda ()
{
}

CBalda::CBalda (const CMDictionary &_dictionary)
{
	dictionary = _dictionary;
}

std::vector < Glib::ustring > CBalda::calc (const std::vector < std::vector < SMyGUniChar > > &_char_map)
{
	std::vector < Glib::ustring > result;
	std::vector < std::vector < SMyGUniChar > > char_map = _char_map;

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			char_map = _char_map;
			walk(char_map, i, j, CWord(), result);
		}

	std::sort(result.begin(), result.end(), compare_len);		
	result.resize(std::unique(result.begin(), result.end(), compare) - result.begin()); 

	return result;
}
