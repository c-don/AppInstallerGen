//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AppInstallerGenie;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;


MainPage::MainPage()
{
	InitializeComponent();
	ApplicationView::PreferredLaunchViewSize = Size(650, 412);
	ApplicationView::PreferredLaunchWindowingMode = ApplicationViewWindowingMode::PreferredLaunchViewSize;
	ApplicationView::GetForCurrentView()->SetPreferredMinSize(Size(650, 412));

	CoreApplication::GetCurrentView()->TitleBar->ExtendViewIntoTitleBar = true;
}

void AppInstallerGenie::MainPage::SelectAppPackage(Object^ sender, RoutedEventArgs^ e)
{
	auto filePicker = ref new FileOpenPicker;
	filePicker->ViewMode = PickerViewMode::List;
	filePicker->FileTypeFilter->Append(".appx");
	filePicker->FileTypeFilter->Append(".appxbundle");
	filePicker->FileTypeFilter->Append(".eappx");
	filePicker->FileTypeFilter->Append(".eappxbundle");

	create_task(filePicker->PickSingleFileAsync()).then(
		[this](StorageFile^ appPackage)
	{
		if (appPackage)
		{
			textBox->Text = "Picked app pacakge: " + appPackage->Name;
		}
		else
		{
			textBox->Text = "Operation cancelled.";
		}
	}
	);

}
