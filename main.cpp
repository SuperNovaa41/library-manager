#include <crow.h>
#include <crow/app.h>

#include <fstream>

#include "csv.h"

#define BOOK_FILENAME "books.csv"
typedef struct book_t  {
	std::string isbn;
	std::string title;
	std::string authors;
	int year_of_publication;
	int page_len;
} book_t;

std::string book_json_output(std)

std::string get_all_books()
{
	std::ifstream file;
	int file_exists;
	std::string line, total_lines;
	book_t book;

	file.open(BOOK_FILENAME);

	if (!file.good()) {
		fprintf(stderr, "Theres no books available!\n"); 
		return "No books saved!";
	}

	std::getline(file, line); // theres probably a better way to skip the first line
	
	std::vector<std::string> book_vec;

	while (std::getline(file, line)) {
		book_vec = get_csv_as_vector(line);
		total_lines += print_vec(book_vec);
	}

	return total_lines;
}

std::string print_hello()
{
	return "Hello, world!";
}

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([](){
		return crow::response(print_hello());
	});

	CROW_ROUTE(app, "/books")([](){
		return crow::response(get_all_books());
	});

	app.port(18080).run();

}
