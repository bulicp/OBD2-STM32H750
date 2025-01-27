/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase() :
    buttonCallback(this, &Screen2ViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_480X272_WAVES_ID));
    add(image1);

    textArea1.setXY(199, 259);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_34L5));
    add(textArea1);

    buttonWithIcon1.setXY(380, 0);
    buttonWithIcon1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_36_TINY_ROUND_INACTIVE_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_36_TINY_ROUND_INACTIVE_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_NAVIGATION_SWITCH_RIGHT_50_50_E8F6FB_SVG_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_NAVIGATION_SWITCH_RIGHT_50_50_E8F6FB_SVG_ID));
    buttonWithIcon1.setIconXY(25, -7);
    buttonWithIcon1.setAction(buttonCallback);
    add(buttonWithIcon1);

    gaugeRPM.setBackground(touchgfx::Bitmap(BITMAP_IMAGE_RPMS_ID));
    gaugeRPM.setPosition(240, 32, 240, 240);
    gaugeRPM.setCenter(120, 120);
    gaugeRPM.setStartEndAngle(-113, 112);
    gaugeRPM.setRange(0, 5000);
    gaugeRPM.setValue(0);
    gaugeRPM.setEasingEquation(touchgfx::EasingEquations::cubicEaseInOut);
    gaugeRPM.setNeedle(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_MEDIUM_NEEDLES_SMOOTH_ID, 7, 67);
    gaugeRPM.setMovingNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    gaugeRPM.setSteadyNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    gaugeRPM.setArcVisible();
    gaugeRPMPainter.setColor(touchgfx::Color::getColorFromRGB(237, 219, 14));
    gaugeRPM.getArc().setPainter(gaugeRPMPainter);
    gaugeRPM.getArc().setRadius(103);
    gaugeRPM.getArc().setLineWidth(7);
    gaugeRPM.getArc().setCapPrecision(10);
    add(gaugeRPM);

    boxProgressTemp.setXY(310, 221);
    boxProgressTemp.setProgressIndicatorPosition(0, 0, 100, 10);
    boxProgressTemp.setRange(0, 180);
    boxProgressTemp.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    boxProgressTemp.setBackground(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BOXPROGRESS_NORMAL_TINY_ID));
    boxProgressTemp.setColor(touchgfx::Color::getColorFromRGB(78, 252, 25));
    boxProgressTemp.setValue(5);
    add(boxProgressTemp);

    gaugeSpeed.setBackground(touchgfx::Bitmap(BITMAP_IMAGE_SPEED_ID));
    gaugeSpeed.setPosition(0, 32, 240, 240);
    gaugeSpeed.setCenter(120, 120);
    gaugeSpeed.setStartEndAngle(-113, 112);
    gaugeSpeed.setRange(0, 200);
    gaugeSpeed.setValue(0);
    gaugeSpeed.setEasingEquation(touchgfx::EasingEquations::cubicEaseInOut);
    gaugeSpeed.setNeedle(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_MEDIUM_NEEDLES_SMOOTH_ID, 7, 67);
    gaugeSpeed.setMovingNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    gaugeSpeed.setSteadyNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    gaugeSpeed.setArcVisible();
    gaugeSpeedPainter.setColor(touchgfx::Color::getColorFromRGB(24, 214, 59));
    gaugeSpeed.getArc().setPainter(gaugeSpeedPainter);
    gaugeSpeed.getArc().setRadius(103);
    gaugeSpeed.getArc().setLineWidth(7);
    gaugeSpeed.getArc().setCapPrecision(10);
    add(gaugeSpeed);

    line1.setPosition(360, 221, 10, 10);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(240, 160, 12));
    line1.setPainter(line1Painter);
    line1.setStart(0, 0);
    line1.setEnd(0, 9);
    line1.setLineWidth(3);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    textAmbientTemp.setPosition(0, 0, 72, 23);
    textAmbientTemp.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAmbientTemp.setLinespacing(0);
    Unicode::snprintf(textAmbientTempBuffer, TEXTAMBIENTTEMP_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_2F84).getText());
    textAmbientTemp.setWildcard(textAmbientTempBuffer);
    textAmbientTemp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_U82J));
    add(textAmbientTemp);

    scalableImage1.setBitmap(touchgfx::Bitmap(BITMAP_LOGO_FRI_EN2_03_ID));
    scalableImage1.setPosition(180, 0, 120, 45);
    scalableImage1.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(scalableImage1);

    circle1.setPosition(70, 102, 100, 100);
    circle1.setCenter(50, 50);
    circle1.setRadius(50);
    circle1.setLineWidth(0);
    circle1.setArc(0, 360);
    circle1Painter.setColor(touchgfx::Color::getColorFromRGB(176, 199, 214));
    circle1.setPainter(circle1Painter);
    add(circle1);

    textSpeed.setPosition(72, 128, 97, 48);
    textSpeed.setColor(touchgfx::Color::getColorFromRGB(3, 65, 87));
    textSpeed.setLinespacing(0);
    Unicode::snprintf(textSpeedBuffer, TEXTSPEED_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_C3A7).getText());
    textSpeed.setWildcard(textSpeedBuffer);
    textSpeed.setTypedText(touchgfx::TypedText(T___SINGLEUSE_EZPO));
    add(textSpeed);

    scalableImage2.setBitmap(touchgfx::Bitmap(BITMAP_TERMOMETER2_ID));
    scalableImage2.setPosition(352, 234, 20, 20);
    scalableImage2.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(scalableImage2);
}

Screen2ViewBase::~Screen2ViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithIcon1)
    {
        //Interaction1
        //When buttonWithIcon1 clicked change screen to Screen1
        //Go to Screen1 with screen transition towards East
        application().gotoScreen1ScreenCoverTransitionEast();
    }
}
