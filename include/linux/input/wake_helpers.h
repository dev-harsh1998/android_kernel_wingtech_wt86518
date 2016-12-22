/*
 * include/linux/input/wake_helpers.h
 *
 * Copyright (c) 2015, Vineeth Raj <contact.twn@openmailbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _LINUX_WAKE_HELPERS_H
#define _LINUX_WAKE_HELPERS_H

#include <stdbool.h>

#ifdef CONFIG_TOUCHSCREEN_SWEEP2WAKE
#include <linux/input/sweep2wake.h>
#endif

#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
#include <linux/input/doubletap2wake.h>
#endif

#if defined(CONFIG_TOUCHSCREEN_SWEEP2WAKE) && defined(CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE)
#define ts_get_prevent_sleep(prevent_sleep) { \
	prevent_sleep = (s2w_switch || dt2w_switch); \
	prevent_sleep = (prevent_sleep && !var_in_phone_call); \
}
#else
#if defined(CONFIG_TOUCHSCREEN_SWEEP2WAKE) || defined(CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE)
#ifdef CONFIG_TOUCHSCREEN_SWEEP2WAKE
#define ts_get_prevent_sleep(prevent_sleep) { \
	prevent_sleep = (s2w_switch > 0); \
	prevent_sleep = (prevent_sleep && !var_in_phone_call); \
}
#endif // S2W
#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
#define ts_get_prevent_sleep(prevent_sleep) { \
	prevent_sleep = (dt2w_switch > 0); \
	prevent_sleep = (prevent_sleep && !var_in_phone_call); \
}
#endif // DT2W
#else
#define ts_get_prevent_sleep(prevent_sleep) { \
	prevent_sleep = (prevent_sleep && !var_in_phone_call); \
}
#endif // S2W||DT2W
#endif // S2W&&DT2W

extern bool dit_suspend;   // to track if its we who called ts to _not_ suspend

extern bool var_in_phone_call;
//extern int headset_plugged_in;
extern int var_is_headset_in_use;
extern int var_in_pocket;

extern bool s2w_scr_suspended;
extern bool dt2w_scr_suspended;

int is_headset_in_use(void);
int in_phone_call(void);
int in_pocket(void);
void read_proximity(void);

extern int dt2w_sent_play_pause;

#endif  /* _LINUX_WAKE_HELPERS_H */
