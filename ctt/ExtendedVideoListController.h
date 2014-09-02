#ifndef _EXTENDEDVIDEOLISTCONTROLLER
#define _EXTENDEDVIDEOLISTCONTROLLER

#include "VideoListController.h"

#include "FilteredVideo.h"
#include "Player.h"

namespace controller {

class ExtendedVideoListController : public controller::VideoListController {
public:
    typedef QScopedPointer<VideoListController> uptr;
    typedef QSharedPointer<VideoListController> sptr;
    typedef QWeakPointer<VideoListController> wptr;

    ExtendedVideoListController(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr baseVideos,
                                ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
                                ::model::saveable::SaveableList<::model::player::Player>::sptr playerList);

public slots:
  //  virtual void addVideo(QString path) Q_DECL_OVERRIDE;
    virtual void addVideo(QString path,
                          int width,
                          int height,
                          double fps,
                          ::model::video::YUVType type) Q_DECL_OVERRIDE;

    virtual void addVideo(QString path,
                          QString macrobockPath,
                          int width,
                          int height,
                          double fps,
                          ::model::video::YUVType type) Q_DECL_OVERRIDE;

    virtual void addVideo(::model::video::Video::sptr video) Q_DECL_OVERRIDE;

    virtual void removeVideo(int index) Q_DECL_OVERRIDE;
    virtual void removeVideo(const ::model::video::Video &video) Q_DECL_OVERRIDE;

private:
    ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
    ::model::saveable::SaveableList<::model::player::Player>::sptr playerList;
};

} // namespace controller

#endif //_EXTENDEDVIDEOLISTCONTROLLER