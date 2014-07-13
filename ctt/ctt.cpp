#include "ctt.h"

#include "MockDisplayHelper.h"

using helper::MockDisplayHelper;

ctt::ctt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    MockDisplayHelper::setMainWindow(this);
}

ctt::~ctt()
{

}
