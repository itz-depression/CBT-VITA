#include <taihen.h>
#include <string.h>
#include <stdio.h>
#include "blit.h"
#include <psp2kern/power.h> 

static SceUID g_hooks[1];

static tai_hook_ref_t ref_hook0;
int _sceDisplaySetFrameBufInternalForDriver(int fb_id1, int fb_id2, const SceDisplayFrameBuf *pParam, int sync){
	if(fb_id1 == ksceDisplayGetPrimaryHead() && pParam) {
		SceDisplayFrameBuf kfb;
		memset(&kfb,0,sizeof(kfb));
		memcpy(&kfb, pParam, sizeof(SceDisplayFrameBuf));
		blit_set_frame_buf(&kfb);
		blit_set_color(0x00000000, 0x00ffffff);
		blit_string(0, 0, "Cock and ball torture (CBT), penis torture or dick torture is a sexual activity involving application of pain or constriction to the penis or testicles. This may involve directly painful activities, such as genital piercing, wax play, genital spanking, squeezing, ball-busting, genital flogging, urethral play, tickle torture, erotic electrostimulation, kneeing or kicking.[1] The recipient of such activities may receive direct physical pleasure via masochism, or emotional pleasure through erotic humiliation, or knowledge that the play is pleasing to a sadistic dominant. Many of these practices carry significant health risks.[2]");
	}
	return TAI_CONTINUE(int, ref_hook0, fb_id1, fb_id2, pParam, sync);
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {	
	g_hooks[0] = taiHookFunctionExportForKernel(KERNEL_PID, &ref_hook0, "SceDisplay",0x9FED47AC,0x16466675, _sceDisplaySetFrameBufInternalForDriver); 
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
	if (g_hooks[0] >= 0) taiHookReleaseForKernel(g_hooks[0], ref_hook0);
	return SCE_KERNEL_STOP_SUCCESS;
}
