#ifndef _XMLLOADER_H
#define _XMLLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QXmlStreamReader>

#include "ProjectLoader.h"
#include "IOException.h"

namespace controller {
namespace project {

/**
 * Loads a project saved as XML file by the XMLSaver.
 */
class XMLLoader : public ProjectLoader {

public:
    typedef QScopedPointer<XMLLoader> uptr;
    typedef QSharedPointer<XMLLoader> sptr;
    typedef QWeakPointer<XMLLoader> wptr;

};

}  // namespace project
}  // namespace controller

#endif  //_XMLLOADER_H
