#include "graphicsedittab.h"
#include "ui_graphicsedittab.h"

GraphicsEditTab::GraphicsEditTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsEditTab)
{
    ui->setupUi(this);
    connect(ui->m_PenColor_b, &QPushButton::clicked,
        this, &GraphicsEditTab::selectPenColor);
    connect(ui->m_BrushColor_b, &QPushButton::clicked,
        this, &GraphicsEditTab::selectBrushColor);

    connect(ui->m_PenColorReset_b,&QPushButton::clicked,
        this,&GraphicsEditTab::resetPenColor);
    connect(ui->m_BrushColorReset_b, &QPushButton::clicked,
        this, &GraphicsEditTab::resetBrushColor);
}

GraphicsEditTab::~GraphicsEditTab()
{
    delete ui;
}

void GraphicsEditTab::setBrushColor(QColor color)
{
    m_brushColor = color;
    brush_pal= ui->m_BrushColor_b->palette();
    brush_pal.setColor(QPalette::Button, m_brushColor);
    ui->m_BrushColor_b->setPalette(brush_pal);
    ui->m_BrushColor_b->setAutoFillBackground(true);
    ui->m_BrushColor_b->setFlat(true);
    ui->m_BrushColor_b->update();
}

void GraphicsEditTab::setPenColor(QColor color)
{
    m_penColor = color;
    pen_pal = ui->m_PenColor_b->palette();
    pen_pal.setColor(QPalette::Button, m_penColor);
    ui->m_PenColor_b->setPalette(pen_pal);
    ui->m_PenColor_b->setAutoFillBackground(true);
    ui->m_PenColor_b->setFlat(true);
    ui->m_PenColor_b->update();
}

void GraphicsEditTab::setBrushColorOrin(QColor color)
{
    m_brushColor_orin = color;
}

void GraphicsEditTab::setPenColorOrin(QColor color)
{
    m_penColor_orin = color;
}

QColor GraphicsEditTab::getPenColor() const
{
    return m_penColor;
}

QColor GraphicsEditTab::getBrushColor() const
{
    return m_brushColor;
}

QColor GraphicsEditTab::getPenColorOrin() const
{
    return m_penColor_orin;
}

QColor GraphicsEditTab::getBrushColorOrin() const
{
    return m_brushColor_orin;
}

void GraphicsEditTab::selectBrushColor(bool val)
{
    Q_UNUSED(val);
    auto cDialog = new QColorDialog;
    cDialog->exec();
    if(cDialog->selectedColor()!=QColor::Invalid)
    {
        setBrushColor(cDialog->selectedColor());
        m_brushColor_orin=cDialog->selectedColor();
    }
    //else setBrushColor(m_brushColor_orin);
    delete cDialog;
}

void GraphicsEditTab::resetPenColor(bool val)
{
    setPenColor(Qt::black);
}

void GraphicsEditTab::resetBrushColor(bool val)
{
    setBrushColor(Qt::white);
}

void GraphicsEditTab::selectPenColor(bool val)
{
    Q_UNUSED(val);
    auto cDialog = new QColorDialog;
    cDialog->exec();
    if(cDialog->selectedColor()!=QColor::Invalid)
    {
        setPenColor(cDialog->selectedColor());
        m_penColor_orin=cDialog->selectedColor();
    }
    //else setPenColor(m_penColor_orin);
    delete cDialog;
}
