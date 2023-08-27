#include "webserv.hpp"

void loop(Config &conf);

// note about error pages, nginx doesn't use <meta> when error page starts with a slash,
// but appends it to the request and redirects if it contains any other slashes
// and redirects without appending when there's no slash
// it searches for (root + route + error_page)

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	try
	{
		Config conf = (argc > 1 ? Config(argv[1]) : Config());

		// conf.getLocationData("127.0.0.1", "8080", "server2", "/a").printEverything("");
		loop(conf);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
}
