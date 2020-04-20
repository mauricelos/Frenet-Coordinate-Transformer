workspace(name = "frenet_coordinate_transformation")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "spline_lib",
    build_file = "//:spline_lib.BUILD",
    sha256 = "9309186ebd3b0845e9f377d4d610598df43591674d57a2f2de81bfde96f2d001",
    strip_prefix = "spline-master",
    url = "https://github.com/ttk592/spline/archive/master.zip",
)

http_archive(
    name = "googletest",
    build_file = "//:gtest.BUILD",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
)

http_archive(
    name = "com_google_protobuf",
    sha256 = "b679cef31102ed8beddc39ecfd6368ee311cbee6f50742f13f21be7278781821",
    strip_prefix = "protobuf-3.11.2",
    url = "https://github.com/protocolbuffers/protobuf/releases/download/v3.11.2/protobuf-all-3.11.2.tar.gz",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()
