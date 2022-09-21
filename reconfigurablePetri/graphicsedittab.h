#ifndef GRAPHICSEDITTAB_H
#define GRAPHICSEDITTAB_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class GraphicsEditTab;
}

class GraphicsEditTab : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsEditTab(QWidget *parent = nullptr);
    ~GraphicsEditTab();

    void setBrushColor(QColor color);
    void setPenColor(QColor color);
    void setBrushColorOrin(QColor color);
    void setPenColorOrin(QColor color);

    QColor getPenColor() const;
    QColor getBrushColor() const;
    QColor getPenColorOrin() const;
    QColor getBrushColorOrin() const;

public slots:
void selectPenColor(bool val);
void selectBrushColor(bool val);
void resetPenColor(bool val);
void resetBrushColor(bool val);

private:
    Ui::GraphicsEditTab *ui;

    QPalette pen_pal;
    QPalette brush_pal;

    QColor m_brushColor;
    QColor m_penColor;

    QColor m_brushColor_orin;
    QColor m_penColor_orin;
};

#endif // GRAPHICSEDITTAB_H
