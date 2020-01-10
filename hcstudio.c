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
		blit_string(0, 0, "Cock and ball torture (CBT), penis torture");
		blit_string(0, 20, "is a sexual activity involving application");
		blit_string(0, 40, "of pain or constriction to the penis or");
		blit_string(0, 60, "testicles.This may involve directly painful");
		blit_string(0, 80, "activities, such as genital piercing, wax play");
		blit_string(0, 100, "genital spanking, squeezing, ball-busting, genital flogging,");
		blit_string(0, 120, "urethral play, tickle torture, erotic");
		blit_string(0, 140, "electrostimulation, kneeing or kicking");
		blit_string(0, 160, "The recipient of such activities may receive");
		blit_string(0, 180, "direct physical pleasure via masochism, or emotional pleasure");
		blit_string(0, 200, "through erotic humiliation, or knowledge that the play is");
		blit_string(0, 220, "pleasing to a sadistic dominant. Many of these practices");
		blit_string(0, 240, "carry significant health risks");
		
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
