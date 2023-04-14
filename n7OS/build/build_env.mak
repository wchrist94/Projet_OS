DOCKER=docker
DOCKER_IMAGE=i386-elf-gcc
DOCKER_IMAGE_EXISTS=$(shell docker images $(DOCKER_IMAGE) | grep $(DOCKER_IMAGE) | cut -d' ' -f1)
ifeq ($(DOCKER_IMAGE_EXISTS), $(DOCKER_IMAGE))
	DOCKER_BUILD= @echo Docker image already exists 
else
	DOCKER_BUILD= $(DOCKER) build -t $(DOCKER_IMAGE) docker
endif

CWD=$(shell pwd)
PROJECT=$(shell dirname $(CWD))
CURRENT=$(shell basename $(CWD))
CPU=$(shell uname -m)
OS=$(shell uname -s)
ifeq ($(CPU), arm64)
	PREFIX=$(DOCKER) run --rm -ti -v $(PROJECT):/usr/src/myapp -w /usr/src/myapp/$(CURRENT) $(DOCKER_IMAGE) i386-elf-
	DEBUG=ggdb
else
	ifeq ($(OS), Darwin)
		PREFIX=i386-elf-
		DEBUG=ggdb
	else 
		PREFIX=
		DEBUG=gdb
	endif
endif

CC= $(PREFIX)gcc
CFLAGS= -m32 -gstabs -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra # -Werror

LD= $(PREFIX)ld.bfd
LDFLAGS = -melf_i386

AS= $(PREFIX)gcc
ASFLAGS= -m32 -DASSEMBLER -g -gstabs

OBJCOPY= $(PREFIX)objcopy