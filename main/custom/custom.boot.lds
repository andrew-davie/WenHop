OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

INCLUDE main/symbols_from_dasm_for_lds.h

_BOOT_SIZE = 0x60;
_DD_START = 0x40000800;
_DRIVER_SIZE = 0x800;


/* Entry Point  */
ENTRY(Custom)

/* Memory Areas  */
MEMORY
{
    boot (RX)   : 	ORIGIN = _PC_ARM_CODE ,	/* C-runtime booter */
			LENGTH = _BOOT_SIZE

    C_code (RX) : 	ORIGIN = _PC_ARM_CODE + _BOOT_SIZE ,
			LENGTH = _PC_ROM_SIZE * 1024 - _PC_ARM_CODE - _BOOT_SIZE

    ram         : 	ORIGIN = _DD_START + _PC_DD_SIZE ,
			LENGTH = _PC_RAM_SIZE * 1024 - _PC_DD_SIZE - _DRIVER_SIZE

}



/* Output sections  */
SECTIONS
{
    .bootcode :
    {
        _sboot = .;
        *(.boot)
        . = ALIGN(4);
        _eboot = .;
    } > boot

    .text : {
        .stext = .;
        . = ALIGN(4);
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } >C_code

    .data : AT ( _etext ) {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } >ram

    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >ram
}
end = .;
