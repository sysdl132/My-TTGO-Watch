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
#ifndef _NETTOOLS_MAIN_H
    #define _NETTOOLS_MAIN_H

    #include <TTGO.h>

    void NetTools_main_setup( uint32_t tile_num );

#endif // _EXAMPLE_APP_MAIN_H

//Replace these with those appropriate for your network!    
#define MY_PC_WOL_MAC "F8:B1:56:A1:71:95" //MAC Address Used For WOL
#define WOL_NAME "Freki"
#define TOGGLE1_NAME "Tasmota1"
#define TOGGLE1_URL "http://172.17.2.31/cm?cmnd=Power%20Toggle"  //Tasmota1 Toggle Url
