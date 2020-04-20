///
/// @file protobuf_message_parser.h
///

#ifndef PROTOBUF_MESSAGE_PARSER_H
#define PROTOBUF_MESSAGE_PARSER_H

#include <string>
#include <fcntl.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include "reference_points.pb.h"

class ProtobufMessageParser
{
  public:
    static inline void CheckProtobufVersion() { GOOGLE_PROTOBUF_VERIFY_VERSION; }
    template <typename T>
    static T ParseProtoMessageFromTxtFile(const std::string& file_path)
    {
        CheckProtobufVersion();
        T protobuf_container{};

        auto reference_points_file{open(file_path.c_str(), O_RDONLY)};
        google::protobuf::io::FileInputStream file_stream(reference_points_file);
        google::protobuf::TextFormat::Parse(&file_stream, &protobuf_container);

        return protobuf_container;
    }
};

#endif  // PROTOBUF_MESSAGE_PARSER_H
