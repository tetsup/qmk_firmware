#include "rev1.h"

#include "joystick.h"
#include "analog.h"
//#include "split_util.h"

#ifdef JOYSTICK_ENABLE

  #define JOYSTICK_X F6
  #define JOYSTICK_Y F7
  //#define JOYSTICK_BUTTON F5

  #define JOYMOUSE_DIV_FAST 100
  #define JOYMOUSE_DIV_SLOW 250

  static int8_t joystick_mode = 1;
  static int16_t mouse_buffer_x = 0;
  static int16_t mouse_buffer_y = 0;
  const int16_t joymouse_threshold = 15;
  static int16_t joymouse_div = JOYMOUSE_DIV_FAST;
  static int8_t joystick_calibrate_count = 0;
  const int8_t joystick_calibrate_times = 5;
  static int16_t joystick_offset_x = 0;
  static int16_t joystick_offset_y = 0;
  const int16_t joystick_multiplier_32 = 12;
  const bool joystick_inverse_x = true;
  const bool joystick_inverse_y = true;

#endif // JOYOSTICK_ENABLE

#ifdef OLED_ENABLE
  oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_left())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
  }
#endif // OLED ENABLE

#ifdef JOYSTICK_ENABLE
  int16_t joystick_read_raw(pin_t pin, bool inverse, int16_t offset){
    if(inverse) return 511 - analogReadPin(pin) + offset;
    else return analogReadPin(pin) - 512 - offset;
  }

  int16_t joystick_read(pin_t pin, bool inverse, int16_t offset){
    return (joystick_read_raw(pin, inverse, offset)) * joystick_multiplier_32 / 32;
  }

  int16_t joymouse_read(pin_t pin, bool inverse, int16_t offset){
    const int16_t joy = joystick_read_raw(pin, inverse, offset);
    if(joy > 0)
      return joy > joymouse_threshold ? joy - joymouse_threshold : 0;
    else
      return joy < -joymouse_threshold ? joy + joymouse_threshold : 0;
  }

  void change_joystick_mode(int8_t mode) {
    joystick_mode = mode;
  }

  uint8_t toggle_joystick_mode(void) {
    change_joystick_mode((joystick_mode + 1) % 2);
    return get_joystick_mode();
  }

  void reset_joystick_calibrate(void){
    joystick_offset_x = 0;
    joystick_offset_y = 0;
    joystick_calibrate_count = 0;
  }

  uint8_t get_joystick_mode(void) {
    return joystick_mode;
  }

  bool joystick_calibrate(void){
    if(joystick_calibrate_count >= joystick_calibrate_times) return true;
    joystick_offset_x += joystick_read_raw(JOYSTICK_X, false, 0);
    joystick_offset_y += joystick_read_raw(JOYSTICK_Y, false, 0);
    joystick_calibrate_count++;
    if(joystick_calibrate_count == joystick_calibrate_times){
      joystick_offset_x /= joystick_calibrate_times;
      joystick_offset_y /= joystick_calibrate_times;
      return true;
    }
    return false;
  }

  void joystick_task(void) {
    switch(joystick_mode){
      case 0: // gamepad
        if(!joystick_calibrate()){
          joystick_status.axes[0] = 0;
          joystick_status.axes[1] = 0;
        }
        else{
          joystick_status.axes[0] = joystick_read(JOYSTICK_X, joystick_inverse_x, joystick_offset_x);
          joystick_status.axes[1] = joystick_read(JOYSTICK_Y, joystick_inverse_y, joystick_offset_y);
        }
        //    setPinInput(JOYSTICK_BUTTON);
        //    joystick_status.buttons[0] = readPin(JOYSTICK_BUTTON);
        if(analogReadPin(F5) > 20)
          joystick_status.buttons[0] = 3;
        else
          joystick_status.buttons[0] = 0;
        joystick_status.status |= JS_UPDATED;
        send_joystick_packet(&joystick_status);
        joystick_status.status &= ~JS_UPDATED;
        break;

      case 1: // mouse
        if(!joystick_calibrate()) break;
        
        joymouse_div = (layer_state & (1 << 2)) ? JOYMOUSE_DIV_SLOW : JOYMOUSE_DIV_FAST;
        mouse_buffer_x += joymouse_read(JOYSTICK_X, joystick_inverse_x, joystick_offset_x);
        mouse_buffer_y += joymouse_read(JOYSTICK_Y, joystick_inverse_y, joystick_offset_y);
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.x = mouse_buffer_x / joymouse_div;
        currentReport.y = mouse_buffer_y / joymouse_div;
        mouse_buffer_x %= joymouse_div;
        mouse_buffer_y %= joymouse_div;
        pointing_device_set_report(currentReport);
        pointing_device_send();
        break;
    }
  }

#endif // JOYSTICK_ENABLE
