///
/// @file reference_points_transformer.cpp
///

#include <cmath>
#include <iostream>
#include <limits>
#include <future>
#include <utility>
#include <vector>

#include "reference_points_transformer.h"

ReferencePointsTransformer::ReferencePointsTransformer(const ReferencePoints& reference_points)
{
    if (reference_points.points_size() >= min_num_reference_points)
    {
        CreateReferenceLine(reference_points);
        SetFrenetCalculationBoundaries(reference_points.points(0).x(),
                                       reference_points.points(reference_points.points_size() - 1).x());
    }
    else
    {
        std::cerr << "No reference line was created, not enough reference points given!" << std::endl;
    }
}

FrenetCoordinates ReferencePointsTransformer::CalculateFrenetCoordinates(const double coordinate_x,
                                                                         const double coordinate_y,
                                                                         const double precision,
                                                                         const double start_x,
                                                                         const double end_x)
{
    FrenetCoordinates frenet_coordinates{std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};

    double current_s{0.0};
    double closest_x{std::numeric_limits<double>::max()};
    double current_x{(end_x - start_x) > 0.0 ? start_x : end_x};

    while (current_x < ((end_x - start_x) > 0.0 ? end_x : start_x))
    {
        double distance = CalculateEuclideanDistance(current_x, coordinate_x, spline_(current_x), coordinate_y);

        if (distance <= frenet_coordinates.d)
        {
            closest_x = current_x;
            frenet_coordinates.d = distance;
            frenet_coordinates.s = current_s - precision;
        }

        current_s += CalculateEuclideanDistance(
            current_x, current_x - precision, spline_(current_x), spline_(current_x - precision));
        current_x += precision;
    }

    frenet_coordinates.d *= CalculateSign(closest_x, coordinate_x, spline_(closest_x), coordinate_y);

    return frenet_coordinates;
}

FrenetCoordinates ReferencePointsTransformer::CalculateFrenetCoordinatesMultiThread(const double coordinate_x,
                                                                                    const double coordinate_y,
                                                                                    const std::uint8_t num_threads,
                                                                                    const double precision)
{
    FrenetCoordinates frenet_coordinates{0.0, std::numeric_limits<double>::max()};
    std::vector<std::future<FrenetCoordinates>> futures{};
    auto step_size{std::fabs(end_x_ - start_x_) / num_threads};

    for (auto i = 0; i < num_threads; ++i)
    {
        futures.push_back(std::async(std::launch::async, &ReferencePointsTransformer::CalculateFrenetCoordinates, this,
                    coordinate_x,
                    coordinate_y,
                    precision,
                    start_x_ + (i * step_size), start_x_ + ((i + 1) * step_size)));
    }

    for (auto& future : futures)
    {
        auto frenet = future.get();
        if (std::fabs(frenet.d) <= std::fabs(frenet_coordinates.d))
        {
            frenet_coordinates.s += frenet.s;
            frenet_coordinates.d = frenet.d;
        }
    }

    return frenet_coordinates;
}

void ReferencePointsTransformer::SetFrenetCalculationBoundaries(const double spline_start_x_value,
                                                                const double spline_end_x_value)
{
    start_x_ = spline_start_x_value;
    end_x_ = spline_end_x_value;
}

void ReferencePointsTransformer::CreateReferenceLine(const ReferencePoints& reference_points)
{
    std::pair<std::vector<double>, std::vector<double>> temp_coordinate_container{};
    temp_coordinate_container.first.reserve(reference_points.points_size());
    temp_coordinate_container.second.reserve(reference_points.points_size());

    for (const auto& reference_point : reference_points.points())
    {
        temp_coordinate_container.first.push_back(reference_point.x());
        temp_coordinate_container.second.push_back(reference_point.y());
    }

    spline_.set_points(temp_coordinate_container.first, temp_coordinate_container.second);
}

inline double ReferencePointsTransformer::CalculateEuclideanDistance(const double x1,
                                                                     const double x2,
                                                                     const double y1,
                                                                     const double y2)
{
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline double ReferencePointsTransformer::CalculateSign(const double x1,
                                                        const double x2,
                                                        const double y1,
                                                        const double y2)
{
    return (x1 - x2) + (y1 - y2) < 0 ? -1.0 : 1.0;
}