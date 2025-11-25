#include <3ds.h>
#include <citro2d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_BARS 16
#define MAX_BAR_HEIGHT 128

int main(void) {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    C2D_Init();
    C2D_Target* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    ndspInit();
    ndspChnReset(0);
    ndspChnWaveBuf buf;
    memset(&buf, 0, sizeof(buf));

    float mic_buffer[1024];
    float bar_heights[NUM_BARS] = {0};

    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & KEY_START) break;

        // Read mic
        u32 read = osMicRead(mic_buffer, 1024);
        for (int i = 0; i < NUM_BARS; i++) {
            int start = (i * 1024) / NUM_BARS;
            float sum = 0;
            for (int j = 0; j < 1024 / NUM_BARS; j++) {
                sum += fabsf(mic_buffer[start + j]);
            }
            bar_heights[i] = (sum / (1024 / NUM_BARS)) * MAX_BAR_HEIGHT;
        }

        // Draw
        C2D_TargetClear(top, C2D_Color32(0, 0, 0, 255));
        C2D_SceneBegin(top);

        for (int i = 0; i < NUM_BARS; i++) {
            float h = bar_heights[i];
            C2D_DrawRectSolid(i*16, MAX_BAR_HEIGHT - h, 0, 12, h, C2D_Color32(128, 0, 255, 255));
        }

        C2D_Flush();
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    ndspExit();
    C2D_Fini();
    gfxExit();
    return 0;
}
