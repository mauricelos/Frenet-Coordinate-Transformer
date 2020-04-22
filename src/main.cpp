///
/// @file main.cpp
///

#include <iostream>

#include "protobuf_message_parser.h"
#include "reference_points.pb.h"
#include "reference_points_transformer.h"

int main()
{
    double user_x_coordinate, user_y_coordinate;

    std::cout << "Please enter your coordinate's x value: ";
    std::cin >> user_x_coordinate;
    std::cout << "Please enter your coordinate's y value: ";
    std::cin >> user_y_coordinate;

    auto reference_points =
        ProtobufMessageParser::ParseProtoMessageFromTxtFile<ReferencePoints>("data/reference_points.pb.txt");

    ReferencePointsTransformer reference_points_transformer{reference_points};

    auto frenet_coordinates =
        reference_points_transformer.CalculateFrenetCoordinatesMultiThread(user_x_coordinate, user_y_coordinate, 12);

    std::cout << "Frenet coordinates, d: " << frenet_coordinates.d << " s: " << frenet_coordinates.s << std::endl;

    return 0;
}