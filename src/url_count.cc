#include "url_count.h"

UrlCount::UrlCount() : _data(std::make_unique<TotalSummary>()) {}

UrlCount::~UrlCount() {}

void UrlCount::add(const time_t ts, const std::string url) {
    const time_t date = ts - (ts % 86400UL);
    if (_data->find(date) == _data->end()) {
        auto element = std::make_pair(date, DailySummary());
        _data->insert(element);
    }

    // ds is short for DailySummary.
    DailySummary &ds = _data->find(date)->second;
    auto itr = ds.find(url);
    if (itr == ds.end()) {
        auto element = std::make_pair(url, 1);
        ds.insert(element);
    } else {
        itr->second++;
    }
}

void UrlCount::output(std::ostream &s) const {
    const size_t bufsize = 64;
    char *buf = new char[bufsize];
    tm *dateinfo = new tm;
    for (const auto &itr : *_data) {
        // TODO(zhongming): Refactor these two closure-like blocks into
        // anynomous functions.
        { // Output the date line.
            const time_t date = itr.first;
            dateinfo = gmtime_r(&date, dateinfo);
            size_t len = strftime(buf, bufsize, "%m/%d/%Y GMT", dateinfo);
            assert(len > 0);
            s << buf << std::endl;
        }

        { // Output the counts within the day.
            DailySummary ds = itr.second;
            std::vector<std::pair<std::string_view, uint32_t>> sorted_counts(
                ds.begin(), ds.end());
            // Sort the daily report in decreasing order of the hit count.
            std::sort(sorted_counts.begin(), sorted_counts.end(),
                      [](auto &lhs, auto &rhs) -> bool {
                          return lhs.second > rhs.second;
                      });
            for (const auto &itr : sorted_counts) {
                std::string_view url = itr.first;
                const uint32_t count = itr.second;
                s << url << " " << count << std::endl;
            }
        }
    }
    delete[] buf;
    delete dateinfo;
}
