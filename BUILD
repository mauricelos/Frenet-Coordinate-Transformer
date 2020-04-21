load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library", "cc_test")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "reference_points",
    srcs = ["data/reference_points.proto"],
)

cc_proto_library(
    name = "cc_proto_reference_points",
    deps = [
        ":reference_points",
    ],
)

filegroup(
    name = "reference_points_data",
    srcs = ["data/reference_points.pb.txt"],
)

cc_library(
    name = "frenet_coordinate_lib",
    srcs = [
        "src/reference_points_transformer.cpp",
    ],
    hdrs = [
        "include/protobuf_message_parser.h",
        "include/reference_points_transformer.h",
    ],
    data = [":reference_points_data"],
    includes = [
        "data",
        "include",
        "src",
    ],
    strip_include_prefix = "include",
    deps = [
        ":cc_proto_reference_points",
        "@spline_lib",
    ],
)

cc_binary(
    name = "frenet_coordinate_transformer",
    srcs = ["src/main.cpp"],
    deps = [":frenet_coordinate_lib"],
)

cc_binary(
    name = "benchmark_calculate_frenet_coordinates",
    srcs = ["benchmark/benchmark_calculate_frenet_coordinates.cpp"],
    deps = [
        ":frenet_coordinate_lib",
        "@benchmark",
    ],
)

cc_test(
    name = "frenet_coordinate_transformer_test",
    srcs = [
        "test/protobuf_message_parser_test.cpp",
        "test/reference_points_transformer_test.cpp",
    ],
    deps = [
        ":frenet_coordinate_lib",
        "@googletest//:gtest_main",
    ],
)
