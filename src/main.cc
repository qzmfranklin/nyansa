#include "url_count.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const *argv[]) {
    // Verify input arguments.
    if (argc != 2) {
        fprintf(stderr, "Usage: url_count FILE\n");
        return 1;
    }

    UrlCount g;
    time_t ts;
    std::string url;
    std::string buf;
    std::ifstream f(argv[1]);
    while (getline(f, buf)) {
        // Parse a line.
        // For easy reference, an example is (minus the leading spaces):
        //      1407478021|www.facebook.com
        std::stringstream bufs(buf);
        bufs >> ts;
        bufs.ignore(1);
        bufs >> url;

        g.add(ts, url);
    }
    g.output();

    return 0;
}
