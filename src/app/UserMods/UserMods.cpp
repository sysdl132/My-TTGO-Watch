/****************************************************************************
 *   Aug 3 12:17:11 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
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
#include "config.h"
#include <TTGO.h>

#include "UserMods.h"
#include "UserMods_main.h"
//#include "UserMods_setup.h"

#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "gui/app.h"
#include "gui/widget.h"

uint32_t UserMods_main_tile_num;
uint32_t UserMods_setup_tile_num;

// app icon
icon_t *UserMods = NULL;

// widget icon container
icon_t *UserMods_widget = NULL;

// declare you images or fonts you need
LV_IMG_DECLARE(UserMods_64px);
LV_IMG_DECLARE(info_1_16px);

// declare callback functions for the app and widget icon to enter the app
static void enter_UserMods_event_cb( lv_obj_t * obj, lv_event_t event );
static void enter_UserMods_widget_event_cb( lv_obj_t * obj, lv_event_t event );

/*
 * setup routine for example app
 */
void UserMods_setup( void ) {
    // register 1 vertical tile and get the first tile number and save it for later use
    UserMods_main_tile_num = mainbar_add_app_tile( 1, 1 );
    //UserMods_setup_tile_num = UserMods_main_tile_num + 1;//No use just yet

    // register app icon on the app tile
    // set your own icon and register her callback to activate by an click
    // remember, an app icon must have an size of 64x64 pixel with an alpha channel
    // use https://lvgl.io/tools/imageconverter to convert your images and set "true color with alpha" to get fancy images
    // the resulting c-file can put in /app/examples/images/ and declare it like LV_IMG_DECLARE( your_icon );
    UserMods = app_register( "User\nMods", &UserMods_64px, enter_UserMods_event_cb );
    //app_set_indicator( UserMods, ICON_INDICATOR_OK );

#ifdef UserMods_WIDGET
    // register widget icon on the main tile
    // set your own icon and register her callback to activate by an click
    // remember, an widget icon must have an max size of 64x64 pixel
    // use https://lvgl.io/tools/imageconverter to convert your images and set "true color with alpha" to get fancy images
    // the resulting c-file can put in /app/examples/images/ and declare it like LV_IMG_DECLARE( your_icon );
    UserMods_widget = widget_register( "UserMods", &UserMods_64px, enter_UserMods_widget_event_cb );
    widget_set_indicator( UserMods_widget, ICON_INDICATOR_UPDATE );
#endif // EXAMPLE_WIDGET

    // init main and setup tile, see UserMods_main.cpp and UserMods_setup.cpp
    UserMods_main_setup( UserMods_main_tile_num );
    //UserMods_setup_setup( UserMods_setup_tile_num ); //No use just yet
}

/*
 *
 */
uint32_t UserMods_get_app_main_tile_num( void ) {
    return( UserMods_main_tile_num );
}

/*
 *
 */
/*//Uncomment this line for setup function
uint32_t UserMods_get_app_setup_tile_num( void ) {
    return( UserMods_setup_tile_num );
}

/*
 *
 */
static void enter_UserMods_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       statusbar_hide( true );
                                        app_hide_indicator( UserMods );
                                        mainbar_jump_to_tilenumber( UserMods_main_tile_num, LV_ANIM_OFF );
                                        break;
    }    
}

/*
 *
 */
static void enter_UserMods_widget_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       statusbar_hide( true );
                                        widget_hide_indicator( UserMods_widget );
                                        mainbar_jump_to_tilenumber( UserMods_main_tile_num, LV_ANIM_OFF );
                                        break;
    }    
}
