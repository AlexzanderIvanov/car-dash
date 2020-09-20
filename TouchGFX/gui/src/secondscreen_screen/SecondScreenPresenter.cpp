#include <gui/secondscreen_screen/SecondScreenView.hpp>
#include <gui/secondscreen_screen/SecondScreenPresenter.hpp>

SecondScreenPresenter::SecondScreenPresenter(SecondScreenView& v)
    : view(v)
{

}

void SecondScreenPresenter::activate()
{
	model -> saveCurrentScreenIndex(2);
}

void SecondScreenPresenter::deactivate()
{

}

void SecondScreenPresenter::setNewValue(uint8_t* newValue)
{
	view.updateVal(newValue);
}

void SecondScreenPresenter::updateDisplaySettings(uint8_t* settings)
{
	view.updateSettings(settings);
}
