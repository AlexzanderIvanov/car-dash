#include <gui/secondscreen_screen/SecondScreenView.hpp>
#include <message_types.h>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <set>
#include <vector>



static int current_slider_index = 1;

SecondScreenView::SecondScreenView() {

}


void SecondScreenView::setupScreen() {
	SecondScreenViewBase::setupScreen();
}

void SecondScreenView::tearDownScreen() {
	SecondScreenViewBase::tearDownScreen();
}

void SecondScreenView::updateSettings(uint8_t *settings) {
}

static bool isKthBitSet(int n, int k) {
	if (n & (1 << (k - 1))) {
		return true;
	} else {
		return false;
	}
}



void SecondScreenView::updateVal(uint8_t *newValue) {
	Unicode::snprintf(FrIndexValueBuffer, FRINDEXVALUE_SIZE, "%d", presenter->getTpmsIdFr());
	FrIndexValue.invalidate();

	Unicode::snprintf(RrIndexValueBuffer, RRINDEXVALUE_SIZE, "%d", presenter->getTpmsIdRr());
	RrIndexValue.invalidate();

	Unicode::snprintf(RlIndexValueBuffer, RLINDEXVALUE_SIZE, "%d", presenter->getTpmsIdRl());
	RlIndexValue.invalidate();

	Unicode::snprintf(FlIndexValueBuffer, FLINDEXVALUE_SIZE, "%d", presenter->getTpmsIdFl());
	FlIndexValue.invalidate();

	display_values *values = (display_values*) newValue;

	Unicode::snprintf(SliderIndexvalueBuffer, SLIDERINDEXVALUE_SIZE, "%d", current_slider_index);
	SliderIndexvalue.invalidate();


}



void SecondScreenView::moveToMainScreen() {
	presenter->setManualErrorChangeScreen();
}

void SecondScreenView::tpmsIndexChanges(int value) {
	current_slider_index = value;
}

void SecondScreenView::frSetIndex() {
	presenter->setTpmsIdFr(current_slider_index);
	Unicode::snprintf(FrIndexValueBuffer, FRINDEXVALUE_SIZE, "%d", current_slider_index);
	FrIndexValue.invalidate();
}

void SecondScreenView::rrSetIndex() {
	presenter->setTpmsIdRr(current_slider_index);
	Unicode::snprintf(RrIndexValueBuffer, RRINDEXVALUE_SIZE, "%d", current_slider_index);
	RrIndexValue.invalidate();
}

void SecondScreenView::rlSetIndex() {
	presenter->setTpmsIdRl(current_slider_index);
	Unicode::snprintf(RlIndexValueBuffer, RLINDEXVALUE_SIZE, "%d", current_slider_index);
	RlIndexValue.invalidate();
}

void SecondScreenView::flSetIndex() {
	presenter->setTpmsIdFl(current_slider_index);
	Unicode::snprintf(FlIndexValueBuffer, FLINDEXVALUE_SIZE, "%d", current_slider_index);
	FlIndexValue.invalidate();
}


