#include <crow.h>
#include <crow/app.h>

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
		 	crow::response response(add_new_book(isbn));
			response.add_header("Access-Control-Allow-Origin", "*");
		 	return response;
		 });

	CROW_ROUTE(app, "/remove/<string>")
		([](std::string id)
		 {
			return crow::response(remove_book(id));
		 });


	app.port(18080).run();
}
