#ifndef _LISTEDPUSHBUTTON
#define _LISTEDPUSHBUTTON

#include <QToolButton>
#include "FilteredVideo.h"
#include "Observer.h"
#include "Frame.h"

namespace view {
	/**
	 *	The ListedPushButton is a small utitlity button wich can be put into a list of dynaically generated buttons
	 *	and whose signals can be later on identified by the id given to the button.
	 */
class ListedPushButton : public QToolButton , public model::Observer {
	Q_OBJECT
public:
	typedef QScopedPointer<ListedPushButton> uptr;
	typedef QSharedPointer<ListedPushButton> sptr;
	typedef QWeakPointer<ListedPushButton> wptr;
	/**
	 *	Creates a new ListedPushButton with an id for later identification, a video for thethumbnail generation and a
	 *	parent wigdet.
	 *
	 *	@param id The id which allows later identification of this button.
	 *	@param video The video from wich the thumbnail is taken.
	 *	@param parent The parent widget.
	 */
	ListedPushButton(int id, model::filter::FilteredVideo::sptr video, QWidget *parent = 0);
	/**
	 *	Creates a new ListedPushButton with an id for later identification and a parent wigdet.
	 *
	 *	@param id The id which allows later identification of this button.
	 *	@param parent The parent widget.
	 */
	ListedPushButton(int id, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;

	virtual void resizeEvent(QResizeEvent *ev) Q_DECL_OVERRIDE;
signals:
	void toggled(bool checked, int id);
	void clicked(bool checked, int id);
	void removed(bool checked, int id);
private slots:
	/**
	*	Wraps the default toggled signal of QPushButton to the custom toggled signal of this class.
	*
	*	@param checked If the button is checkable this determines whether the button was checked or unchecked
	*/
	void buttonToggled(bool checked);
	/**
	*	Wraps the default clicked signal of QPushButton to the custom clicked signal of this class.
	*
	*	@param checked If the button is checkable this determines whether the button was checked or unchecked
	*/
	void buttonClicked(bool checked);

	void removeToggled(bool checked);
private:
	void init(int id);
	void setThumbnail();

	int id; /**< The id which represents the buttons index in the list */
	double iconRatio; /**< Holds the icon's aspect ratio */
	model::filter::FilteredVideo::sptr video; /**< The video from which this button generates its thumbnail */
	model::frame::Frame::sptr testFrame;
};

} // namespace view
#endif //_LISTEDPUSHBUTTON