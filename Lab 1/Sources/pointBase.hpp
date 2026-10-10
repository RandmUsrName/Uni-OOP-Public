#pragma once

#include <string>

// why does this even exist now?
class PointClass {
    public:
        PointClass() = default;

        virtual std::string toString() const = 0;
        virtual std::string repr() const = 0;
};