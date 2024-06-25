#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

// trim from start (in place)
inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
	trim(s);
	return s;
}

struct item
{
	std::vector<std::string> lines;

	std::string name;
	std::string message;
	std::string func;

	std::string returnType;
	std::string returnValue;

	std::vector<std::string> argsName;
	std::vector<std::string> argsValue;
};

std::vector<std::string> parse_line(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;

	std::vector<std::string> collection;



	while (std::getline(file, line))
	{
		trim(line);

		collection.push_back(line);
	}

	return collection;
}

std::vector<item*> parse_item_collection(std::vector<std::string>& line_collection)
{
	std::vector<item*> item_collection;
	item* o = nullptr;

	std::string line;
	std::string next_line;


	std::size_t i;
	std::size_t count;


	count = line_collection.size();
	for(i=0; i<count; i++)
	{
		line = line_collection[i];
		if ((i+1)<count)
		{
			next_line = line_collection[i+1];
		}
		else
		{
			next_line.clear();
		}


		if (line.size()>4)
		{
			if (line.substr(0, 3) == "// ")
			{
				if (*(line.rbegin()) == ')')
				{
					if (next_line.substr(0, 8) == "#define ")
					{
						o = new item;
					}
				}
			}
		}

		if (o)
		{
			o->lines.push_back(line);
		}


		if (o)
		{
			if (*(line.rbegin()) == '}')
			{
				item_collection.push_back(o);

				o = nullptr;
			}
		}
	}

	return item_collection;
}

void parse_item(item* o)
{
	o->name = o->lines[0];

	
}

void output_item(std::string& s)
{

}

int main() 
{
	std::string filename = "atlcrack.h";


	std::vector<std::string> line_collection;
	
	
	line_collection = parse_line(filename);


	std::vector<item*> item_collection;
	
	
	item_collection = parse_item_collection(line_collection);



	for (auto& i : item_collection)
	{
		parse_item(i);
	}


	std::string output;


	for (auto& i : item_collection)
	{
		output_item(output);
	}


	return 0;
}