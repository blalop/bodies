#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#define N 10000

struct Body {
    int x, y, dx, dy;
};

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, int height, int width, int refresh_rate);
    ~Graphics();
    enum Color { black, white };

  protected:
    void paintEvent(QPaintEvent *);

  private:
    QImage image;
    QTimer *timer;
    int height, width;
    Body b[N];

    void drawBody(Body &b);

  private slots:
    void calculate();

};

#endif // GRAPHICS_HH
