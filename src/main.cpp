#include "includes.hpp"

int main(void)
{
	if (startwindow())
		return (1);
	return (0);
}

static std::string convert_buffer(const wchar_t *buffer)
{
	if (!buffer || !*buffer)
		return (NULL);
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
	if (sizeNeeded <= 0)
		return (NULL);
	std::string result(sizeNeeded - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, result.data(), sizeNeeded, nullptr, nullptr);
	return result;
}

int file_processing(const wchar_t *buffer)
{
	// convert the buffer to a std::string
	std::string filename = convert_buffer(buffer);
	if (filename.empty())
		return (0);

	// get file content
	std::ifstream ifile(filename);
	std::ofstream ofile(filename + ".replace");
	if (!ofile.is_open() || !ifile.is_open())
		return (0);
	std::stringstream tempstream;
	std::string content;
	tempstream << ifile.rdbuf();
	content = tempstream.str();

	// replace text
	size_t pos = 0;
	std::string result;
	const std::string vowel = "aeiou";
	for (int i = 0; i <= 4; i++)
	{
		while((pos = content.find_first_of(vowel, pos)) != std::string::npos)	
			content.replace(pos, 1, 1, vowel[i]);
		result += content + "\n";
	}
	ofile << result;
	return (1);
}
