#include <gui/main_screen/MainView.hpp>
#include <message_types.h>

#include <touchgfx/Color.hpp>

static int color_index = 0;
static int rev_limit_warning = 6200;
static int rev_limit = 9000;

static int prev_rpm = 100;
static int prev_clt = 110;
static float prev_lambda = 0.77f;
static float prev_lambda_targ = 0.81f;
static int prev_oil_tmp = 0;
static float prev_oil_press = 0;
static int prev_tps = 0;
static int prev_br_p = 0;
static int prev_diff_t = 0;

static int prev_tpms_t_fr = 0;
static int prev_tpms_t_fl = 0;
static int prev_tpms_t_rr = 0;
static int prev_tpms_t_rl = 0;

static int prev_tpms_p_fr = 0;
static int prev_tpms_p_fl = 0;
static int prev_tpms_p_rr = 0;
static int prev_tpms_p_rl = 0;

MainView::MainView() {
	// Support of larger displays for this example
	// is handled by showing a black box in the
	// unused part of the display.
	if (HAL::DISPLAY_WIDTH > backgroundImage.getWidth()
			|| HAL::DISPLAY_HEIGHT > backgroundImage.getHeight()) {
		backgroundBox.setVisible(true);
	}
}

void MainView::setupScreen() {
}

void MainView::tearDownScreen() {
}

static colortype getYellowColor() {
	colortype black_color = touchgfx::Color::getColorFrom24BitRGB(255, 255, 0);
	return black_color;
}

static colortype getRedColor() {
	colortype black_color = touchgfx::Color::getColorFrom24BitRGB(255, 0, 0);
	return black_color;
}

static colortype getBlackColor() {
	colortype black_color = touchgfx::Color::getColorFrom24BitRGB(0, 0, 0);
	return black_color;
}

