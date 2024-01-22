#include <crow.h>
#include <crow/app.h>

#include <fstream>

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
