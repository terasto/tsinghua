/*
	skyeye_sound.c - skyeye sound device support functions
	Copyright (C) 2003 - 2007 Skyeye Develop Group
        for help please send mail to <skyeye-developer@lists.gro.clinux.org>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

/*
 * 03/25/2007	initial version by Anthony Lee
 */

#include "skyeye_device.h"
#include "skyeye_options.h"
#include "skyeye.h"
#include "skyeye_sound.h"

static int
do_sound_option (skyeye_option_t * this_option, int num_params,
		 const char *params[]);
/*
 * sound_init() : Initialize the sound module set.
 *	If you want to add a new sound simulation,
 *	just add a "sound_*_init" function to it.
 */
static void sound_init(struct device_module_set *mod_set)
{
	//sound_s3c44b0x_init(mod_set);
}


static int sound_setup(struct device_desc *dev, void *option)
{
	struct sound_device *snd_dev;
	struct sound_option *snd_opt = (struct sound_option*)option;
	int ret = 0;

	snd_dev = (struct sound_device*)malloc(sizeof(struct sound_device));
	if (snd_dev == NULL) return -1;

	memset(snd_dev, 0, sizeof(struct sound_device));

	snd_dev->mod = snd_opt->mod;
	snd_dev->channels = snd_opt->channels;
	snd_dev->bits_per_sample = snd_opt->bits_per_sample;
	snd_dev->samples_per_sec = snd_opt->samples_per_sec;

	switch (snd_opt->mod) {
		case SOUND_SIM_PCM:
			snd_dev->sound_open = pcm_sound_open;
			snd_dev->sound_close = pcm_sound_close;
			snd_dev->sound_update = pcm_sound_update;
			snd_dev->sound_read = pcm_sound_read;
			snd_dev->sound_write = pcm_sound_write;
			break;

		default:
			break;
	}

	dev->dev = (void*)snd_dev;
	return ret;
}


static struct device_module_set snd_mod_set = {
	.name = "sound",
	.count = 0,
	.count_max = 0,
	.init = sound_init,
	.initialized = 0,
	.setup_module = sound_setup,
};


/*
 * sound_register() : Used by global device initialize function.
 */
void sound_register(void)
{
	if (register_device_module_set(&snd_mod_set)) {
		SKYEYE_ERR("\"%s\" module set register error!\n", snd_mod_set.name);
	}
	register_option("sound", do_sound_option, "");
}

/* help functions. */
static int
do_sound_option (skyeye_option_t * this_option, int num_params,
		 const char *params[])
{
	char name[MAX_PARAM_NAME], value[MAX_PARAM_NAME];
	struct sound_option snd_opt;
	int i;

	memset (&snd_opt, 0, sizeof(snd_opt));

	for (i = 0; i < num_params; i++) {
		if (split_param (params[i], name, value) < 0)
			SKYEYE_ERR
				("Error: sound has wrong parameter \"%s\".\n",
				 name);
		if (!strncmp ("mod", name, strlen (name))) {
			if (!strncmp ("pcm", value, strlen (value))) {
				snd_opt.mod = 1; /* SOUND_SIM_PCM */
			}
		}
		if (!strncmp ("channels", name, strlen (name))) {
			sscanf (value, "%d", &snd_opt.channels);
		}
		if (!strncmp ("bits_per_sample", name, strlen (name))) {
			sscanf (value, "%d", &snd_opt.bits_per_sample);
		}
		if (!strncmp ("samples_per_sec", name, strlen (name))) {
			sscanf (value, "%d", &snd_opt.samples_per_sec);
		}
	}

	if (snd_opt.mod == 0) return 0;

	SKYEYE_INFO ("sound: channels:%d, bits_per_sample:%d, samples_per_sec:%d.\n",
		     snd_opt.channels, snd_opt.bits_per_sample, snd_opt.samples_per_sec);

	setup_device_option (this_option->option_name, (void*)&snd_opt,
			     num_params, params);

	return 0;
}

