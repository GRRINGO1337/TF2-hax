/*
* textfile.cpp
*
*  Created on: Jan 24, 2017
*      Author: nullifiedcat
*/

#include "textfile.h"

#include <fstream>

#include <stdio.h>

TextFile::TextFile()
	: lines{}
{
}

bool TextFile::TryLoad(std::string name)
{
	if (name.length() == 0) return false;
	std::string filename(name);
	std::ifstream file(filename, std::ios::in);
	if (!file)
	{
		return false;
	}
	lines.clear();
	for (std::string line; std::getline(file, line);)
	{
		if (*line.rbegin() == '\r') line.erase(line.length() - 1, 1);
		lines.push_back(line);
	}
	return true;
}

void TextFile::Load(std::string name)
{
	std::string filename(name);
	std::ifstream file(filename, std::ios::in);
	if (file.bad())
		return;
	lines.clear();
	for (std::string line; std::getline(file, line);)
	{
		if (*line.rbegin() == '\r') line.erase(line.length() - 1, 1);
		lines.push_back(line);
	}
}

size_t TextFile::LineCount() const
{
	return lines.size();
}

const std::string& TextFile::Line(size_t id) const
{
	return lines.at(id);
}