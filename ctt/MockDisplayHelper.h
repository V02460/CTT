#ifndef _MOCKDISPLAYHELPER_H
#define _MOCKDISPLAYHELPER_H

#include <QImage>
#include <QLabel>

#include "ctt.h"

namespace helper {

class MockDisplayHelper {
public:
    static void setMainWindow(ctt *mainWindow);

    static void showImage(QImage image);

private:
    static QLabel *label;
};

}  // namespace helper

#endif