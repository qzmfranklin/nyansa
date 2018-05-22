package(default_visibility=['//visibility:public'])

cc_binary(
    name = 'url_count',
    srcs = [
        'main.cc',
    ],
    deps = [
        ':url_count_lib',
    ],
)

cc_library(
    name = 'url_count_lib',
    srcs = [
        'url_count.cc',
    ],
    hdrs = [
        'url_count.h',
    ],
    copts = [
        '-std=c++17',
    ],
)

cc_test(
    name = 'url_count_test',
    srcs = [
        'url_count_test.cc',
    ],
    deps = [
        ':url_count_lib',
        '//:gtest_main',
    ],
    testonly = True,
)
