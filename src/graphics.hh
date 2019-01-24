#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include "body.hh"

#include <QImage>
#include <QPainter>
#include <QScopedPointer>
#include <QTimer>
#include <QWidget>

#define N 1000

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, int height, int width, int refresh_rate);
    ~Graphics();

  protected:
    void paintEvent(QPaintEvent *);

  private:
    enum Color { black, white };
    int width, height;
    QImage image;
    QScopedPointer<QTimer> timer;
    Body b[N];

  private slots:
    void step();
};

#endif // GRAPHICS_HH
