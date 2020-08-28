#ifndef SECONDSCREENVIEW_HPP
#define SECONDSCREENVIEW_HPP

#include <gui_generated/secondscreen_screen/SecondScreenViewBase.hpp>
#include <gui/secondscreen_screen/SecondScreenPresenter.hpp>

class SecondScreenView : public SecondScreenViewBase
{
public:
    SecondScreenView();
    virtual ~SecondScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SECONDSCREENVIEW_HPP
