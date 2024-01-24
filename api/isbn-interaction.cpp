#include <string>
#include <vector>
#include <fstream>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

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

std::string add_new_book(std::string isbn)
{
	pid_t pid;
	int exec_status;

	std::string program_name = "./isbn";
	std::string write = "w";
	char* args[] = {(char*) program_name.c_str(), (char*) isbn.c_str(), (char*) write.c_str(), NULL};

	pid = fork();	
	if (0 == pid) { 
		execvp(args[0], args);
		exit(EXIT_SUCCESS);
	} else if (pid < 0) {
		perror("Adding book, failed to fork");	
		return "Book lookup failed!";
	} else {
		wait(&exec_status);

		if (!WIFEXITED(exec_status)) {
			perror("ISBN exited unexpectedly!");
			return "Book lookup failed!";
		}

		if (0 != WEXITSTATUS(exec_status)) {
			return "Invalid ISBN submitted!";
		}

		return "Book added successfully!";
	}
}
