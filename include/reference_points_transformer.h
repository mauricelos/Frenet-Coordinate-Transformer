///
/// @file reference_points_transformer.h
///

#ifndef REFERENCE_POINTS_TRANSFORMER_H
#define REFERENCE_POINTS_TRANSFORMER_H

#include "spline.h"

#include "reference_points.pb.h"

struct FrenetCoordinates
{
    double s;
    double d;
};

class ReferencePointsTransformer
{
  public:
    ReferencePointsTransformer() = delete;
    ReferencePointsTransformer(const ReferencePoints& reference_points);
    tk::spline GetReferenceLine() { return spline_; };
    FrenetCoordinates CalculateFrenetCoordinates(const double coordinate_x,
                                                 const double coordinate_y,
                                                 const double precision = 0.001);
    void SetFrenetCalculationBoundaries(const double spline_start_x_value, const double spline_end_x_value);

  private:
    void CreateReferenceLine(const ReferencePoints& reference_points);
    double CalculateEuclideanDistance(const double x1, const double x2, const double y1, const double y2);
    double CalculateSign(const double x1, const double x2, const double y1, const double y2);

    static constexpr int min_num_reference_points{3};
    tk::spline spline_{};
    double start_x_{0.0};
    double end_x_{0.0};
};

#endif  // REFERENCE_POINTS_TRANSFORMER_H
