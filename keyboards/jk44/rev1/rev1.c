#include "rev1.h"

#include "joystick.h"
#include "analog.h"
#include "split_util.h"
#include "transactions.h"
#include "crc.h"

#ifdef JOYSTICK_ENABLE

  #define JOYSTICK_X F6
  #define JOYSTICK_Y F7
  #define JOYSTICK_BUTTON F5

  #define JOYMOUSE_DIV_FAST 100
  #define JOYMOUSE_DIV_SLOW 250
  #define JOYMOUSE_WHEEL_DIV_FAST 100
  #define JOYMOUSE_WHEEL_DIV_SLOW 250

  static int8_t joystick_mode = 1;
  static int16_t mouse_buffer_x = 0;
  static int16_t mouse_buffer_y = 0;
  const int16_t joymouse_threshold = 15;
  static int16_t joymouse_div = JOYMOUSE_DIV_FAST;
  static int16_t joymouse_wheel_div = JOYMOUSE_WHEEL_DIV_FAST;
  static int8_t joystick_calibrate_count = 0;
  const int8_t joystick_calibrate_times = 5;
  static int16_t joystick_offset_x = 0;
  static int16_t joystick_offset_y = 0;
  const int16_t joystick_multiplier_32 = 12;
  const bool joystick_inverse_x = true;
  const bool joystick_inverse_y = true;
  static joystick_status_t own_joystick_status;
  #ifdef SPLIT_JOYSTICK_ENABLE
  static joystick_status_t slave_joystick_status = {.joystick_x=0, .joystick_y=0, .buttons=0};
  #endif // SPLIT_JOYSTICK_ENABLE
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

  int16_t joystick_trim(int16_t joystick_raw){
    return joystick_raw * joystick_multiplier_32 / 32;
  }
//#if POINTING_DEVICE_ENABLE = yes
//#if POINTING_DEVICE_DRIVER = custom
  int16_t joymouse_trim(int16_t joystick_raw){
    if(joystick_raw > 0)
      return joystick_raw > joymouse_threshold ? joystick_raw - joymouse_threshold : 0;
    else
      return joystick_raw < -joymouse_threshold ? joystick_raw + joymouse_threshold : 0;
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

# ifdef SPLIT_JOYSTICK_ENABLE
  void get_joystick_data_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data){
    joystick_status_t *trans = (joystick_status_t*)out_data;
    trans->joystick_x = own_joystick_status.joystick_x;
    trans->joystick_y = own_joystick_status.joystick_y;
    trans->buttons = own_joystick_status.buttons;
  }

  void keyboard_post_init_kb(void){
    transaction_register_rpc(GET_JOYSTICK_DATA, get_joystick_data_slave_handler);
    keyboard_post_init_user();
  }
# endif // SPLIT_JOYSTICK_ENABLE

  void joystick_task(void) {
    if(!joystick_calibrate()){
      own_joystick_status.joystick_x = 0;
      own_joystick_status.joystick_y = 0;
    }
    else{
      own_joystick_status.joystick_x = joystick_read_raw(JOYSTICK_X, joystick_inverse_x, joystick_offset_x);
      own_joystick_status.joystick_y = joystick_read_raw(JOYSTICK_Y, joystick_inverse_y, joystick_offset_y);
    }
    own_joystick_status.buttons = analogReadPin(JOYSTICK_BUTTON) > 20 ? 0 : 1;
    // todo joystick_button
    if(!is_keyboard_master()) return;
#   ifdef SPLIT_JOYSTICK_ENABLE
      bool slave_joystick_update = transaction_rpc_recv(GET_JOYSTICK_DATA, sizeof(slave_joystick_status), &slave_joystick_status);
#   endif // SPLIT_JOYSTICK_ENABLE
    report_mouse_t currentReport = pointing_device_get_report();
    switch(joystick_mode){
      case 0: // gamepad
        #ifndef SPLIT_JOYSTICK_ENABLE
          joystick_status.axes[0] = joystick_trim(own_joystick_status.joystick_x);
          joystick_status.axes[1] = joystick_trim(own_joystick_status.joystick_y);
        #else
          joystick_status.axes[0] = joystick_trim(own_joystick_status.joystick_x);
          joystick_status.axes[1] = joystick_trim(own_joystick_status.joystick_y);
          if(slave_joystick_update){
            joystick_status.axes[2] = joystick_trim(slave_joystick_status.joystick_x);
            joystick_status.axes[3] = joystick_trim(slave_joystick_status.joystick_y);
            if(slave_joystick_status.buttons)
              joystick_status.buttons[0] |= 0b10;
            else
              joystick_status.buttons[0] &= 0b01;
          }
        #endif // SPLIT_JOYSTICK_ENABLE
        if(own_joystick_status.buttons)
          joystick_status.buttons[0] |= 0b01;
        else
          joystick_status.buttons[0] &= 0b10;
        joystick_status.status |= JS_UPDATED;
        send_joystick_packet(&joystick_status);
        joystick_status.status &= ~JS_UPDATED;
        break;

      case 1: // mouse
        joymouse_div = (layer_state & (1 << 2)) ? JOYMOUSE_DIV_SLOW : JOYMOUSE_DIV_FAST;
        joymouse_wheel_div = (layer_state & (1 << 2)) ? JOYMOUSE_WHEEL_DIV_SLOW : JOYMOUSE_WHEEL_DIV_FAST;
        mouse_buffer_x += joymouse_trim(own_joystick_status.joystick_x);
        mouse_buffer_y += joymouse_trim(own_joystick_status.joystick_y);
        currentReport.x = mouse_buffer_x / joymouse_div;
        currentReport.y = mouse_buffer_y / joymouse_div;
        mouse_buffer_x %= joymouse_div;
        mouse_buffer_y %= joymouse_div;
        #ifdef SPLIT_JOYSTICK_ENABLE
          static int16_t mouse_buffer_h = 0;
          static int16_t mouse_buffer_v = 0;
          mouse_buffer_h += joymouse_trim(slave_joystick_status.joystick_x);
          mouse_buffer_v -= joymouse_trim(slave_joystick_status.joystick_y);
          currentReport.h = mouse_buffer_h / joymouse_wheel_div;
          currentReport.v = mouse_buffer_v / joymouse_wheel_div;
          mouse_buffer_h %= joymouse_wheel_div;
          mouse_buffer_v %= joymouse_wheel_div;
        #endif
        pointing_device_set_report(currentReport);
        pointing_device_send();
        break;
    }
  }

#endif // JOYSTICK_ENABLE
