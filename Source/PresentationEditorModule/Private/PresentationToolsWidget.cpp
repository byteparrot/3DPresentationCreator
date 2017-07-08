#include "PresentationEditorModulePCH.h"
#include "PresentationEditorCommands.h"
#include "PresentationToolsWidget.h"

#define LOCTEXT_NAMESPACE "PresentationToolsWidget"

void PresentationToolsWidget::Construct(const FArguments& InArgs)
{
	UE_LOG(PresentationPluginLog, Log, TEXT("PresentationToolsWidget::Construct..."));

	index = 0;

	ChildSlot
		[
			SNew(SVerticalBox)	
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(TEXT("Project Settings:"))).Margin(5.0f)
			]
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			[
				SNew(SBorder).HAlign(HAlign_Fill).BorderBackgroundColor(FSlateColor(FLinearColor(1,1,1,0.5f))).BorderImage(FCoreStyle::Get().GetBrush("ExpandableArea.Border"))
				[
					SNew(SWrapBox).UseAllottedWidth(true)
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton).OnClicked_Lambda([]()->FReply { PresentationEditorCommands::NewSlide_Clicked(); return FReply::Handled(); }).Text(FText::FromString(TEXT("Add Slide"))).ContentPadding(3)
					]
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton).OnClicked_Lambda([]()->FReply { PresentationEditorCommands::ConfigurePresentation_Clicked(); return FReply::Handled(); }).Text(FText::FromString(TEXT("Configure Presentationmode"))).ContentPadding(3)
					]
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton).OnClicked_Lambda([]()->FReply { PresentationEditorCommands::NewCustomDesign_Clicked(); return FReply::Handled(); }).Text(FText::FromString(TEXT("New Custom Design"))).ContentPadding(3)
					]
				]
			]
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(TEXT("Presentation Settings:"))).Margin(5.0f)
			]
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			[
				SNew(SBorder).HAlign(HAlign_Fill).BorderBackgroundColor(FSlateColor(FLinearColor(1, 1, 1, 0.5f))).BorderImage(FCoreStyle::Get().GetBrush("ExpandableArea.Border"))
				[
					SNew(SWrapBox).UseAllottedWidth(true)
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.OnClicked(this, &PresentationToolsWidget::UpdateAllSlidesButtonClicked)
						.Text(FText::FromString(TEXT("Update All Slides")))
						.ContentPadding(3)
					]
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.OnClicked(this, &PresentationToolsWidget::FixSlideNumbersClicked)
						.Text(FText::FromString(TEXT("Fix Slide Numbers")))
						.ContentPadding(3)
					]
				]
			]
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			[
				SNew(STextBlock).Text(FText::FromString(TEXT("Navigation:"))).Margin(5.0f)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder).HAlign(HAlign_Fill).BorderBackgroundColor(FSlateColor(FLinearColor(1, 1, 1, 0.5f))).BorderImage(FCoreStyle::Get().GetBrush("ExpandableArea.Border"))
				[
					SNew(SWrapBox).UseAllottedWidth(true)
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.OnClicked(this, &PresentationToolsWidget::PrevSlideButtonClicked)
						.Text(FText::FromString(TEXT("Previous Slide")))
						.ContentPadding(3)
					]
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.OnClicked(this, &PresentationToolsWidget::GotoSlideButtonClicked)
						.Text(FText::FromString(TEXT("Go To Slide")))
						.ContentPadding(3)
					]
					+ SWrapBox::Slot().Padding(10.0f)
					[
						SNew(SButton)
						.OnClicked(this, &PresentationToolsWidget::NextSlideButtonClicked)
						.Text(FText::FromString(TEXT("Next Slide")))
						.ContentPadding(3)
					]
				]
			]
		];
}

FReply PresentationToolsWidget::UpdateAllSlidesButtonClicked()
{

	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world

	for (TObjectIterator<ASlide> Itr; Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != World)
		{
			continue;
		}
		Itr->RerunConstructionScripts();
	}

	PluginManager::printMessageBox(LOCTEXT("UpdateAllSlides", "All Slides Updated!"));

	return FReply::Handled();
}

FReply PresentationToolsWidget::PrevSlideButtonClicked()
{
	index = index > 0 ? index - 1 : 0;
	MoveToSlide(index);

	return FReply::Handled();
}

FReply PresentationToolsWidget::GotoSlideButtonClicked()
{
	MoveToSlide(index);

	return FReply::Handled();
}

void PresentationToolsWidget::MoveToSlide(int _index)
{
	UWorld* const World = GEditor->GetEditorWorldContext().World(); // get a reference to the world
	AActor* TargetSlide = nullptr;

	for (TActorIterator<ASlide> Itr(World); Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != World || Itr->SlideIndex != _index)
		{
			continue;
		}
		TargetSlide = *Itr;

	}

	if (TargetSlide) {
		auto arrow = TargetSlide->FindComponentByClass<class UArrowComponent>();
		if (arrow)
			GEditor->MoveViewportCamerasToComponent(arrow, true);
		else
			GEditor->MoveViewportCamerasToActor(*TargetSlide, true);
		GEditor->SelectNone(false, true);
		GEditor->SelectActor(TargetSlide, true, true, true);
	}
	else
		UE_LOG(PresentationPluginLog, Log, TEXT("Slide not found"));
}

FReply PresentationToolsWidget::NextSlideButtonClicked()
{
	int last = ASlide::GetLastSlideNumber();
	index = index < last ? index + 1 : last;

	MoveToSlide(index);

	return FReply::Handled();
}

FReply PresentationToolsWidget::FixSlideNumbersClicked()
{
	ASlide::FixSlideNumbers();

	PluginManager::printMessageBox(LOCTEXT("SlideNumbersFixed", "Fixing Slide Numbers Complete!"));

	return FReply::Handled();
}


#undef LOCTEXT_NAMESPACE