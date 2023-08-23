#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

// HTTP
httplib::Server svr;

// HTTPS
httplib::SSLServer svr;

svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
res.set_content("Test!", "text/plain");
});

svr.listen("0.0.0.0", 8080);
