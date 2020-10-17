#include <gui/secondscreen_screen/SecondScreenView.hpp>
#include <message_types.h>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <set>
#include <vector>

static float prev_ign_ang = 10;
static float prev_ve;
static float prev_boost_dc;
static int prev_boost_trgt;
static float prev_injector_dc;

static bool prev_error = true;

static int color_index = 0;
static int error_screen_blinks = 0;
static TEXTS *error;
static unsigned cutrrentErrorIndex = 0;
static int check_eng_code = 0;
static int eng_prot_code = 0;

SecondScreenView::SecondScreenView() {

}

static colortype getBlackColor() {
	colortype black_color = touchgfx::Color::getColorFrom24BitRGB(0, 0, 0);
	return black_color;
}

static colortype getRedColor() {
	colortype red_color = touchgfx::Color::getColorFrom24BitRGB(255, 0, 0);
	return red_color;
}

static colortype getColorForErrors() {

	color_index++;
	if (color_index >= 3) {
		color_index = 0;
		error_screen_blinks++;
		if (error_screen_blinks > 1000000) {
			error_screen_blinks = 0;
		}
	}

	colortype red_color = touchgfx::Color::getColorFrom24BitRGB(255, 0, 0);
	colortype black_color = touchgfx::Color::getColorFrom24BitRGB(0, 0, 0);
	colortype white_color = touchgfx::Color::getColorFrom24BitRGB(255, 255,
			255);

	colortype color_to_set;

	if (color_index == 0) {
		color_to_set = red_color;
	}
	if (color_index == 1) {
		color_to_set = black_color;
	}
	if (color_index == 2) {
		color_to_set = white_color;
	}

	return color_to_set;
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

static TEXTS getErrorText(int index) {
	TEXTS a;
	switch (index) {
	case 1:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 2:
		a = T_IAT_SENSOR_FAILURE;
		break;
	case 3:
		a = T_MAP_SENSOR_FAILURE;
		break;
	case 4:
		a = T_O2_SENSOR_FAILED;
		break;
	case 5:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 6:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 7:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 8:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 9:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	case 10:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	default:
		a = T_COOLANT_SENSOR_FAILURE;
		break;
	}
	return a;
}

void SecondScreenView::updateVal(uint8_t *newValue) {

	display_values *values = (display_values*) newValue;

	if (values->ing_ang != prev_ign_ang) {
		prev_ign_ang = values->ing_ang;
		Unicode::snprintfFloat(IngAngValueBuffer, INGANGVALUE_SIZE, "%.1f",
				values->ing_ang);
		IngAngValue.invalidate();
	}

	if (values->ve != prev_ve) {
		prev_ve = values->ve;
		Unicode::snprintfFloat(VeValueBuffer, VEVALUE_SIZE, "%.1f", values->ve);
		VeValue.invalidate();
	}

	if (values->boost_dc != prev_boost_dc) {
		prev_boost_dc = values->boost_dc;
		Unicode::snprintfFloat(BoostDcValueBuffer, BOOSTDCVALUE_SIZE, "%.1f",
				values->boost_dc);
		BoostDcValue.invalidate();
	}

	if (values->boost_trgt != prev_boost_trgt) {
		prev_boost_trgt = values->boost_trgt;
		Unicode::snprintf(BoostTrgtValueBuffer, BOOSTTRGTVALUE_SIZE, "%d",
				values->boost_trgt);
		BoostTrgtValue.invalidate();
	}

	if (values->injector_dc != prev_injector_dc) {
		prev_injector_dc = values->injector_dc;
		Unicode::snprintfFloat(InjctorDcValueBuffer, INJCTORDCVALUE_SIZE,
				"%.1f", values->injector_dc);
		InjctorDcValue.invalidate();
	}
	bool has_error = ((int) values->emu_errors) > 0;
	bool has_protection_error = ((int) values->emu_protection) > 0;
	bool has_check_eng_code = ((int) values->check_eng_code) > 0;
	bool has_eng_prot_code = ((int) values->eng_protection_code) > 0;
	if (has_check_eng_code) {
		if (error_screen_blinks < 100) {
			backgroundBox.setColor(getColorForErrors());
		} else {
			backgroundBox.setColor(getRedColor());
		}
		backgroundBox.invalidate();
		CheckEngCodeValue.setVisible(true);
		Unicode::snprintf(CheckEngCodeValueBuffer, CHECKENGCODEVALUE_SIZE, "%d",
				values->check_eng_code);
		CheckEngCodeValue.invalidate();
		check_eng_code = values->check_eng_code;
		prev_error = true;
	}
	if (has_eng_prot_code) {
		if (error_screen_blinks < 100) {
			backgroundBox.setColor(getColorForErrors());
		} else {
			backgroundBox.setColor(getRedColor());
		}
		backgroundBox.invalidate();
		EngProtCodeValue.setVisible(true);
		Unicode::snprintf(EngProtCodeValueBuffer, ENGPROTCODEVALUE_SIZE, "%d",
				values->eng_protection_code);
		EngProtCodeValue.invalidate();
		eng_prot_code = values->eng_protection_code;
		prev_error = true;
	}
	if (has_error) {
		if (error_screen_blinks < 100) {
			backgroundBox.setColor(getColorForErrors());
		} else {
			backgroundBox.setColor(getRedColor());
		}
		backgroundBox.invalidate();

		if (isKthBitSet((int) values->emu_errors, (int) 1)) {
			ErrorMessage.setTypedText(TypedText(T_COOLANT_SENSOR_FAILURE));
			*error = T_COOLANT_SENSOR_FAILURE;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 2)) {
			ErrorMessage.setTypedText(TypedText(T_IAT_SENSOR_FAILURE));
			*error = T_IAT_SENSOR_FAILURE;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 3)) {
			ErrorMessage.setTypedText(TypedText(T_MAP_SENSOR_FAILURE));
			*error = T_MAP_SENSOR_FAILURE;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 4)) {
			ErrorMessage.setTypedText(TypedText(T_O2_SENSOR_FAILED));
			*error = T_O2_SENSOR_FAILED;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 5)) {
			ErrorMessage.setTypedText(TypedText(T_EGT1_SESNSOR_FAILED));
			*error = T_EGT1_SESNSOR_FAILED;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 6)) {
			ErrorMessage.setTypedText(TypedText(T_EGT2_SENSOR_FAILED));
			*error = T_EGT2_SENSOR_FAILED;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 7)) {
			ErrorMessage.setTypedText(TypedText(T_EGT_HIGH));
			*error = T_EGT_HIGH;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 8)) {
			ErrorMessage.setTypedText(TypedText(T_KNOCKING));
			*error = T_KNOCKING;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 10)) {
			ErrorMessage.setTypedText(TypedText(T_DBW_SENSOR_FAILED));
			*error = T_DBW_SENSOR_FAILED;
		}
		if (isKthBitSet((int) values->emu_errors, (int) 11)) {
			ErrorMessage.setTypedText(TypedText(T_FPR_RELATIVE_ERROR));
			*error = T_FPR_RELATIVE_ERROR;
		}

		int x = 240 - ErrorMessage.getTextWidth() / 2;
		ErrorMessage.setXY(x, 205);
		ErrorMessage.resizeToCurrentText();
		ErrorMessage.invalidate();
		nextErrorButton.setVisible(true);
		clearErrorsBtn.setVisible(true);
		prev_error = true;
	} else if (has_protection_error) {
		if (error_screen_blinks < 100) {
			backgroundBox.setColor(getColorForErrors());
		} else {
			backgroundBox.setColor(getRedColor());
		}
		backgroundBox.invalidate();

		if (isKthBitSet((int) values->emu_protection, (int) 1)) {
			ErrorMessage.setTypedText(TypedText(T_OIL_TEMPERATURE_PROTECTION));
			*error = T_OIL_TEMPERATURE_PROTECTION;
		}
		if (isKthBitSet((int) values->emu_protection, (int) 2)) {
			ErrorMessage.setTypedText(TypedText(T_CLT_PROTECTION));
			*error = T_CLT_PROTECTION;
		}
		if (isKthBitSet((int) values->emu_protection, (int) 3)) {
			ErrorMessage.setTypedText(TypedText(T_OIL_PRESSSURE_PROTECTION));
			*error = T_OIL_PRESSSURE_PROTECTION;
		}
		if (isKthBitSet((int) values->emu_protection, (int) 4)) {
			ErrorMessage.setTypedText(TypedText(T_FUEL_PRESSURE_PROTECTION));
			*error = T_FUEL_PRESSURE_PROTECTION;
		}

		int x = 240 - ErrorMessage.getTextWidth() / 2;
		ErrorMessage.setXY(x, 205);
		ErrorMessage.resizeToCurrentText();
		ErrorMessage.invalidate();
		nextErrorButton.setVisible(true);
		clearErrorsBtn.setVisible(true);
		prev_error = true;
	} else if (error || check_eng_code > 0 || eng_prot_code > 0) {
		CheckEngCodeValue.setVisible(true);
		Unicode::snprintf(CheckEngCodeValueBuffer, CHECKENGCODEVALUE_SIZE, "%d",
				check_eng_code);
		CheckEngCodeValue.invalidate();

		EngProtCodeValue.setVisible(true);
		Unicode::snprintf(EngProtCodeValueBuffer, ENGPROTCODEVALUE_SIZE, "%d",
				eng_prot_code);
		EngProtCodeValue.invalidate();

		backgroundBox.setColor(getBlackColor());
		backgroundBox.invalidate();
		ErrorMessage.setTypedText(TypedText(*error));
		ErrorMessage.setXY(193, 205);
		ErrorMessage.invalidate();
		nextErrorButton.setVisible(true);
		clearErrorsBtn.setVisible(true);
		cutrrentErrorIndex = 0;
		prev_error = true;
	} else if (prev_error && !has_check_eng_code && !has_eng_prot_code) {
		backgroundBox.setColor(getBlackColor());
		backgroundBox.invalidate();
		ErrorMessage.setTypedText(TypedText(T_NO_ERRORS));
		ErrorMessage.setXY(193, 232);
		ErrorMessage.invalidate();
		nextErrorButton.setVisible(false);
		clearErrorsBtn.setVisible(false);
		CheckEngCodeValue.setVisible(false);
		EngProtCodeValue.setVisible(false);
		prev_error = false;
	}

}

void SecondScreenView::clearErrors() {
	error = NULL;
	check_eng_code = 0;
	eng_prot_code = 0;
	ErrorMessage.setTypedText(TypedText(T_NO_ERRORS));
	ErrorMessage.setXY(193, 232);
	ErrorMessage.invalidate();
	nextErrorButton.setVisible(false);
	clearErrorsBtn.setVisible(false);
	EngProtCodeValue.setVisible(false);
	CheckEngCodeValue.setVisible(false);
	prev_error = true;
}

void SecondScreenView::nextError() {
//	if (cutrrentErrorIndex >= errors.size()) {
//		cutrrentErrorIndex = 0;
//	} else {
//		cutrrentErrorIndex++;
//	}
//	std::vector<int> errorsVector = errorsToVector();
//	int index = errorsVector[cutrrentErrorIndex];
//	TEXTS text = getErrorText(index);
//	ErrorMessage.setTypedText(TypedText(text));
//	int x = 240 - ErrorMessage.getTextWidth() / 2;
//	ErrorMessage.setXY(x, 205);
//	ErrorMessage.resizeToCurrentText();
//	ErrorMessage.invalidate();
}

void SecondScreenView::moveToMainScreen() {
	presenter->setManualErrorChangeScreen();
}

