#include <tonc.h>

#include <gba_sram.h>

#define BUFFER_SIZE 50

int main(void) {
    int err;
	u8 buffer[BUFFER_SIZE];

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	
	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));

    // Write Test
    err = sram_write(0, "SRAM Test Passed!", BUFFER_SIZE);
    if (err) {
        tte_write("SRAM Write Failed!");
        goto end;
    }

    // Read Test
    err = sram_read(0, buffer, BUFFER_SIZE);
    if (err) {
        tte_write("SRAM Read Failed!");
    }

    // Final Result
    tte_write(buffer);

end:
	irq_init(NULL);
	irq_enable(II_VBLANK);

	while (1) {
		VBlankIntrWait();
	}
	
}
