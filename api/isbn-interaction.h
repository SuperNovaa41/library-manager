#ifndef ISBN_INTERACTION_H
#define ISBN_INTERACTION_H

enum ISBN_EXIT_CODE {
	FORK_FAILED,
	PROGRAM_EXIT_UNEXPECTED,
	PROGRAM_SUCCESS,
	PROGRAM_FAIL
};


/**
 * std::string book_vec_to_json
 * std::vector<std::string> headers - Vector of strings that contain the type information of the data
 * std::vector<std::string> book - Vector of strings that contain the data
 *
 * Helper function that converts a vector of book data into a json format
 */
std::string book_vec_to_json(std::vector<std::string> headers, std::vector<std::string> book);

/**
 * std::string get_all_books
 *
 * This will return all the currently saved books.
 */
std::string get_all_books();

std::string add_new_book(std::string isbn);

enum ISBN_EXIT_CODE run_isbn_program(char* args[]);


#endif
