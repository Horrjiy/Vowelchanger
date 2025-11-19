#include "includes.hpp"

static std::string convert_buffer(const wchar_t *buffer)
{
	if (!buffer || !*buffer)
		return (NULL);
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
	if (sizeNeeded <= 0)
		return (NULL);
	std::string result(sizeNeeded - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &result[0], sizeNeeded, nullptr, nullptr);
	return result;
}

std::string file_processing(const wchar_t *buffer)
{
	// convert the buffer to a std::string
	std::string filename = convert_buffer(buffer);
	if (filename.empty())
		return (NULL);

	// get file content
	std::ifstream ifile(filename);
	if (!ifile.is_open())
		return (NULL);
	std::ofstream ofile(filename + ".replace");
	if (!ofile.is_open())
		return (NULL);
	std::stringstream tempstream;
	std::string content;
	tempstream << ifile.rdbuf();
	content = tempstream.str();

	// replace text
	size_t pos;
	std::string result;
	const std::string vowel = "aeiouAEIOU";
	for (int i = 0; i <= 4; i++)
	{
		pos = 0;
		while ((pos = content.find_first_of(vowel, pos)) != std::string::npos)
		{
			content.replace(pos, 1, 1, vowel[i]);
			pos++;
		}
		result += content + "\n\n";
	}
	ofile << result;
	return (filename);
}
