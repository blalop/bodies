#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include "body.hh"

#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <QWidget>

#define N 10000

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, int height, int width, int refresh_rate);
    ~Graphics();
    enum Color { black, white };

  protected:
    void paintEvent(QPaintEvent *);

  private:
    int width, height;
    QImage image;
    QTimer *timer;
    Body b[N];

  private slots:
    void step();
};

#endif // GRAPHICS_HH
