BUILD_DIR = ./object
SRC_DIR = ./src

CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
LDFLAGS = -nostdlib -nostartfiles

all: $(BUILD_DIR)/kernel8.img run

full: clean all

$(BUILD_DIR)/start.o: $(SRC_DIR)/start.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@ -w

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	aarch64-none-elf-gcc $(CFLAGS) -c $< -o $@ -w

$(BUILD_DIR)/kernel8.img: $(BUILD_DIR)/start.o $(OFILES)
	aarch64-none-elf-ld $(LDFLAGS) $(BUILD_DIR)/start.o $(OFILES) -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf
	aarch64-none-elf-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
	rm ./object/kernel8.elf ./object/*.o kernel8.img

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
