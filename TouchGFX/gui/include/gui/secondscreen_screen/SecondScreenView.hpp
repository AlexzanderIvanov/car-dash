#ifndef SECONDSCREENVIEW_HPP
#define SECONDSCREENVIEW_HPP

#include <gui_generated/secondscreen_screen/SecondScreenViewBase.hpp>
#include <gui/secondscreen_screen/SecondScreenPresenter.hpp>

class SecondScreenView: public SecondScreenViewBase {
public:
	SecondScreenView();
	virtual ~SecondScreenView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void moveToMainScreen();
    virtual void tpmsIndexChanges(int value);

    virtual void frSetIndex();
    virtual void rrSetIndex();
    virtual void rlSetIndex();
    virtual void flSetIndex();

	void updateVal(uint8_t *newValue);
	void updateSettings(uint8_t *settings);

protected:
};

#endif // SECONDSCREENVIEW_HPP
