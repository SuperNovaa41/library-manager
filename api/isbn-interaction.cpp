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
{ int i;
	std::string out = "{";

	for (i = 0; i < book.size(); i++) {
		out += "\"" + headers[i] + "\":";
		out += "\"" + book[i] + "\",";
	}
	// remove the trailing comma
	out.pop_back();

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

	total_lines = "{ \"books\": [";	
	while (std::getline(file, line)) {
		book_vec = get_csv_as_vector(line);
	
		total_lines += book_vec_to_json(header_vec, book_vec) + ",";
	}

	// remove the trailing comma
	total_lines.pop_back();


	return total_lines + "]}";
}

std::string remove_book(std::string id)
{
	enum ISBN_EXIT_CODE exec_code;
	std::string program_name = "./isbn";
	std::string remove = "remove";

	char* args[] = {(char*) program_name.c_str(), (char*) remove.c_str(), (char*) id.c_str(), NULL};

	exec_code = run_isbn_program(args);

	switch (exec_code) {
		case FORK_FAILED:
			perror("removing book, failed to fork");
			return "Couldn't remove book!";
		case PROGRAM_EXIT_UNEXPECTED:
			perror("ISBN exited unexpectedly");
			return "Couldn't remove book!";
		case PROGRAM_FAIL:
			return "There was an error in removing the book!";
		case PROGRAM_SUCCESS:
			return "Successfully removed book!";
		default:
			return "Unknown error in removing book!";
	}
}


std::string add_new_book(std::string isbn)
{
	enum ISBN_EXIT_CODE exec_code;
	std::string program_name = "./isbn";
	char* args[] = {(char*) program_name.c_str(), (char*) isbn.c_str(), NULL};


	exec_code = run_isbn_program(args);
	
	switch (exec_code) {
		case FORK_FAILED:
			perror("Adding book, failed to fork");
			return "Book lookup failed!";
		case PROGRAM_EXIT_UNEXPECTED:
			perror("ISBN exited unexpectedly");
			return "Book lookup failed!";
		case PROGRAM_FAIL:
			return "Invalid ISBN submitted!";
		case PROGRAM_SUCCESS:
			return "Book added succesfully!";
		default:
			return "Unknown error in adding book!";
	}
}

enum ISBN_EXIT_CODE run_isbn_program(char* args[])
{
	pid_t pid;
	int exec_status;

	pid = fork();
	if (0 == pid) {
		execvp(args[0], args);
		exit(EXIT_SUCCESS);
	} else if (pid < 0) {
		return FORK_FAILED;	
	} else {
		wait(&exec_status);

		if (!WIFEXITED(exec_status))
			return PROGRAM_EXIT_UNEXPECTED;
		if (0 != WEXITSTATUS(exec_status))
			return PROGRAM_FAIL;
		return PROGRAM_SUCCESS;
	}
}

