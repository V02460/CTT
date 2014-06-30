#if !defined(_FILTERPARAM_H)
#define _FILTERPARAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
	namespace filter {
		/**
		 * Represents a parameter influencing the behaviour of a Filter.
		 */
		class FilterParam {
		public:
			typedef QScopedPointer<FilterParam> uptr;
			typedef QSharedPointer<FilterParam> sptr;
			typedef QWeakPointer<FilterParam> wptr;

			any getValue();
			/**
			 * Creates a new FilterParam
			 */
			FilterParam(QString name, );
		private:
			QString name;
		};

	}  // namespace filter
}  // namespace model

#endif  //_FILTERPARAM_H
