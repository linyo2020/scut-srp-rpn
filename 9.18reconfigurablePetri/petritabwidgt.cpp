#include "petritabwidgt.h"

PetriTabwidgt::PetriTabwidgt(const QString &id, QWidget * parent)
    : QWidget(parent)
{
    this->id = id;
    name = id;
//    createTab ();
}
void PetriTabwidgt::createTab ()
{

}

PetriTabwidgt::~PetriTabwidgt ()
{

}
