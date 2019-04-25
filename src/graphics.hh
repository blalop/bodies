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
    Graphics(QWidget *parent, Map map, int iters);

  protected:
    void paintEvent(QPaintEvent *);

  private:
    static constexpr int SIZE = 800;
    enum Color { BLACK, WHITE };
    Map map;
    int iters, itersCounter;
    QImage image;
    std::unique_ptr<QTimer> timer;

  private slots:
    void step();
};

#endif // GRAPHICS_HH
