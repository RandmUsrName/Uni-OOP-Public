#include "Sources/point2D.hpp"
#include <iostream>

int Point2D::_CreatedPointsTotal = 0;

double Point2D::_distanceBetweenPoints(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return std::sqrt(dx*dx + dy*dy);
}

Point2D::Point2D(double X, double Y) : _X(X), _Y(Y) {_CreatedPointsTotal++;}
Point2D::Point2D(const Point2D& other) : _X(other._X), _Y(other._Y) {_CreatedPointsTotal++;}
Point2D::Point2D(Point2D&& other) noexcept : _X(other._X), _Y(other._Y) {other._X = 0.0; other._Y = 0.0;}

//Point2D::~Point2D() {_pointsCount--;}

double Point2D::x() const {return _X;}
double Point2D::y() const {return _Y;}

void Point2D::setX(double X) {_X = X;}
void Point2D::setY(double Y) {_Y = Y;}

std::string Point2D::toString() const {return std::format("({:.2f}, {:.2f})", _X, _Y);}
std::string Point2D::repr() const {return std::format("Point2D(x={:.2f}, y={:.2f})", _X, _Y);}

double Point2D::distanceTo(const Point2D& other) const {
    return _distanceBetweenPoints(_X, _Y, other._X, other._Y);
}

Point2D Point2D::origin() {return Point2D(0.0, 0.0);}

Point2D Point2D::clone() const {return Point2D(*this);}
Point2D Point2D::clone(const Point2D& point) {return Point2D(point);}

Point2D Point2D::fromPolar(double r, double thetaEuler) {
    double thetaRad = thetaEuler * std::numbers::pi / 180;
    double x = r * std::cos(thetaRad);
    double y = r * std::sin(thetaRad);

    return Point2D(x, y);
};

double Point2D::distanceBetween(double x1, double y1, double x2, double y2) {return _distanceBetweenPoints(x1, y1, x2, y2);}

double Point2D::distanceBetween(const std::tuple<double, double>& p1, const std::tuple<double, double>& p2) {
    return _distanceBetweenPoints(std::get<0>(p1), std::get<1>(p1), std::get<0>(p2), std::get<1>(p2));
}

double Point2D::distanceBetween(const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
    return _distanceBetweenPoints(p1.first, p1.second, p2.first, p2.second);
}

int Point2D::getCreatedPointsTotal() {return _CreatedPointsTotal;}