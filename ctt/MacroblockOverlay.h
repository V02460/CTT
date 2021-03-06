#ifndef _MACROBLOCKOVERLAY_H
#define _MACROBLOCKOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QColor>

#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"
#include "VertexAttribute.h"

namespace model {
namespace filter {
namespace overlay {

/**
 * Provides a new version of the predecessors frame with the graphical representation of macroblock types mixed into it.
 */
class MacroblockOverlay : public ColoringOverlay {
    Q_OBJECT

public:
    typedef QScopedPointer<MacroblockOverlay> uptr;
    typedef QSharedPointer<MacroblockOverlay> sptr;
    typedef QWeakPointer<MacroblockOverlay> wptr;

    static const QByteArray kFilterID;

    /**
     * Creates a new MacroblockOverlay object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit MacroblockOverlay(Module::sptr predecessor);

    /**
     * Destroys the MacroblockOverlay.
     */
    virtual ~MacroblockOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static ::model::saveable::Saveable::SaveableType getSaveableType() { return Saveable::macroblockOverlay; }
    virtual ::model::saveable::Saveable::SaveableType saveableType() const Q_DECL_OVERRIDE{return getSaveableType();}
    static Saveable::sptr getDummy();

	/**
	* Renders the macroblock view.
	*/
	class Macroblocks : public Filter, public QOpenGLFunctions {
	public:
		typedef QScopedPointer<Macroblocks> uptr;
		typedef QSharedPointer<Macroblocks> sptr;
		typedef QWeakPointer<Macroblocks> wptr;

		Macroblocks(::model::Module::sptr predecessor);
		~Macroblocks();
		virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
		static ::model::saveable::Saveable::SaveableType getSaveableType() { return Saveable::macroblockOverlay_macroblocks; }
		virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
		virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
		virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
		virtual SaveableType saveableType() const Q_DECL_OVERRIDE{ return getSaveableType(); }
		virtual QString getName() const Q_DECL_OVERRIDE{ return "filter_macroblockoverlay_macroblocks"; }
		virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; };
		static ::model::saveable::Saveable::sptr getDummy();

	private:
		Macroblocks();

		QColor getMacroblockColor(::model::frame::MacroblockType type) const;
		QRectF getPartitionTextureCoordinates(::model::frame::MacroblockType type) const;

		void buildBuffers(QVector<QVector<::model::frame::MacroblockType>> mbTypes) const;

		mutable ::helper::VertexAttribute::sptr positionAttribute;
		mutable ::helper::VertexAttribute::sptr colorAttribute;
		mutable ::helper::VertexAttribute::sptr texcrdAttribute;

		// buffer builder functionality
		void startBuilder() const;
		// position
		void append(QPointF position) const;
		void append(QRectF quad) const;
		// color
		void append(QColor color, unsigned int count = 1) const;
		// texture coordinates
		void appendTexcrd(QPointF texcrd) const;
		void appendQuadCoordinates(QRectF texcrd) const;
		void indexRestart() const;

		mutable bool doIndexRestartPosition;
		mutable bool doIndexRestartColor;
		mutable bool doIndexRestartTexcrd;
		mutable QPointF lastPosition;
		mutable QColor lastColor;
		mutable QPointF lastTexcrd;

		Surface::sptr partitionMap;
	};

private:
    static const float kBlockAlpha;

    /**
     * Creates a dummy MacroblockOverlay.
     */
    MacroblockOverlay();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROBLOCKOVERLAY_H
