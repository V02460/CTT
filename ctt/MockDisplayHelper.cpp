#include "MockDisplayHelper.h"

namespace helper {

void MockDisplayHelper::setMainWindow(ctt *mainWindow) {
    label = mainWindow->getLabel();
}

void MockDisplayHelper::showImage(QImage image) {
    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}

QLabel *MockDisplayHelper::label = nullptr;

}  // namespace helper