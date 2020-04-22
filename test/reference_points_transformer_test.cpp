///
/// @file reference_points_transformer_test.cpp
///

#include <gtest/gtest.h>

#include "protobuf_message_parser.h"

#define private public
#include "reference_points_transformer.h"

namespace
{

class ReferencePointsTransformerTest : public ::testing::Test
{
  public:
    const double threshold_{0.001};
    const std::string path_to_protobuf_txt_file_{"data/reference_points.pb.txt"};
    const std::string expected_error_message_{"No reference line was created, not enough reference points given!"};
    ReferencePoints reference_points_{};
    ReferencePointsTransformer reference_points_transformer_{reference_points_};

    virtual void SetUp()
    {
        reference_points_ =
            ProtobufMessageParser::ParseProtoMessageFromTxtFile<ReferencePoints>(path_to_protobuf_txt_file_);

        ReferencePointsTransformer temp_reference_points_transformer{reference_points_};
        reference_points_transformer_ = temp_reference_points_transformer;
    }
};

TEST_F(ReferencePointsTransformerTest, GetReferenceLineTest)
{
    const double expected_y_value{0.119615256786};

    auto spline = reference_points_transformer_.GetReferenceLine();

    EXPECT_NEAR(spline(0.0), expected_y_value, threshold_);
}

TEST_F(ReferencePointsTransformerTest, CalculateFrenetCoordinatesTestLeftFromSpline)
{
    auto frenet_coordinates = reference_points_transformer_.CalculateFrenetCoordinates(20.0, 2.0);

    EXPECT_NEAR(frenet_coordinates.d, -1.9441, threshold_);
    EXPECT_NEAR(frenet_coordinates.s, 19.9891, threshold_);
}

TEST_F(ReferencePointsTransformerTest, CalculateFrenetCoordinatesTestRightFromSpline)
{
    auto frenet_coordinates = reference_points_transformer_.CalculateFrenetCoordinates(20.0, 0.0);

    EXPECT_NEAR(frenet_coordinates.d, 0.0557, threshold_);
    EXPECT_NEAR(frenet_coordinates.s, 19.9991, threshold_);
}

TEST_F(ReferencePointsTransformerTest, CalculateFrenetCoordinatesMultiThreadTestLeftFromSpline)
{
    auto frenet_coordinates = reference_points_transformer_.CalculateFrenetCoordinatesMultiThread(20.0, 2.0, 12);

    EXPECT_NEAR(frenet_coordinates.d, -1.9441, threshold_);
    EXPECT_NEAR(frenet_coordinates.s, 19.9891, 0.01);
}

TEST_F(ReferencePointsTransformerTest, CalculateFrenetCoordinatesMultiThreadTestRightFromSpline)
{
    auto frenet_coordinates = reference_points_transformer_.CalculateFrenetCoordinatesMultiThread(20.0, 0.0, 12);

    EXPECT_NEAR(frenet_coordinates.d, 0.0557, threshold_);
    EXPECT_NEAR(frenet_coordinates.s, 19.9991, 0.01);
}

TEST_F(ReferencePointsTransformerTest, SetFrenetCalculationBoundariesTest)
{
    reference_points_transformer_.SetFrenetCalculationBoundaries(-20.0, 100.0);

    EXPECT_DOUBLE_EQ(reference_points_transformer_.start_x_, -20.0);
    EXPECT_DOUBLE_EQ(reference_points_transformer_.end_x_, 100.0);
}

TEST_F(ReferencePointsTransformerTest, CreateReferenceLineTest)
{
    const double expected_y_value{0.119615256786};

    reference_points_transformer_.CreateReferenceLine(reference_points_);

    EXPECT_NEAR(reference_points_transformer_.spline_(0.0), expected_y_value, threshold_);
}

TEST_F(ReferencePointsTransformerTest, CalculateEuclideanDistanceTest)
{
    auto distance = reference_points_transformer_.CalculateEuclideanDistance(0.0, 1.0, 2.0, 0.0);

    EXPECT_NEAR(distance, 2.2360, threshold_);
}

TEST_F(ReferencePointsTransformerTest, CalculateSignTestRightFromSpline)
{
    auto sign = reference_points_transformer_.CalculateSign(0.0, 1.0, 2.0, 0.0);

    EXPECT_DOUBLE_EQ(sign, 1.0);
}

TEST_F(ReferencePointsTransformerTest, CalculateSignTestLeftFromSpline)
{
    auto sign = reference_points_transformer_.CalculateSign(0.0, 1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(sign, -1.0);
}

}  // namespace