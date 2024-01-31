#include <string>
#include <vector>
#include <fstream>
#include <sqlite3.h>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "isbn-interaction.h"

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

std::vector<std::string> get_db_headers(sqlite3* db)
{
	int i;
	std::vector<std::string> res;
	sqlite3_stmt* getmsgs;

	sqlite3_prepare(db, "SELECT * FROM books;", -1, &getmsgs, NULL);
	sqlite3_step(getmsgs);
	for (i = 0; i < sqlite3_column_count(getmsgs); i++)
		res.push_back(sqlite3_column_name(getmsgs, i));

	sqlite3_finalize(getmsgs);
	return res;
}

std::string get_all_books()
{
	int rc, i;
	sqlite3* db;
	char* text;
	std::string total_lines;
	std::vector<std::string> book_vec;
	std::vector<std::string> header_vec;

	std::ifstream file("books.db");
	if (!file.is_open())
		return "No books found!\n";
	file.close();

	rc = sqlite3_open("books.db", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		exit(EXIT_FAILURE);
	}

	total_lines += "{\"books\": [";

	header_vec = get_db_headers(db);

	sqlite3_stmt* getmsgs;
	sqlite3_prepare(db, "SELECT * FROM books;", -1, &getmsgs, NULL);
	while(sqlite3_step(getmsgs) == SQLITE_ROW) {
		book_vec.clear();
		for (i = 0; i < sqlite3_column_count(getmsgs); i++) {
			text = (char*) sqlite3_column_text(getmsgs, i);
			book_vec.push_back(std::string(text));
		}
		total_lines += book_vec_to_json(header_vec, book_vec) + ",";
	}
	sqlite3_finalize(getmsgs);
	sqlite3_close(db);

	// remove trailing comma
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

