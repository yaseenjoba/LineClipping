// Last modified by: Yaseen Joba (181033), on 2.03.2021


#include "RenderWidget.h"
#include <QPainter>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string>Directions;
RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
  // to be implemeted later
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(800, 1100);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
  
  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(QPen(Qt::black, 2));
  int w = width() / 2;
  int h = height() / 2;
  int windowSize = 200;
  float Xmin = w - windowSize, Xmax = w + windowSize, Ymin = h + windowSize, Ymax = h - windowSize;
  drawClippingWindow(Xmin, Xmax, Ymin, Ymax);
  float x1 = Xmin -50, y1 = Ymin + 200, x2 = Xmax + 200, y2 = Ymax - 200;
  drawInitialLine(x1, y1, x2, y2);
  clipLine(x1, y1, x2, y2 , Xmin, Xmax, Ymin, Ymax);

  
}
void RenderWidget::drawClippingWindow(float Xmin, float Xmax, float Ymin, float Ymax) {
    QPainter painter(this);
    QColor color(0, 0, 0);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(Xmin, Ymin, Xmin, Ymax);//left
    painter.drawLine(Xmin, Ymin, Xmax, Ymin);//bottom
    painter.drawLine(Xmax, Ymin, Xmax, Ymax);//right
    painter.drawLine(Xmin, Ymax, Xmax, Ymax);//up
    
}
void RenderWidget::drawInitialLine(float x1, float y1, float x2, float y2) {
    QPainter painter(this);
    QColor color(0, 0, 0);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(x1, y1, x2, y2);
}
void RenderWidget::clipLine(float x1, float y1, float x2, float y2 , float Xmin, float Xmax, float Ymin, float Ymax) {
    QPainter painter(this);
    QColor color(255, 0, 0);
    painter.setPen(QPen(Qt::red, 2));
    //clip the first point.
    getDirections(x1, y1, Xmin, Xmax, Ymin, Ymax);

    while (Directions.size() != 0) {
        for (auto i : Directions) {
            if (i == "L") {
               int y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1);
               int x = Xmin;
               x1 = x;
               y1 = y;
               getDirections(x1, y1, Xmin, Xmax, Ymin, Ymax);
               break;
            }
            if (i == "R") {
               int y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1);
               int x = Xmax;
               x1 = x;
               y1 = y;
               getDirections(x1, y1, Xmin, Xmax, Ymin, Ymax);
               break;
            }
            if (i == "B") {
                int x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1);
                int y = Ymin;
                x1 = x;
                y1 = y;
                getDirections(x1, y1, Xmin, Xmax, Ymin, Ymax);
                break;
            }
            if (i == "T") {
                int x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1);
                int y = Ymax;
                x1 = x;
                y1 = y;
                getDirections(x1, y1, Xmin, Xmax, Ymin, Ymax);
                break;
            }
        }
    }
    //clip the second point.
    getDirections(x2, y2, Xmin, Xmax, Ymin, Ymax);
    while (Directions.size() != 0) {
        for (auto i : Directions) {
            if (i == "L") {
                int y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1);
                int x = Xmin;
                x2 = x;
                y2 = y;
                getDirections(x2, y2, Xmin, Xmax, Ymin, Ymax);
                break;
            }
            if (i == "R") {
                int y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1);
                int x = Xmax;
                x2 = x;
                y2 = y;
                getDirections(x2, y2, Xmin, Xmax, Ymin, Ymax);
                break;
            }
            if (i == "B") {
                int x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1);
                int y = Ymin;
                x2 = x;
                y2 = y;
                getDirections(x2, y2, Xmin, Xmax, Ymin, Ymax);
                break;
            }
            if (i == "T") {
                int x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1);
                int y = Ymax;
                x2 = x;
                y2 = y;
                getDirections(x2, y2, Xmin, Xmax, Ymin, Ymax);
                break;
            }
        }
    }
    painter.drawLine(x1, y1, x2, y2);

}
void RenderWidget::getDirections(float x, float y, float Xmin, float Xmax, float Ymin, float Ymax) {
    Directions.clear();
    //check if the point in.
    if (x >= Xmin && x <= Xmax && y <= Ymin && y >= Ymax) {
        return;
    }
    // test against left:
    if (x < Xmin) {
        Directions.push_back("L");
    }
    // test against right:
    if (x > Xmax) {
        Directions.push_back("R");
    }
    // test against Up:
    if (y < Ymax){
        Directions.push_back("T");

    }
    // test against Up:
    if (y > Ymin) {
        Directions.push_back("B");
    }
}