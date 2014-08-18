#ifndef _VIDEOPROCESSINGWIDGET_H
#define _VIDEOPROCESSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>

#include "Video.h"
#include "VideoFileType.h"
#include "VideoWidget.h"
#include "VideoListController.h"

namespace view {

/**
 * The VideoProcessingWidget provides the interactable components for saving a video and for using it later in the
 * analysing view as well as it holds the means to display a video.
 */
class VideoProcessingWidget : public QWidget {
    Q_OBJECT
public:
    typedef QScopedPointer<VideoProcessingWidget> uptr;
    typedef QSharedPointer<VideoProcessingWidget> sptr;
    typedef QWeakPointer<VideoProcessingWidget> wptr;

	VideoProcessingWidget(::model::player::VideoScrubber::sptr scrubber,
		::controller::VideoListController::sptr controller, bool showSaveButton = false, QWidget *parent = 0);

	void subscribe(::controller::VideoListController::sptr observer);

	void unsubscribe(const ::controller::VideoListController &observer);
	
public slots:
    /**
     * This method is called when the user changes the state of the checkbox.
     * It decides according to the current state of the checkbox if it has to emitt the videoForAnalysingAdded signal or
     * the videoForAnalysingRemoved signal.
     *
     * @param state The current state of the checkbox.
     */
    void checkboxUseForAnalysisValueChanged(int state);
    /**
     * This method is called when the user clicks the save button.
     * It opens a file chooser dialog where the user can specify the save directory, the save name and the file type of
     * the video which should be saved
     */
    void btnSaveVideoClicked();

signals:
    /**
     * This signal is emitted when the checkbox is checked.
     */
    void videoForAnalysingAdded(::model::video::Video::sptr video);

    /**
     * This signal is emitted when the checkbox is unchecked.
     */
    void videoForAnalysingRemoved(const ::model::video::Video &video);
private:
	void setupUi();

    bool showSaveButton; /**< Indicates whether the saveButton is shown or not */

    /**
     * The checkbox where the user can decide to use the video for analysing or not.
     */
    QCheckBox *checkboxUseForAnalysis;
    
    QPushButton *btnSaveVideo; /** The button which starts the video saving process */
    VideoWidget *videoWidget; /** The video widget which actually displays the video */
};

}  // namespace view

#endif  //_VIDEOPROCESSINGWIDGET_H
