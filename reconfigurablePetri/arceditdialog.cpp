#include "arceditdialog.h"
#include "tabwidget.h"

ArcEditDialog::ArcEditDialog(QWidget * parent):QDialog(parent)
{
    setFixedSize (450, 450);
    setModal(false);
    setWindowTitle(tr("Arc Attributes"));
    QFont font;
    font.setFamily("Arial");
    this->setFont(font);
    /*Tab*/
    QTabWidget * l_tabWidget = new QTabWidget;
    QWidget * l_tab1 = new QWidget;
    GraphicsEditTab * l_tab2 = new GraphicsEditTab;
    m_graphicsEditTab = l_tab2;
    l_tabWidget->addTab(l_tab1, tr("General"));
    l_tabWidget->addTab(l_tab2, tr("Graphic"));

    QFormLayout * temp = new QFormLayout;
    temp->addRow(l_tabWidget);

    inputWeight = new QLineEdit;
    inputWeight->setFixedSize(150,25);
    inputWeight->setText("1.0");

    validateButton = new QPushButton("OK");
    //validateButton->setDefault(true);
    cancelButton = new QPushButton("Cancel");

     outputButton=new QPushButton(tr("Output to .m file"));
     outputButton->setFixedSize(150,25);

    vlayout = new QVBoxLayout;
    flayout = new QFormLayout;
    hlayout = new QHBoxLayout;

    //m_experssionHlayout->addWidget(m_experssionEdit);
    //m_experssionHlayout->addWidget(m_showExperssion);


    hlayout->addWidget(validateButton);
    hlayout->addWidget(cancelButton);
    hlayout->setStretch (0, 100);
    hlayout->setAlignment (cancelButton, Qt::AlignRight);
    hlayout->setAlignment (validateButton, Qt::AlignRight);

    //flayout->addRow("<span style=\"text-decoration:underline;\">E</span>xperssion : ", m_experssionHlayout);
    flayout->addRow("<span style=\"text-decoration:underline;\">W</span>eight : ", inputWeight);
    groupBox = new QGroupBox (this);
    groupBox->setFlat (false);
    //groupBox->setLayout (flayout);
    QLayout *layout = new QVBoxLayout;
    layout->addWidget(l_tabWidget);
    groupBox->setLayout(layout);

    l_tab1->setLayout(flayout);

    flayout->addWidget(outputButton);
    vlayout->addWidget(groupBox);
    vlayout->addLayout(hlayout);

    this->setLayout(vlayout);//old
    //l_tab1->setLayout(layout);


    //this->setLayout(layout);

//    connect(outputButton,SIGNAL(clicked()),this,SLOT(output()));
    connect(validateButton, &QPushButton::clicked, this, &ArcEditDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ArcEditDialog::reject);
}

/*
void ArcEditDialog::showDialog(int w)
{
 inputWeight->setValue(w);
 exec();
}

int ArcEditDialog::getValue() const
{
  return inputWeight->value();
}
*/
ArcEditDialog::~ArcEditDialog()
{
    delete groupBox;
    //delete inputExpression;
    delete validateButton;
    delete cancelButton;

    //delete fisButton;

}



