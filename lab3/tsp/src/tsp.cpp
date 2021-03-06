/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "Point.h"
#include "Tour.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    string filename = "mona-100k.txt";
    ifstream input;
    //input.open("/Users/Hampus/Documents/C++/Qt Projects/tddd86/labb3/tsp/res/"+filename); //MAC

    input.open(filename); // Normal

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    // run insertion heuristic
    Tour tour;
    double x;
    double y;
    auto start = chrono::system_clock::now();
    while (input >> x >> y) {
        Point p(x, y);
        tour.insertNearest(p);
        //tour.draw(scene);
        //Why draw the whole tour every time we add a point?
        //Isn't the point to call draw when it's done?
        //std::chrono::milliseconds dura(50);
        //std::this_thread::sleep_for(dura);
        a.processEvents();
    }
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    input.close();
    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    cout << "Number of points: " << tour.size() << endl;
    tour.show();
    cout << "Computational time: " << elapsed.count() << " ms" << endl;

    // draw tour
    tour.draw(scene);
    return a.exec(); // start Qt event loop
    // setup graphical window
}
