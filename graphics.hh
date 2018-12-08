#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <QImage>
#include <QPainter>
#include <QWidget>

class Graphics : public QWidget {
    Q_OBJECT

  public:
    Graphics(QWidget *parent, int height, int width);
    ~Graphics();
    void refresh(QImage image);
    enum Color { black, white };

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    QImage image;
};

#endif // GRAPHICS_HH
