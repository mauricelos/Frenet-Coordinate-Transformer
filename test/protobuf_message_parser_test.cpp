///
/// @file protobuf_message_parser_test.cpp
///

#include <gtest/gtest.h>

#include "protobuf_message_parser.h"

namespace
{

class ProtobufMessageParserTest : public ::testing::Test
{
  public:
    std::string path_to_protobuf_txt_file_{"data/reference_points.pb.txt"};
    const int expected_num_of_reference_points_{22};
};

TEST_F(ProtobufMessageParserTest, CheckProtobufVersionTest)
{
    ProtobufMessageParser::CheckProtobufVersion();
    EXPECT_TRUE(true);
}

TEST_F(ProtobufMessageParserTest, ParseProtoMessageFromTxtFileTest)
{
    auto reference_points =
        ProtobufMessageParser::ParseProtoMessageFromTxtFile<ReferencePoints>(path_to_protobuf_txt_file_);
    EXPECT_EQ(reference_points.points_size(), expected_num_of_reference_points_);
}

}  // namespace