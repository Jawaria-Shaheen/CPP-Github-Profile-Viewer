#define _WIN32_WINNT 0x0A00
#define WINVER 0x0A00
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "httplib.h"
using namespace std;
using namespace httplib;

int main() {
    Server svr;

    auto setCORS = [](Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    };

    svr.Get("/github", [&setCORS](const Request& req, Response& res) {
        setCORS(res);

        if (!req.has_param("username")) {
            res.status = 400;
            res.set_content("{\"error\":\"username param is required\"}", "application/json");
            return;
        }

        string username = req.get_param_value("username");

        Client gh("https://api.github.com");
        gh.set_default_headers({
            {"User-Agent", "CPP-Github-Profile-Viewer"},
            {"Accept",     "application/vnd.github+json"}
        });

        auto profileResult = gh.Get("/users/" + username);
        auto reposResult   = gh.Get("/users/" + username + "/repos?sort=updated&per_page=20");

        if (!profileResult || profileResult->status != 200) {
            res.status = 404;
            res.set_content("{\"error\":\"User not found\"}", "application/json");
            return;
        }

        string combined = "{"
            "\"profile\":" + profileResult->body + ","
            "\"repos\":"   + (reposResult && reposResult->status == 200 ? reposResult->body : "[]") +
        "}";

        res.set_content(combined, "application/json");
    });

    svr.Options(".*", [&setCORS](const Request& req, Response& res) {
        setCORS(res);
        res.status = 204;
    });

    cout << "Server running at http://localhost:8080\n";
    cout << "  GET /github?username=torvalds\n";
    cout.flush();

    svr.listen("0.0.0.0", 8080);
    return 0;
}