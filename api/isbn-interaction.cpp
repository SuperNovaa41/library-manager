#include <cinttypes>
#include <string>
#include <vector>
#include <fstream>

#include <unistd.h>

#include "isbn-interaction.h"
#include "csv.h"

#define BOOK_FILENAME "books.csv"

std::string book_vec_to_json(std::vector<std::string> headers, std::vector<std::string> book)
{
	int i;
	std::string out = "{";
	for (i = 0; i < book.size(); i++) {
		out += "\"" + headers[i] + "\":";
		out += "\"" + book[i] + "\",";
	}
	return out + "}";

}

std::string get_all_books()
{
	std::ifstream file;
	int file_exists;
	std::string line, total_lines;
	std::vector<std::string> book_vec;
	std::vector<std::string> header_vec;

	file.open(BOOK_FILENAME);

	if (!file.good()) {
		fprintf(stderr, "Theres no books available!\n"); 
		return "No books saved!";
	}

	std::getline(file, line); 
	
	// this contains the headers so that we can fill the json file
	header_vec = get_csv_as_vector(line); 

	total_lines = "{";	
	while (std::getline(file, line)) {
		book_vec = get_csv_as_vector(line);
		total_lines += book_vec_to_json(header_vec, book_vec) + ",";
	}

	return total_lines + "}";
}

void add_new_book(std::string isbn)
{
	pid_t pid;


	std::string program_name = "./isbn";
	std::string write = "w";
	const char* args[] = {program_name.c_str(), isbn.c_str(), write.c_str()};

	pid = fork();	
	if (0 == pid) { // 
		// this is the child
	}

	//TODO execvp the args blah blah
}
