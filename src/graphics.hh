#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QWidget>

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, int height, int width, int refresh_rate);
    ~Graphics();
    enum Color { black, white };

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    QImage image;
    QTimer *timer;
    int height, width;

  private slots:
    void calculate();

};

#endif // GRAPHICS_HH
