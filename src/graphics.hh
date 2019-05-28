#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include "map.hh"

#include <QImage>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include <memory>

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, std::shared_ptr<Map> map, int iters, int trace);
    void saveImage(QString filename) const;

  protected:
    void paintEvent(QPaintEvent *);

  private:
    std::shared_ptr<Map> map;
    int iters, i, trace;
    QImage image;
    std::unique_ptr<QTimer> timer;
    void draw();

    static constexpr int SIZE = 800;
    enum Color { BLACK, WHITE };

  private slots:
    void step();
};

#endif // GRAPHICS_HH
