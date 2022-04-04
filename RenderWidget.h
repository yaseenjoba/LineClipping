// Last modified by: Yaseen Joba (181033), on 2.03.2021



#pragma once

#include <QWidget>
#include <vector>
#include <string>

class RenderWidget : public QWidget
{
    Q_OBJECT

  public:
    RenderWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
	void drawClippingWindow(float Xmin, float Xmax, float Ymin, float Ymax);
    void drawInitialLine(float x1, float y1, float x2, float y2);
    void clipLine(float x1, float y1, float x2, float y2 , float Xmin, float Xmax, float Ymin, float Ymax);
    void getDirections(float x, float y, float Xmin, float Xmax, float Ymin, float Ymax);
  protected:
    void paintEvent(QPaintEvent *event) override;
};
