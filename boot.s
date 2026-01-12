.set MEMINFO, 1<<1
.set MODULES, 1<<0
.set FLAGS, MODULES | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .mutliboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_butt:
.skip 16284
stack_top:

.section .text
.global _start
.type _start, @function
_start:
  movl $stack_top,%esp
  call ilyass
  cli
hna:
  hlt
  jmp hna
  
  
