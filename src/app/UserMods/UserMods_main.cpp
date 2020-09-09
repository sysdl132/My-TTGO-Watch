/****************************************************************************
 *  UserMods_main.cpp
 *  Copyright  2020  David Stewart
 *  Email: genericsoftwaredeveloper@gmail.com
 *
 *  Requires Library: IRremoteESP8266 by David Conran
 *
 *  Remote codes are stored in UserMods_main.h, currently only a handful
 *  of Samsung TV remote codes are defined.
 *
 *
 *  Based on the work of Dirk Brosswick,  sharandac / My-TTGO-Watch  Example_App"
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 */
#include "config.h"
#include <TTGO.h>

#include "UserMods.h"
#include "UserMods_main.h"

#include "gui/mainbar/app_tile/app_tile.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"


lv_obj_t *UserMods_main_tile = NULL;
lv_style_t UserMods_main_style;

//lv_task_t * _UserMods_task; //unused

LV_IMG_DECLARE(exit_32px);
LV_IMG_DECLARE(setup_32px);
LV_FONT_DECLARE(Ubuntu_32px);


static void exit_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );
//static void enter_UserMods_setup_event_cb( lv_obj_t * obj, lv_event_t event );

static void Four_Hz_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void One_Hz_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void On_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );
static void Off_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );

static void EnableChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event );

void UserMods_main_setup( uint32_t tile_num ) {

    UserMods_main_tile = mainbar_get_tile_obj( tile_num );
    lv_style_copy( &UserMods_main_style, mainbar_get_style() );

    lv_obj_t * exit_btn = lv_imgbtn_create( UserMods_main_tile, NULL);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_RELEASED, &exit_32px );
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_PRESSED, &exit_32px );
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_RELEASED, &exit_32px );
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_PRESSED, &exit_32px );
    lv_obj_add_style( exit_btn, LV_IMGBTN_PART_MAIN, &UserMods_main_style );
    lv_obj_align( exit_btn, UserMods_main_tile, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10 );
    lv_obj_set_event_cb( exit_btn, exit_UserMods_main_event_cb );

    /*//No use for this just yet
    lv_obj_t * setup_btn = lv_imgbtn_create( UserMods_main_tile, NULL);
    lv_imgbtn_set_src(setup_btn, LV_BTN_STATE_RELEASED, &setup_32px);
    lv_imgbtn_set_src(setup_btn, LV_BTN_STATE_PRESSED, &setup_32px);
    lv_imgbtn_set_src(setup_btn, LV_BTN_STATE_CHECKED_RELEASED, &setup_32px);
    lv_imgbtn_set_src(setup_btn, LV_BTN_STATE_CHECKED_PRESSED, &setup_32px);
    lv_obj_add_style(setup_btn, LV_IMGBTN_PART_MAIN, &UserMods_main_style );
    lv_obj_align(setup_btn, UserMods_main_tile, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10 );
    lv_obj_set_event_cb( setup_btn, enter_UserMods_setup_event_cb );
    */
    
    //Top Left, Charge LED blink 4Hz
    lv_obj_t *UserMods_main_CHGLED4HZ_btn = NULL;
    UserMods_main_CHGLED4HZ_btn = lv_btn_create( UserMods_main_tile, NULL);  
    lv_obj_set_size( UserMods_main_CHGLED4HZ_btn, 70, 40);
    lv_obj_set_event_cb( UserMods_main_CHGLED4HZ_btn, Four_Hz_ChargeLED_UserMods_main_event_cb );
    lv_obj_add_style( UserMods_main_CHGLED4HZ_btn, LV_BTN_PART_MAIN, mainbar_get_button_style() );
    lv_obj_align( UserMods_main_CHGLED4HZ_btn, NULL, LV_ALIGN_CENTER, -80, -90 );
    lv_obj_t *UserMods_4hz_label = lv_label_create( UserMods_main_CHGLED4HZ_btn, NULL);
    lv_label_set_text( UserMods_4hz_label, "4 Hz");
 
    //Top Left, Charge LED blink 1Hz
    lv_obj_t *UserMods_main_CHGLED1HZ_btn = NULL;
    UserMods_main_CHGLED1HZ_btn = lv_btn_create( UserMods_main_tile, NULL);  
    lv_obj_set_size( UserMods_main_CHGLED1HZ_btn, 70, 40);
    lv_obj_set_event_cb( UserMods_main_CHGLED1HZ_btn, One_Hz_ChargeLED_UserMods_main_event_cb );
    lv_obj_add_style( UserMods_main_CHGLED1HZ_btn, LV_BTN_PART_MAIN, mainbar_get_button_style() );
    lv_obj_align( UserMods_main_CHGLED1HZ_btn, NULL, LV_ALIGN_CENTER, -80, -30 );
    lv_obj_t *UserMods_1hz_label = lv_label_create( UserMods_main_CHGLED1HZ_btn, NULL);
    lv_label_set_text( UserMods_1hz_label, "1 Hz");
    
     //Top Left, Charge LED On
    lv_obj_t *UserMods_main_CHGLED1ON_btn = NULL;
    UserMods_main_CHGLED1ON_btn = lv_btn_create( UserMods_main_tile, NULL);  
    lv_obj_set_size( UserMods_main_CHGLED1ON_btn, 70, 40);
    lv_obj_set_event_cb( UserMods_main_CHGLED1ON_btn, On_ChargeLED_UserMods_main_event_cb );
    lv_obj_add_style( UserMods_main_CHGLED1ON_btn, LV_BTN_PART_MAIN, mainbar_get_button_style() );
    lv_obj_align( UserMods_main_CHGLED1ON_btn, NULL, LV_ALIGN_CENTER, -80, 30 );
    lv_obj_t *UserMods_onLed_label = lv_label_create( UserMods_main_CHGLED1ON_btn, NULL);
    lv_label_set_text( UserMods_onLed_label, "On");
    
        //Top Left, Charge LED Off
    lv_obj_t *UserMods_main_CHGLED1OFF_btn = NULL;
    UserMods_main_CHGLED1OFF_btn = lv_btn_create( UserMods_main_tile, NULL);  
    lv_obj_set_size( UserMods_main_CHGLED1OFF_btn, 70, 40);
    lv_obj_set_event_cb( UserMods_main_CHGLED1OFF_btn, Off_ChargeLED_UserMods_main_event_cb );
    lv_obj_add_style( UserMods_main_CHGLED1OFF_btn, LV_BTN_PART_MAIN, mainbar_get_button_style() );
    lv_obj_align( UserMods_main_CHGLED1OFF_btn, NULL, LV_ALIGN_CENTER, 0, -90 );
    lv_obj_t *UserMods_offLed_label = lv_label_create( UserMods_main_CHGLED1OFF_btn, NULL);
    lv_label_set_text( UserMods_offLed_label, "Off");
    
        //Top Left, Charge LED blink
    lv_obj_t *UserMods_main_CHGLEDCHRGCONTROLLED_btn = NULL;
    UserMods_main_CHGLEDCHRGCONTROLLED_btn = lv_btn_create( UserMods_main_tile, NULL);  
    lv_obj_set_size( UserMods_main_CHGLEDCHRGCONTROLLED_btn, 70, 40);
    lv_obj_set_event_cb( UserMods_main_CHGLEDCHRGCONTROLLED_btn, EnableChargeLED_UserMods_main_event_cb );
    lv_obj_add_style( UserMods_main_CHGLEDCHRGCONTROLLED_btn, LV_BTN_PART_MAIN, mainbar_get_button_style() );
    lv_obj_align( UserMods_main_CHGLEDCHRGCONTROLLED_btn, NULL, LV_ALIGN_CENTER, 0, -30 );
    lv_obj_t *UserMods_indicatorOn_label = lv_label_create( UserMods_main_CHGLEDCHRGCONTROLLED_btn, NULL);
    lv_label_set_text( UserMods_indicatorOn_label, "Charge Ind.");
    
    
}

