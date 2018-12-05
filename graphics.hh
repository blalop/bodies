#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <QImage>
#include <QPainter>
#include <QWidget>

class graphics : public QWidget {
    Q_OBJECT

  public:
    graphics(QWidget *parent, int height, int width);
    ~graphics();
    void refresh(QImage image);

  protected:
    void paintEvent();

  private:
    QImage image;
};

#endif // GRAPHICS_HH
