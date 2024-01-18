#include "csv.h"

std::string strip_quotes(std::string input)
{
	if (input[0] != '"')
		return input;
	return input.substr(1, input.size() - 1);
		
}

int get_next_comma(std::string input)
{
	int i;
	bool in_string = false;
	for (i = 0; i < input.size(); i++) {
		if (input[i] == '"')
			in_string = !in_string;
		if (input[i] == ',' && !in_string)
			return i;
	}
	return -1;
}

std::vector<std::string> get_csv_as_vector(std::string input)
{
	std::vector<std::string> output;
	int next_comma;

	while ((next_comma = get_next_comma(input)) != -1) {
		output.push_back(input.substr(0, next_comma));
		input = strip_quotes(input.substr(next_comma + 1, input.size()));
	}

	return output;
}
