#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include "map.hh"

#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QWidget>

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, Map map, int iters);
    ~Graphics();

  protected:
    void paintEvent(QPaintEvent *);

  private:
    Map map;
    int iters, counter;
    QImage image;
    QTimer *timer;

    static constexpr int SIZE = 800;
    enum Color { BLACK, WHITE };

  private slots:
    void step();
};

#endif // GRAPHICS_HH
