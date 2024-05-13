KERNEL = tatze
CC = x86_64-elf-gcc
LD = x86_64-elf-ld

DEFAULT_CFLAGS = -g -O2 -pipe

CFLAGS = ${DEFAULT_CFLAGS} \
	-Wall \
	-Wextra \
	-Werror \
	-std=c2x \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fPIE \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone

CPPFLAGS = -I src/include \
	-I src/libc/include \
	-MMD \
	-MP

LDFLAGS = -m elf_x86_64 \
	-nostdlib \
	-static \
	-pie \
	--no-dynamic-linker \
	-z text \
	-z max-page-size=0x1000 \
	-T linker.ld

NASMFLAGS = -Wall \
	-felf64 \

CFILES = $(shell find -L src -type f -name '*.c')
NASMFILES = $(shell find -L src -type f -name '*.asm')
HEADER_DEPS = $(shell find -L src -type f -name '*.d')
PSFFILES = $(shell find -L -type f -name '*.psf')

OBJFILES = ${CFILES:.c=.o} ${NASMFILES:.asm=.o} ${PSFFILES:.psf=.o}

.PHONY: all
all: bin/${KERNEL}

bin/${KERNEL}: Makefile linker.ld ${OBJFILES}
	mkdir -p bin
	${LD} ${OBJFILES} ${LDFLAGS} -o $@

%.o: %.psf Makefile
	objcopy -O elf64-x86-64 -B i386 -I binary $< $@

%.asm.o: ${NASMFILES} Makefile
	nasm ${NASMFLAGS} $< -o $@

%.c.o: ${CFILES} Makefile
	${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@

.PHONY: clean

clean:
	rm -rf ${OBJFILES} ${HEADER_DEPS} bin iso limine *.iso