#pragma once

#include <optional>
#include "bonsoir_service.h"

namespace bonsoir_windows {
    BonsoirService::BonsoirService(std::string _name, std::string _type, int _port, std::optional<std::string> _host, std::map<std::string, std::string> _attributes) :
        name(_name),
        type(_type),
        port(_port),
        host(_host),
        attributes(_attributes)
    {}

    EncodableMap BonsoirService::to_encodable() {
        auto encodableAttributes = EncodableMap{};
        for (auto const& [key, value] : attributes) {
            encodableAttributes.insert({ EncodableValue(key), EncodableValue(value) });
        }
        return EncodableMap{
            { EncodableValue("service.name"), EncodableValue(name) },
            { EncodableValue("service.type"), EncodableValue(type) },
            { EncodableValue("service.port"), EncodableValue(port) },
            { EncodableValue("service.host"), host.has_value() ? EncodableValue(host.value()) : nullptr},
            { EncodableValue("service.attributes"), encodableAttributes },
        };
    }
    std::string BonsoirService::get_description() {
        std::string attributes_string = "{";
        for (auto const& [key, value] : attributes) {
            attributes_string += (key + "=" + value + ", ");
        }
        attributes_string = attributes_string.substr(0, attributes_string.length() - 2);
        attributes_string += "}";
        return "{" + name + ", " + type + ", " + std::to_string(port) + ", " + host.value_or("NULL") + ", " + attributes_string + "}";
    }

    bool BonsoirService::operator==(const BonsoirService& other) const {
        if (name != other.name || type != other.type || port != other.port || host != other.host) {
            return false;
        }
        return attributes.size() == other.attributes.size() && std::equal(attributes.begin(), attributes.end(), other.attributes.begin());
    }
}