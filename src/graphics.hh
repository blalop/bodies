#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include "body.hh"
#include "map.hh"
#include "vector2d.hh"

#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include <memory>

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, double dim, int n, int i);

  protected:
    void paintEvent(QPaintEvent *);

  private:
    enum Color { black, white };
    double dim;
    Map map;
    int iters, itersCounter;
    QImage image;
    std::unique_ptr<QTimer> timer;
    void drawPoints();

  private slots:
    void step();
};

#endif // GRAPHICS_HH
