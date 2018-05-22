#include <climits>
#include <ctime>
#include <tuple>

#include <gtest/gtest.h>

#include "url_count.h"

namespace {

/*
 * TODO(zhongming): This test suite needs to be expanded much more than this to
 * cover at least the following cases:
 *      1.  Empty inputs.
 *      2.  Nearly empty and partially empty inputs.
 *      3.  Erroneous inputs, e.g., nullptr, -1, etc..
 *      4.  A good number of combinations of different days, months, years.
 */

TEST(UrlCount, Trivia) {
    /*
     * The test case is a literal translation of the example listed in the
     * following page:
     *      https://sites.google.com/a/nyansa.com/nyansa-programming-exercise
     */

    const std::tuple<const time_t, const char *> data[] = {
        {static_cast<time_t>(1407564301UL), "www.nba.com"},
        {static_cast<time_t>(1407478021UL), "www.facebook.com"},
        {static_cast<time_t>(1407478022UL), "www.facebook.com"},
        {static_cast<time_t>(1407481200UL), "news.ycombinator.com"},
        {static_cast<time_t>(1407478028UL), "www.google.com"},
        {static_cast<time_t>(1407564301UL), "sports.yahoo.com"},
        {static_cast<time_t>(1407564300UL), "www.cnn.com"},
        {static_cast<time_t>(1407564300UL), "www.nba.com"},
        {static_cast<time_t>(1407564300UL), "www.nba.com"},
        {static_cast<time_t>(1407564301UL), "sports.yahoo.com"},
        {static_cast<time_t>(1407478022UL), "www.google.com"},
        {static_cast<time_t>(1407648022UL), "www.twitter.com"}};

    const std::string expected_output = R"(08/08/2014 GMT
www.facebook.com 2
www.google.com 2
news.ycombinator.com 1
08/09/2014 GMT
www.nba.com 3
sports.yahoo.com 2
www.cnn.com 1
08/10/2014 GMT
www.twitter.com 1
)";

    UrlCount g;
    for (auto &&datum : data) {
        const time_t ts = std::get<0>(datum);
        const char *url = std::get<1>(datum);
        g.add(ts, url);
    }
    std::stringstream sbuf;
    g.output(sbuf);
    EXPECT_EQ(expected_output, sbuf.str());
}

} // anonymous namespace
