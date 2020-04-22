#include <benchmark/benchmark.h>

#include "protobuf_message_parser.h"
#include "reference_points_transformer.h"

auto reference_points =
    ProtobufMessageParser::ParseProtoMessageFromTxtFile<ReferencePoints>("data/reference_points.pb.txt");
static ReferencePointsTransformer reference_points_transformer_{reference_points};

static void BenchmarkCalculateFrenetCoordinates(benchmark::State& state)
{
    for (auto _ : state)
    {
        reference_points_transformer_.CalculateFrenetCoordinates(40.0, 5.0);
    }
}

static void BenchmarkCalculateFrenetCoordinatesLowerPrecision(benchmark::State& state)
{
    for (auto _ : state)
    {
        reference_points_transformer_.CalculateFrenetCoordinates(40.0, 5.0, 0.01);
    }
}

static void BenchmarkCalculateFrenetCoordinatesMultiThread(benchmark::State& state)
{
    for (auto _ : state)
    {
        reference_points_transformer_.CalculateFrenetCoordinatesMultiThread(40.0, 5.0, 12);
    }
}

static void BenchmarkCalculateFrenetCoordinatesMultiThreadLowerPrecision(benchmark::State& state)
{
    for (auto _ : state)
    {
        reference_points_transformer_.CalculateFrenetCoordinatesMultiThread(40.0, 5.0, 12, 0.01);
    }
}

BENCHMARK(BenchmarkCalculateFrenetCoordinates);
BENCHMARK(BenchmarkCalculateFrenetCoordinatesLowerPrecision);
BENCHMARK(BenchmarkCalculateFrenetCoordinatesMultiThread);
BENCHMARK(BenchmarkCalculateFrenetCoordinatesMultiThreadLowerPrecision);
BENCHMARK_MAIN();