#include <crow.h>
#include <crow/app.h>
#include <fstream>


#include "csv.h"
#include "isbn-interaction.h"

std::string print_hello()
{
	return "server is running!";
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

	CROW_ROUTE(app, "/add/<string>")
		([](std::string isbn)
		 {
		 	return crow::response(add_new_book(isbn));
		 });




	app.port(18080).run();

}
