#include "placeeditdialog.h"

PlaceEditDialog::PlaceEditDialog (QWidget * parent):
    QDialog (parent)
{
    setFixedSize (450, 450);
    setModal(true);
    setWindowTitle(tr("Place Attributes"));
    QFont font;
    font.setFamily("Arial");
    this->setFont(font);
    m_placeID=new QLabel;

    QTabWidget * l_tabWidget= new QTabWidget;
    QWidget * l_tab1=new QWidget;

    //QWidget * l_tab2=new QWidget;
    GraphicsEditTab * l_tab2 = new GraphicsEditTab;
    m_graphicsEditTab = l_tab2;

    QWidget * l_tab3=new QWidget;

    l_tabWidget->addTab(l_tab1,tr("General"));
    l_tabWidget->addTab(l_tab2,tr("Graphic"));
    l_tabWidget->addTab(l_tab3,tr("Port"));

    //布局设置
    m_plainTextEdit=new QTextEdit;
    m_commentLabel=new QLabel("Comment  : ");
    m_showComment=new QCheckBox("show");
    m_inputPort=new QCheckBox("Input port");
    m_outputPort=new QCheckBox("Output port");
    //设置互斥勾选框
    m_inputPort->setAutoExclusive(true);
    m_outputPort->setAutoExclusive(true);

    inputLabel = new QLineEdit(tr("labeltext"), 0);
    inputLabel->setFixedSize(150, 25);

    inputTokens = new QLineEdit(tr("input"), 0);
    inputTokens->setFixedSize(150, 25);

    validateButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    vlayout  = new QVBoxLayout;
    vlayout2 = new QVBoxLayout;
    hlayout  = new QHBoxLayout;
    hlayout2 = new QHBoxLayout;
    flayout  = new QFormLayout;
    m_commentHlayout=new QHBoxLayout;


    flayout->addRow(tr("<span style=\"text-decoration:\
                       underline;\">I</span>D  : "),m_placeID);
    flayout->addRow(tr("<span style=\"text-decoration:\
           underline;\">N</span>ame  : "), inputLabel);
    flayout->addRow(tr("<span style=\"text-decoration:\
           underline;\">M</span>arking : "), inputTokens);
    m_commentHlayout->addWidget(m_commentLabel);
    m_commentHlayout->addWidget(m_showComment);
    //m_plainTextEdit->setText("123");
    flayout->addRow(m_commentHlayout);
    flayout->addRow(m_plainTextEdit);
    l_tab1->setLayout(flayout);

    //端口界面布局
    m_portlayout = new QVBoxLayout;
    m_portlayout->addWidget(m_inputPort);
    m_portlayout->addWidget(m_outputPort);
    l_tab3->setLayout(m_portlayout);


    QFormLayout * temp=new QFormLayout;
    temp->addRow(l_tabWidget);
    vlayout->addLayout(temp);

    groupBox = new QGroupBox (this);
    groupBox->setFlat (false);
    groupBox->setLayout (vlayout);

    hlayout2->addWidget(validateButton);
    hlayout2->addWidget(cancelButton);
    hlayout2->setStretch (0, 100);
    hlayout2->setAlignment (cancelButton, Qt::AlignRight);
    hlayout2->setAlignment (validateButton, Qt::AlignRight);

    vlayout2->addWidget(groupBox);
    vlayout2->addLayout(hlayout2);

    setLayout(vlayout2);

    connect (validateButton, &QPushButton::clicked, this, &PlaceEditDialog::accept);
    connect (cancelButton, &QPushButton::clicked, this,  &PlaceEditDialog::reject);
}

/*
void PlaceEditDialog::show (const QString& nm, int t, int c)
{
    inputLabel->setText (nm);
    inputTokens->setValue (t);

    if(c == omega)
       inputCapacity->setValue (0);
    else
       inputCapacity->setValue (c);

    exec ();
}

QString PlaceEditDialog::getName () const
{
  return inputLabel->text();
}

int PlaceEditDialog::getTokens() const
{
  return inputTokens->value ();
}

int PlaceEditDialog::getCapacity() const
{
  return inputCapacity->value();
}

bool PlaceEditDialog::showAttributes()
{
  return chckBox->isChecked ();
}
*/

PlaceEditDialog::~PlaceEditDialog()
{

    //delete label;
    delete inputLabel;
    delete inputTokens;
    //delete inputCapacity;
    //delete chckBox;

    delete validateButton;
    delete cancelButton;
    delete groupBox;
    //delete m_groupBox_1;
    //delete m_flayout_1;
    //delete m_radiusSpinBox;
    //delete m_radiusSpinBox;
}