static colortype getColorFromRevLimit() {

	color_index++;
	if (color_index >= 3) {
		color_index = 0;
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

void MainView::updateSettings(uint8_t *settings) {
	settings_message *new_settings = (settings_message*) settings;

	rev_limit_warning = (int) new_settings->rpm_limit_warning;
	rev_limit = (int) new_settings->rpm_limit;

	RPMProgressBar.setRange(0, (int) (new_settings->rpm8 * 1000.0f), 0, 0);
	RPMProgressBar.invalidate();

	Unicode::snprintf(rpm1Buffer, RPM1_SIZE, "%d", new_settings->rpm1);
	rpm1.resizeToCurrentText();
	rpm1.invalidate();
	Unicode::snprintf(rpm2Buffer, RPM2_SIZE, "%d", new_settings->rpm2);
	rpm2.resizeToCurrentText();
	rpm2.invalidate();
	Unicode::snprintf(rpm3Buffer, RPM3_SIZE, "%d", new_settings->rpm3);
	rpm3.resizeToCurrentText();
	rpm3.invalidate();
	Unicode::snprintf(rpm4Buffer, RPM4_SIZE, "%d", new_settings->rpm4);
	rpm4.resizeToCurrentText();
	rpm4.invalidate();
	Unicode::snprintf(rpm5Buffer, RPM5_SIZE, "%d", new_settings->rpm5);
	rpm5.resizeToCurrentText();
	rpm5.invalidate();
	Unicode::snprintf(rpm6Buffer, RPM6_SIZE, "%d", new_settings->rpm6);
	rpm6.resizeToCurrentText();
	rpm6.invalidate();
	Unicode::snprintf(rpm7Buffer, RPM7_SIZE, "%d", new_settings->rpm7);
	rpm7.resizeToCurrentText();
	rpm7.invalidate();
	Unicode::snprintf(rpm8Buffer, RPM8_SIZE, "%d", new_settings->rpm8);
	rpm8.resizeToCurrentText();
	rpm8.invalidate();

}

void MainView::updateVal(uint8_t *newValue) {
	static bool background_is_black = false;
	display_values *values = (display_values*) newValue;

	bool on_rev_limit_warning = values->rpm >= rev_limit_warning;
	bool on_rev_limiter = values->rpm >= rev_limit;
	//Commented because of strange behavior of EMU error codes. It is not reliable and irritating at this stage.
//	bool has_error = ((int) values->emu_errors) > 0 || ((int) values->emu_protection) > 0
//			|| ((int) values->check_eng_code) > 0 || ((int) values->eng_protection_code) > 0;
//	if (has_error) {
//		backgroundBox.setColor(getRedColor());
//		backgroundBox.invalidate();
//	} else
	if(on_rev_limit_warning && !on_rev_limiter) {
		background_is_black = false;
		backgroundBox.setColor(getYellowColor());
		backgroundBox.invalidate();
	} else if (on_rev_limiter) {
		background_is_black = false;
		backgroundBox.setColor(getColorFromRevLimit());
		backgroundBox.invalidate();
	} else if (!background_is_black) {
		backgroundBox.setColor(getBlackColor());
		backgroundBox.invalidate();
		background_is_black = true;
	}

	if (values->rpm != prev_rpm) {
		prev_rpm = values->rpm;
		RPMProgressBar.setValue(values->rpm);
		RPMProgressBar.invalidate();

		Unicode::snprintf(RPMValueBuffer, RPMVALUE_SIZE, "%d", values->rpm);
		RPMValue.invalidate();
	}

	if (values->clt != prev_clt) {
		prev_clt = values->clt;
		Unicode::snprintf(CLTValueBuffer, CLTVALUE_SIZE, "%d", values->clt);
		CLTValue.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdFr() && values->tpms_press != prev_tpms_p_fr) {
		prev_tpms_p_fr = values->tpms_press;
		Unicode::snprintfFloat(TpFrBuffer, TPFR_SIZE, "%.2f",
				(float)(values->tpms_press / (float)100));
		TpFr.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdFr() && values->tpms_temp != prev_tpms_t_fr) {
		prev_tpms_t_fr = values->tpms_temp;
			Unicode::snprintf(TtFrBuffer, TTFR_SIZE, "%d", values->tpms_temp);
		TtFr.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdRr() && values->tpms_press != prev_tpms_p_rr) {
		prev_tpms_p_rr = values->tpms_press;
			Unicode::snprintfFloat(TpRrBuffer, TPRR_SIZE, "%.2f",
					(float)(values->tpms_press / (float)100));
		TpRr.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdRr() && values->tpms_temp != prev_tpms_t_rr) {
		prev_tpms_t_rr = values->tpms_temp;
			Unicode::snprintf(TtRrBuffer, TTRR_SIZE, "%d", values->tpms_temp);
		TtRr.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdRl() && values->tpms_press != prev_tpms_p_rl) {
		prev_tpms_p_rl = values->tpms_press;
				Unicode::snprintfFloat(TpRlBuffer, TPRL_SIZE, "%.2f",
						(float)(values->tpms_press / (float)100));
		TpRl.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdRl() && values->tpms_temp != prev_tpms_t_rl) {
			prev_tpms_t_rl = values->tpms_temp;
				Unicode::snprintf(TtRlBuffer, TTRL_SIZE, "%d", values->tpms_temp);
			TtRl.invalidate();
		}

	if (values->tpms_id == presenter->getTpmsIdFl() && values->tpms_press != prev_tpms_p_fl) {
		prev_tpms_p_fl = values->tpms_press;
					Unicode::snprintfFloat(TpFlBuffer, TPFL_SIZE, "%.2f",
							(float)(values->tpms_press / (float)100));
		TpFl.invalidate();
	}

	if (values->tpms_id == presenter->getTpmsIdFl() && values->tpms_temp != prev_tpms_t_fl) {
		prev_tpms_t_fl = values->tpms_temp;
			Unicode::snprintf(TtFlBuffer, TTFL_SIZE, "%d", (values->tpms_temp));
		TtFl.invalidate();
	}

	if (values->oil_press != prev_oil_press) {
		prev_oil_press = values->oil_press;
		Unicode::snprintfFloat(OILPressureValueBuffer, OILPRESSUREVALUE_SIZE,
				"%.1f", values->oil_press);
		OILPressureValue.invalidate();
	}

	if (values->diff_tmp != prev_diff_t) {
		prev_diff_t = values->diff_tmp;
		Unicode::snprintf(DiffTBuffer, DIFFT_SIZE, "%d",
				values->diff_tmp);
		DiffT.invalidate();
	}

	if (values->oil_tmp != prev_oil_tmp) {
		prev_oil_tmp = values->oil_tmp;
		Unicode::snprintf(OILTempValueBuffer, OILTEMPVALUE_SIZE, "%d",
				values->oil_tmp);
		OILTempValue.invalidate();
	}



	if (values->tps != prev_tps) {
		prev_tps = values->tps;
		TPSProgress.setValue(values->tps);
		RPMProgressBar.invalidate();
		Unicode::snprintf(TpsNumberValueBuffer, TPSNUMBERVALUE_SIZE, "%d",
				values->tps);
		TpsNumberValue.invalidate();
	}

	if (values->br_p != prev_br_p) {
		prev_br_p = values->br_p;
		BrP.setValue(values->br_p);
		BrP.invalidate();
		Unicode::snprintf(BrPrValueBuffer, BRPRVALUE_SIZE, "%d", values->br_p);
		BrPrValue.invalidate();
	}

	//Commented because of strange behavior of EMU error codes. Need USB to CAN to trace the problem.
//	if (has_error && !presenter->getManualErrorChangeScreen()) {
//		static_cast<FrontendApplication*>(Application::getInstance())->gotoSecondScreenScreenSlideTransitionEast();
//	}
}
