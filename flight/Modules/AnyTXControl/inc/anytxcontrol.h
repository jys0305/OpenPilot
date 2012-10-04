/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup AnyTXControlModule AnyTX Control Module
 * @{
 *
 * @file       anytxcontrol.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      AnyTXControl module. Handles safety R/C link and flight mode.
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef ANYTXCONTROL_H
#define ANYTXCONTROL_H

#include "manualcontrolcommand.h"

typedef enum {FLIGHTMODE_UNDEFINED = 0, FLIGHTMODE_MANUAL = 1, FLIGHTMODE_STABILIZED = 2, FLIGHTMODE_GUIDANCE = 3} flightmode_path;

#define PARSE_FLIGHT_MODE(x) ( \
	(x == FLIGHTSTATUS_FLIGHTMODE_MANUAL) ? FLIGHTMODE_MANUAL : \
	(x == FLIGHTSTATUS_FLIGHTMODE_STABILIZED1) ? FLIGHTMODE_STABILIZED : \
	(x == FLIGHTSTATUS_FLIGHTMODE_STABILIZED2) ? FLIGHTMODE_STABILIZED : \
	(x == FLIGHTSTATUS_FLIGHTMODE_STABILIZED3) ? FLIGHTMODE_STABILIZED : \
	(x == FLIGHTSTATUS_FLIGHTMODE_ALTITUDEHOLD) ? FLIGHTMODE_GUIDANCE : \
	(x == FLIGHTSTATUS_FLIGHTMODE_VELOCITYCONTROL) ? FLIGHTMODE_GUIDANCE : \
	(x == FLIGHTSTATUS_FLIGHTMODE_POSITIONHOLD) ? FLIGHTMODE_GUIDANCE : FLIGHTMODE_UNDEFINED \
	)

int32_t AnyTXControlInitialize();


/*
 * These are assumptions we make in the flight code about the order of settings and their consistency between
 * objects.  Please keep this synchronized to the UAVObjects
 */


#define assumptions_channelcount ( \
( (int)MANUALCONTROLCOMMAND_CHANNEL_NUMELEM == (int)ANYTXCONTROLSETTINGS_CHANNELGROUPS_NUMELEM ) && \
( (int)MANUALCONTROLCOMMAND_CHANNEL_NUMELEM == (int)ANYTXCONTROLSETTINGS_CHANNELNUMBER_NUMELEM ) && \
( (int)MANUALCONTROLCOMMAND_CHANNEL_NUMELEM == (int)ANYTXCONTROLSETTINGS_CHANNELMIN_NUMELEM ) && \
( (int)MANUALCONTROLCOMMAND_CHANNEL_NUMELEM == (int)ANYTXCONTROLSETTINGS_CHANNELMAX_NUMELEM ) && \
( (int)MANUALCONTROLCOMMAND_CHANNEL_NUMELEM == (int)ANYTXCONTROLSETTINGS_CHANNELNEUTRAL_NUMELEM ) )

#endif // ANYTXCONTROL_H
