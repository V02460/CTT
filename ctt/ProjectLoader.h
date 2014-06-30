#if !defined(_PROJECTLOADER_H)
#define _PROJECTLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace project {

class ProjectLoader {
public:
	typedef QScopedPointer<ProjectLoader> uptr;
	typedef QSharedPointer<ProjectLoader> sptr;
	typedef QWeakPointer<ProjectLoader> wptr;

	void restore(QDir path);
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTLOADER_H
