// 4.21.1 0xe1ddb5f8
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_alternate_theme_images_backgrounds_480x272_waves[]; // BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_480X272_WAVES_ID = 0, Size: 480x272 pixels
extern const unsigned char image_alternate_theme_images_widgets_boxprogress_normal_tiny[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BOXPROGRESS_NORMAL_TINY_ID = 1, Size: 100x10 pixels
extern const unsigned char image_alternate_theme_images_widgets_button_regular_height_36_tiny_round_inactive[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_36_TINY_ROUND_INACTIVE_ID = 2, Size: 100x36 pixels
extern const unsigned char image_alternate_theme_images_widgets_gauge_medium_needles_smooth[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_MEDIUM_NEEDLES_SMOOTH_ID = 3, Size: 14x75 pixels
extern const unsigned char image_icon_theme_images_navigation_switch_left_50_50_e8f6fb_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_SWITCH_LEFT_50_50_E8F6FB_SVG_ID = 4, Size: 50x50 pixels
extern const unsigned char image_icon_theme_images_navigation_switch_right_50_50_e8f6fb_svg[]; // BITMAP_ICON_THEME_IMAGES_NAVIGATION_SWITCH_RIGHT_50_50_E8F6FB_SVG_ID = 5, Size: 50x50 pixels
extern const unsigned char image_image_rpms[]; // BITMAP_IMAGE_RPMS_ID = 6, Size: 240x240 pixels
extern const unsigned char image_image_speed[]; // BITMAP_IMAGE_SPEED_ID = 7, Size: 240x240 pixels
extern const unsigned char image_logo_fri_en2_03[]; // BITMAP_LOGO_FRI_EN2_03_ID = 8, Size: 800x320 pixels
extern const unsigned char image_termometer[]; // BITMAP_TERMOMETER_ID = 9, Size: 36x36 pixels
extern const unsigned char image_termometer1[]; // BITMAP_TERMOMETER1_ID = 10, Size: 512x512 pixels
extern const unsigned char image_termometer2[]; // BITMAP_TERMOMETER2_ID = 11, Size: 512x512 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_alternate_theme_images_backgrounds_480x272_waves, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_alternate_theme_images_widgets_boxprogress_normal_tiny, 0, 100, 10, 0, 0, 100, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 10, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_alternate_theme_images_widgets_button_regular_height_36_tiny_round_inactive, 0, 100, 36, 17, 0, 66, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 3, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_gauge_medium_needles_smooth, 0, 14, 75, 4, 20, 6, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 43, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_icon_theme_images_navigation_switch_left_50_50_e8f6fb_svg, 0, 50, 50, 29, 18, 7, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 14, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_icon_theme_images_navigation_switch_right_50_50_e8f6fb_svg, 0, 50, 50, 13, 18, 7, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 13, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_image_rpms, 0, 240, 240, 36, 35, 168, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 170, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_image_speed, 0, 240, 240, 36, 35, 168, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 170, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_logo_fri_en2_03, 0, 800, 320, 57, 147, 134, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 134, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_termometer, 0, 36, 36, 1, 0, 34, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 35, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_termometer1, 0, 512, 512, 226, 238, 60, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 225, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_termometer2, 0, 512, 512, 179, 41, 101, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 457, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase