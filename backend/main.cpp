#include <iostream>
#include "httplib.h"
using namespace std;

using namespace httplib;

int main() {
    Server svr;

    svr.Get("/", [](const Request& req, Response& res) {
        res.set_content("Hello from C++ backend ", "text/plain");
    });

    cout << "Server running at http://localhost:8080\n";

    svr.listen("0.0.0.0", 8080);

    return 0;
}