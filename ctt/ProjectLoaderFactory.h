#if !defined(_PROJECTLOADERFACTORY_H)
#define _PROJECTLOADERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace project {

class ProjectLoaderFactory {
public:
	typedef QScopedPointer<ProjectLoaderFactory> uptr;
	typedef QSharedPointer<ProjectLoaderFactory> sptr;
	typedef QWeakPointer<ProjectLoaderFactory> wptr;

};

}  // namespace project
}  // namespace model

#endif  //_PROJECTLOADERFACTORY_H
