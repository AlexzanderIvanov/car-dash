/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/secondscreen_screen/SecondScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

SecondScreenViewBase::SecondScreenViewBase() :
    buttonCallback(this, &SecondScreenViewBase::buttonCallbackHandler),
    flexButtonCallback(this, &SecondScreenViewBase::flexButtonCallbackHandler)
{

    backgroundBox.setPosition(0, 0, 480, 272);
    backgroundBox.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    ButtonGoToMainScreen.setBoxWithBorderPosition(0, 0, 133, 272);
    ButtonGoToMainScreen.setBorderSize(5);
    ButtonGoToMainScreen.setBoxWithBorderColors(touchgfx::Color::getColorFrom24BitRGB(0, 102, 153), touchgfx::Color::getColorFrom24BitRGB(0, 153, 204), touchgfx::Color::getColorFrom24BitRGB(0, 51, 102), touchgfx::Color::getColorFrom24BitRGB(51, 102, 153));
    ButtonGoToMainScreen.setPosition(0, 0, 133, 272);
    ButtonGoToMainScreen.setAlpha(0);
    ButtonGoToMainScreen.setAction(flexButtonCallback);

    IngAngValue.setPosition(12, 11, 71, 42);
    IngAngValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    IngAngValue.setLinespacing(0);
    Unicode::snprintf(IngAngValueBuffer, INGANGVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID77).getText());
    IngAngValue.setWildcard(IngAngValueBuffer);
    IngAngValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID76));

    IgnAngDescriptor.setXY(12, 53);
    IgnAngDescriptor.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 220, 0));
    IgnAngDescriptor.setLinespacing(0);
    IgnAngDescriptor.setTypedText(touchgfx::TypedText(T_SINGLEUSEID78));

    ErrorMessage.setXY(193, 205);
    ErrorMessage.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 220, 0));
    ErrorMessage.setLinespacing(0);
    Unicode::snprintf(ErrorMessageBuffer, ERRORMESSAGE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID80).getText());
    ErrorMessage.setWildcard(ErrorMessageBuffer);
    ErrorMessage.resizeToCurrentText();
    ErrorMessage.setTypedText(touchgfx::TypedText(T_SINGLEUSEID79));

    nextErrorButton.setXY(256, 226);
    nextErrorButton.setBitmaps(touchgfx::Bitmap(BITMAP_ICONFINDER_NEXT_6290417_ID), touchgfx::Bitmap(BITMAP_ICONFINDER_NEXT_6290417_ID));
    nextErrorButton.setAction(buttonCallback);

    clearErrorsBtn.setXY(193, 226);
    clearErrorsBtn.setBitmaps(touchgfx::Bitmap(BITMAP_ICONFINDER_7_SOUND_OFF_3279057_ID), touchgfx::Bitmap(BITMAP_ICONFINDER_7_SOUND_OFF_3279057_ID));
    clearErrorsBtn.setAction(buttonCallback);

    add(backgroundBox);
    add(ButtonGoToMainScreen);
    add(IngAngValue);
    add(IgnAngDescriptor);
    add(ErrorMessage);
    add(nextErrorButton);
    add(clearErrorsBtn);
}

void SecondScreenViewBase::setupScreen()
{

}

void SecondScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &nextErrorButton)
    {
        //DisplayNextErrorInteraction
        //When nextErrorButton clicked call virtual function
        //Call nextError
        nextError();
    }
    else if (&src == &clearErrorsBtn)
    {
        //ClearErrorsInteraction
        //When clearErrorsBtn clicked call virtual function
        //Call clearErrors
        clearErrors();
    }
}

void SecondScreenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &ButtonGoToMainScreen)
    {
        //MoveToMainScreenBtnInteraction
        //When ButtonGoToMainScreen clicked call virtual function
        //Call moveToMainScreen
        moveToMainScreen();

        //MoveToMainScreenInteraction
        //When MoveToMainScreenBtnInteraction completed change screen to Main
        //Go to Main with screen transition towards West
        application().gotoMainScreenSlideTransitionWest();
    }
}
