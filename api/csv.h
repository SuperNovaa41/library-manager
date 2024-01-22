#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>

std::string strip_quotes(std::string input);

int get_next_comma(std::string input);

std::vector<std::string> get_csv_as_vector(std::string input);



#endif