/*//Not yet in use
static void enter_UserMods_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       statusbar_hide( true );
                                        mainbar_jump_to_tilenumber( UserMods_get_app_setup_tile_num(), LV_ANIM_ON );
                                        break;
    }
}
*/

static void exit_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        
                                        mainbar_jump_to_maintile( LV_ANIM_OFF );
                                        break;
    }
}

static void Four_Hz_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        TTGOClass *ttgo;
                                        ttgo = TTGOClass::getWatch();
                                        ttgo->power->setChgLEDMode(AXP20X_LED_BLINK_4HZ);
                                        break;
    }
}

static void One_Hz_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        TTGOClass *ttgo;
                                        ttgo = TTGOClass::getWatch();
                                        ttgo->power->setChgLEDMode(AXP20X_LED_BLINK_1HZ);
                                        break;
    }
}

static void On_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        TTGOClass *ttgo;
                                        ttgo = TTGOClass::getWatch();
                                        ttgo->power->setChgLEDMode(AXP20X_LED_LOW_LEVEL);
                                        break;
    }
}

static void Off_ChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        TTGOClass *ttgo;
                                        ttgo = TTGOClass::getWatch();
                                        ttgo->power->setChgLEDMode(AXP20X_LED_OFF);
                                        break;
    }
}

static void EnableChargeLED_UserMods_main_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        TTGOClass *ttgo;
                                        ttgo = TTGOClass::getWatch();
                                        ttgo->power->EnableChgLEDInd();
                                        break;
    }
}


