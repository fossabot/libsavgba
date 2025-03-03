#include <stddef.h>

#include <tonc_memmap.h>

#include "gba_sram.h"

const char BackupID[] = "SRAM_Vnnn";

IWRAM_CODE
static void sram_memcpy(volatile unsigned char *dst, const volatile unsigned char *src, size_t size) {
    for (;size > 0;--size) 
        *dst++ = *src++;
}

IWRAM_CODE
static unsigned int sram_absmemcmp(const volatile unsigned char *dst, const volatile unsigned char *src, size_t size) {
  while (size-- > 0) {
    unsigned int a = *dst++;
    unsigned int b = *src++;
    if (a != b) 
        return 1;
  }

  return 0;
}

int sram_read(u32 addr, u8 *data, size_t size) {
    if (addr > MEM_SRAM)
        addr -= MEM_SRAM;

    if (addr > SRAM_SIZE || data == NULL)
        return E_INVALID_PARAM;

    sram_memcpy(data, &sram_mem[addr], size);
    
    return 0;
}

int sram_write(u32 addr, u8 *data, size_t size) {
    if (addr > MEM_SRAM)
        addr -= MEM_SRAM;

    if (addr > SRAM_SIZE || data == NULL)
        return E_INVALID_PARAM;

    sram_memcpy(&sram_mem[addr], data, size);

    if (sram_absmemcmp(&sram_mem[addr], data, size))
        return E_VERIFY_FAIL;

    return 0;
}
