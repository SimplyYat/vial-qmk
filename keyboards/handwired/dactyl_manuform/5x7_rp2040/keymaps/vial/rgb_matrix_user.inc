// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(custom_solid_colours)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "action_layer.h"
#ifndef CUSTOM_RGB_H
#include "custom_rgb.h"
#endif

static bool custom_solid_colours(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  if(get_highest_layer(layer_state) > 0){
    set_active_layer_colours(led_min, led_max);
  }
  else{
    set_base_layer_colours(led_min, led_max);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
