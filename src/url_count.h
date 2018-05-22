#ifndef _URL_COUNT_H
#define _URL_COUNT_H

#include <climits>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <string_view>

class UrlCount {
  public:
    UrlCount();
    virtual ~UrlCount();

    /*
     * Add a pair of (timestamp, url) into the counter.
     *
     * ts: Time stamp since epoch.  It is rounded to UTC days internally.
     * url: The URL to add.
     */
    void add(const time_t ts, const std::string url);

    /*
     * Output the report to the given stream.
     *
     * s: The output stream.
     */
    void output(std::ostream &s = std::cout) const;

  private:
    using DailySummary = std::map<const std::string, uint32_t>;
    using TotalSummary = std::map<const time_t, DailySummary>;
    std::unique_ptr<TotalSummary> _data;
};

#endif /* end of include guard */
