#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

#include "Sources/point2D.hpp"
#include "Sources/utils.hpp"

using namespace std;

void listPoints(const vector<Point2D>& vec, bool listAddr = false) {
    if (vec.size() > 0) {
        for (int i = 0; i < vec.size(); i++) {
            if (listAddr) {cout << i << " | " << vec[i].repr() << " at: " << &vec[i] << "\n";}
            else {cout << i << " | " << vec[i].repr() << "\n";}
        }
    }
    else {cout << "Nothing to list \n";}
};

void pointSelector(vector<Point2D>& vec) {
    string opt;
    if (vec.size() == 0) {cout << "Add a point first\n\nPress any key to continue..." << endl; getch(); return;}
    while (true) {
        if (system("CLS")) {system("clear");}
        opt = utils::CInputManager("Select a point. Esc to quit\n>> ", regex("^\\d+$"), false, true);
        if (opt == "esc") {return;}

        int optInt = stoi(opt);
        if (optInt > vec.size()-1) {cout << ">>> Bad Input <<< \n\nPress any key to continue..." << endl; getch(); continue;}

        Point2D& pnt = vec[optInt];
        while (true) {
            if (system("CLS")) {system("clear");}
            cout << "selected Point: " << optInt << " | " << pnt.repr() << "\n";
            string innerOpt = utils::CInputManager("What to do?. Esc to quit\n1. set X\n2. set Y\n3. get distance to other point\n4. get origin\n5. list points\n", regex("^\\d+$"), true, false);
            if (innerOpt == "esc") {break;}

            int innerOptInt = stoi(innerOpt);
            switch (innerOptInt) {
                case 1: {
                    string xStr = utils::CInputManager("input new x coordinate. Esc to quit\n>> ", regex("^\\d+(.\\d+)?+$"), false, true);
                    if (xStr == "esc") {break;}
                    pnt.setX(stod(xStr));
                    break;
                }
                case 2: {
                    string yStr = utils::CInputManager("input new y coordinate. Esc to quit\n>> ", regex("^\\d+(.\\d+)?+$"), false, true);
                    if (yStr == "esc") {break;}
                    pnt.setY(stod(yStr));
                    break;
                }
                case 3: {
                    string otherInd = utils::CInputManager("Select other point. Esc to quit\n>> ", regex("^\\d+$"), false, true);
                    if (otherInd == "esc") {cout << "\n"; break;}
                        
                    int otherIndInt = stoi(otherInd);
                    if (otherIndInt > vec.size()-1) {cout << ">>> Bad Input <<< \n\nPress any key to continue..." << endl; getch(); break;}

                    Point2D& pnt2 = vec[otherIndInt];
                    cout << "Other point: " << pnt2.repr() <<  "\ndistance = " << pnt.distanceTo(pnt2) << endl; getch();

                    break;
                }
                case 4: cout << "origin: " << pnt.origin().repr() << endl << "\n\n Press any key to continue..." << endl; getch(); break;
                case 5: listPoints(vec); cout << "\nPress any key to continue..." << endl; getch(); break;
                default: break;
            }
        }
    }

}

void addPoints(vector<Point2D>& vec) {
    string mode = utils::CInputManager("How to add?\n1. From polar\n2. Empty\n3. Clone existing\n", regex("^\\d+$"), true, false);
    if (mode == "esc") {return;}
    
    switch(stoi(mode)) {
        case 1: {
            string opt = utils::CInputManager("Input radius and angle, separated by comma. Esc to quit\n>> ", regex("^\\d+(.\\d+)?,\\s*\\d+(.\\d+)?$"), false, true);
            if (opt == "esc") {break;}

            int sepPos = opt.find(",");
            string rad = opt.substr(0, sepPos);
            string angle = opt.substr(sepPos+1);
            int i = 0;
            for (;i < angle.size() && std::isspace(angle[i]); i++) {}
            angle.erase(0, i);

            vec.push_back(Point2D::fromPolar(stod(rad), stod(angle)));
            break;
        }
        case 2: {
            string opt = utils::CInputManager("How many points to add? Esc to quit\n>> ", regex("^\\d+$"), false, true);
            if (opt == "esc") {break;}

            int optInt = stoi(opt);
            for (int i = 0; i < optInt; i++) {
                vec.push_back(Point2D(0, 0));
            }

            break;   
        }
        case 3: {
            if (vec.size() == 0) {cout << "Nothing to copy \n\nPress any key to continue..." << endl; getch(); break;}
            string opt = utils::CInputManager("Select a point. Esc to quit\n>> ", regex("^\\d+$"), false, true);
            if (opt == "esc") {break;}

            int optInt = stoi(opt);
            if (optInt > vec.size()-1) {cout << ">>> Bad Input <<< \n\nPress any key to continue..." << endl; getch(); break;}

            const Point2D& pnt = vec[optInt];
            vec.push_back(pnt.clone());

            break;
        }
        default: break;
    }
}

void calcDistance() {
    string pointStr;
    while (true) {
        pointStr = utils::CInputManager("input points as string, formated as: (x1,y1); (x2,y2). Esc to quit\n>> ", regex("^\\(\\d+(.\\d+)?,\\d+(.\\d+)?\\);\\s*\\(\\d+(.\\d+)?,\\d+(.\\d+)?\\)$"), false, true);
        if (pointStr == "esc") {break;}

        int sepPos = pointStr.find(";");
        string p1 = pointStr.substr(0, sepPos);
        string p2 = pointStr.substr(sepPos+1);
        int i = 0;
        for (;i < p2.size() && std::isspace(p2[i]); i++) {}
        p2.erase(0, i);

        int p1Sep = p1.find(",");
        double p1_x = stod(p1.substr(1, p1Sep));
        double p1_y = stod(p1.substr(p1Sep+1, p1.length()-1));

        int p2Sep = p2.find(",");
        double p2_x = stod(p2.substr(1, p2Sep));
        double p2_y = stod(p2.substr(p2Sep+1, p2.length()-1));

        cout << "Distance = " << Point2D::distanceBetween(tuple<double, double>(p1_x, p1_y), tuple<double, double>(p2_x, p2_y)) << "\n\n";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<Point2D> pointsVec = {};

    string option;
    while (true) {
        if (system("CLS")) {system("clear");}
        option = utils::CInputManager("What to do? Esc to quit\n1. List Points\n2. Select a Point\n3. Add Points\n4. Calculate distance between points(static)\n5. Get Total Created Point Ammount\n", regex("^\\d+$"), true, false);
        if (option == "esc") {break;}

        if (system("CLS")) {system("clear");}

        int optInt = stoi(option);
        switch (optInt) {
            case 1: listPoints(pointsVec, true); cout << "\nPress any key to continue..." << endl; getch(); break;
            case 2: pointSelector(pointsVec); break;
            case 3: addPoints(pointsVec); break;
            case 4: calcDistance(); break;
            case 5: cout << "Created Total = " << Point2D::getCreatedPointsTotal() << "\n\nPress any key to continue..." << endl; getch(); break;
            default: break;
        }
    }

    return 0;
}