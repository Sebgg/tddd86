/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt. While doing executing the same task as brute.cpp
 * fast does this way faster.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <utility>

using namespace std;

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

/*
 * Draws specified dot on given scene object
 */
void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

/*
 * Draws a line between two specified points on scene.
 */
void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}


/*
 * computing function which firsts puts all points with the same
 * slope to a given starting point in the same "bucket".
 * The buckets containing more than 3 points are sorted
 * and finally a line is drawn between the points in the bucket
 * and the starting point.
 */
void computeLines(vector<Point> points, const Point& orgPnt, QGraphicsScene* scene){
    map<double, vector<Point>> bucket;

    for(Point p : points){
        if(orgPnt < p){
            bucket[orgPnt.slopeTo(p)].push_back(p);
        }
    }

    for(auto const &key : bucket){
        if(key.second.size() > 2){
            vector<Point> tmpVec = key.second;
            render_line(scene, orgPnt, tmpVec.back());
        }
    }

}


/*
 * Main function
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input100.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);

    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());

    // create watch to count time taken to compute
    auto begin = chrono::high_resolution_clock::now();
    for(auto const &p : points){
        computeLines(points, p, scene);
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}

