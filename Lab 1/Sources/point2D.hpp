#pragma once

#include <format>
#include <cmath>
#include <numbers>
#include <tuple>

#include "Sources/pointBase.hpp"

// copying a point with a copy constructor creates a separate point instance, therefore increments _CreatedPointsTotal
// calling origin() also increments the counter
class Point2D: public PointClass {
    private:
        double _X;
        double _Y;

        static int _CreatedPointsTotal;

        static double _distanceBetweenPoints(double x1, double y1, double x2, double y2);

    public:
        Point2D(double X, double Y);
        Point2D(const Point2D& other);
        Point2D(Point2D&& other) noexcept;
        //~Point2D();

        std::string toString() const;

        std::string repr() const;

        double x() const;
        double y() const;

        void setX(double X);
        void setY(double Y);

        double distanceTo(const Point2D& other) const;

        Point2D clone() const;

        static double distanceBetween(double x1, double y1, double x2, double y2);
        static double distanceBetween(const std::tuple<double, double>& p1, const std::tuple<double, double>& p2);
        static double distanceBetween(const std::pair<double, double>& p1, const std::pair<double, double>& p2);

        static Point2D origin();

        static Point2D clone(const Point2D& point);

        static Point2D fromPolar(double r, double thetaEuler);

        static int getCreatedPointsTotal();
};