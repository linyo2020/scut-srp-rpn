#include "transitioneditdialog.h"

TransitionEditDialog::TransitionEditDialog(QWidget *parent) :
    QDialog(parent)
{
    QFont font;
    font.setFamily("Arial");
    this->setFont(font);
    setFixedSize (450, 450);
    setModal(true);
    setWindowTitle("Transition Attributes");

    inputLabel = new QLineEdit(this);
    //inputLabel->setFont(font);
    inputLabel->setMaximumSize(200, 30);
    inputLabel1 = new QLineEdit(this);
    inputLabel1->setMaximumSize(200, 30);
    //inputLabel1->setFont(font);
    //inputLabel2 = new QLineEdit(this);
    //inputLabel2->setMaximumSize(200, 30);

    m_tabWidget = new QTabWidget;
    m_tab1 = new QWidget;
    //m_tab2 = new QWidget;
    m_tab3 = new  GraphicsEditTab;
    m_graphicsEditTab = m_tab3;
    m_transitionID = new QLabel;
    m_plainTextEdit = new QTextEdit;
    m_showComment = new QCheckBox(tr("show"));
    m_commentLabel = new QLabel(tr("Comment"));
    m_commentHlayout = new QHBoxLayout;
    //m_checkFunction = new QPushButton(tr("Check Function"));
    //m_functionAssistant = new QPushButton(tr("Function assistant"));
    //m_functionOverview = new QPushButton(tr("Function overview"));

    m_tabWidget->addTab(m_tab1,tr("General"));
    //m_tabWidget->addTab(m_tab2,tr("Function"));
    m_tabWidget->addTab(m_tab3,tr("Graphic"));


     slider = new QSlider(Qt::Horizontal);
     slider->setFixedWidth(200);
     slider->setRange(-90, 90);
     slider->setSliderPosition (0);
     slider->setTickPosition(QSlider::TicksBelow);
     slider->setTickInterval(45);

    validateButton = new QPushButton("OK");
    //validateButton->setDefault(true);
    cancelButton = new QPushButton("Cancel");

    vlayout = new QVBoxLayout;
    flayout = new QFormLayout;
    hlayout = new QHBoxLayout;


    hlayout->addWidget(validateButton);
    hlayout->addWidget(cancelButton);
    hlayout->setStretch (0, 100);
    hlayout->setAlignment (cancelButton, Qt::AlignRight);
    hlayout->setAlignment (validateButton, Qt::AlignRight);

    flayout->addRow("<span style=\"text-decoration:"\
                     "underline;\">I</span>D : ",m_transitionID);
    flayout->addRow("<span style=\"text-decoration:"\
        "underline;\">N</span>ame : ", inputLabel);
    flayout->addRow("<span style=\"text-decoration:"\
        "underline;\">F</span>unction : ", inputLabel1);
    //flayout->addRow("<span style=\"text-decoration:"\
      //  "underline;\">M</span>assAction : ", inputLabel2);
    flayout->addRow("<span style=\"text-decoration:"\
        "underline;\">R</span>otation : ", slider);
    m_commentHlayout->addWidget(m_commentLabel);
    m_commentHlayout->addWidget(m_showComment);
    flayout->addRow(m_commentHlayout);
    flayout->addRow(m_plainTextEdit);

    m_tab1->setLayout(flayout);

    //m_functionEdit=new QPlainTextEdit;

    //m_tab2Flayout=new QFormLayout;
    //m_tab2Flayout->addRow(m_functionEdit);
    //m_tab2Flayout->addRow(m_checkFunction);
    //m_tab2Flayout->addRow(m_functionAssistant);
    //m_tab2Flayout->addRow(m_functionOverview);
    //m_tab2->setLayout(m_tab2Flayout);


    QFormLayout * temp=new QFormLayout;
    temp->addRow(m_tabWidget);
    groupBox = new QGroupBox;
    groupBox->setLayout(temp);


    vlayout->addWidget(groupBox);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect (validateButton, &QPushButton::clicked , this, &TransitionEditDialog::accept);
    connect (cancelButton, &QPushButton::clicked, this, &TransitionEditDialog::reject);
    connect (slider, &QSlider::valueChanged, this, &TransitionEditDialog::showRotDegree);
}

void TransitionEditDialog::showRotDegree(int d)
{
   QVariant v(d);
   QToolTip::showText ( slider->mapToGlobal(QPoint(90 + d - 35, 0)),
                       QString(v.toString()+" "), slider);
}

TransitionEditDialog::~TransitionEditDialog()
{
    delete inputLabel;
    delete inputLabel1;
    //delete inputLabel2;
    delete slider;
    delete validateButton;
    delete cancelButton;
    delete hlayout;
    delete flayout;
    delete groupBox;
    delete vlayout;


    /*delete m_tab1;
    delete m_tab2;
    delete m_tab3;
    delete m_tabWidget;
    delete m_transitionID;
    delete m_plainTextEdit;
    delete m_showComment;
    delete m_commentLabel;
    delete m_commentHlayout;
    delete m_checkFunction;
    delete m_functionAssistant;
    delete m_functionOverview;*/
}
