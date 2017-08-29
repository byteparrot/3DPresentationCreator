#pragma once

#include "Slide.h"
#include "PluginManager.h"
#include "UnrealEd.h"
#include "Runtime/Slate/Public/Framework/Notifications/NotificationManager.h"
#include "Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h"
#include "SDockTab.h"

/**
* The PresentationToolsWidget represents the content of the presentation tools tab
* with all the buttons and their layouts
*/
class PresentationToolsWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(PresentationToolsWidget) {}
	SLATE_END_ARGS()

	/**
	* Construct creates the widget when the tab opens
	*/
	void Construct(const FArguments& InArgs);

	/**
	* UpdateAllSlidesButtonClicked iterates through all the slides in the world
	* and updates their proportions and their content to the data
	*/
	FReply UpdateAllSlidesButtonClicked();

	/**
	* PrevSlideButtonClicked decrements the current navigation-slide-index and
	* calls MoveToSlide to move the camera to the slide
	*/
	FReply PrevSlideButtonClicked();

	/**
	* GotoSlideButtonClicked calls MoveToSlide to move the camera to the current slide
	*/
	FReply GotoSlideButtonClicked();

	/**
	* MoveToSlide moves the camera to the slide with the specified index
	* @param _index index of the slide where the camera should move to
	*/
	void MoveToSlide(int _index);

	/**
	* NextSlideButtonClicked increments the current navigation-slide-index and
	* calls MoveToSlide to move the camera to the slide
	*/
	FReply NextSlideButtonClicked();

	/**
	* FixSlideNumbersClicked iterates through all the slides and checks for wrongly numbered slides
	* like indexes that are left out and changes the indexes to fill the holes
	*/
	FReply FixSlideNumbersClicked();

private:
	int index;	// stores the current slide index - used for navigating inside the editor
};
