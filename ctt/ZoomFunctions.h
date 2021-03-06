#ifndef _ZOOMFUNCTIONS_H
#define _ZOOMFUNCTIONS_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QPushButton>
#include <QSlider>

namespace view {

/**
 * The ZoomFunctions manage the zooming into or out of the timeline by providing the needed interactable components.
 */
class ZoomFunctions : public QWidget {
    Q_OBJECT
public:
    typedef QScopedPointer<ZoomFunctions> uptr;
    typedef QSharedPointer<ZoomFunctions> sptr;
    typedef QWeakPointer<ZoomFunctions> wptr;

    /**
     * Sets the internal zoomFactor when for example the user clicked on the zoom-out-button.
     * After changing the zoomFactor the zoomFactorChanged signal is emitted.
     *
     * @param zoomFactor The new zoom factor for the timeline.
     */
    void setZoomFactor(double zoomFactor);

    /**
     * Returns the current zoom factor.
     *
     * @return the current zoom factor.
     */
    double getZoomFactor() const;

signals:
    /**
     * This signal is emitted as soon as the internal zommFactor has changed its value.
     */
    void zoomFactorChanged(double zoomFactor);

private:
    QPushButton btnZoomOut; /**< The button to zoom out of the timline */
    QPushButton btnZoomIn; /**< The button to zoom in to the timeline */
    QSlider sliderZoom; /**< The slider for zooming smoothly in the timeline */
    double zoomFactor; /**< The internally saved zoom factor */
};

}  // namespace view

#endif  //_ZOOMFUNCTIONS_H
