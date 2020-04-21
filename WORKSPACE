workspace(name = "frenet_coordinate_transformation")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "spline_lib",
    build_file = "//:spline_lib.BUILD",
    sha256 = "9309186ebd3b0845e9f377d4d610598df43591674d57a2f2de81bfde96f2d001",
    strip_prefix = "spline-master",
    url = "https://github.com/ttk592/spline/archive/master.zip",
)

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

git_repository(
    name = "benchmark",
    remote = "https://github.com/google/benchmark",
    tag = "v1.5.0",
)

git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/protocolbuffers/protobuf",
    tag = "v3.11.4",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()
