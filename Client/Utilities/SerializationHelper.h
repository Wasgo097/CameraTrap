#pragma once
#include <nlohmann/json.hpp>
enum class SerializationType
{
	Simple,
	Binary
};

NLOHMANN_JSON_SERIALIZE_ENUM(SerializationType, {
    {SerializationType::Simple, "Simple"},
    {SerializationType::Binary, "Binary"}
    })