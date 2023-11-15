export module utils;

import <unordered_map>;
import <string>;
import <vector>;

export std::vector<std::string> Split(const std::string& str, const std::string& delim); //splits a string returning a vector of substrings separated by the delimiter

export std::unordered_map<std::string, std::string> ParseUrlArgs(const std::string& urlArgs); //splits a string of URL query parameters into key-value pairs

//export void TestWord();