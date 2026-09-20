################################################################################
# Makefile for BTL_AVR (ATmega324P)
# Microcontroller: ATmega324P
# Clock frequency: 8.000.000 Hz (8MHz)
################################################################################

# Tên file đầu ra
TARGET = BTL_AVR

# Cấu hình vi điều khiển và tần số thạch anh
MCU   = atmega324p
F_CPU = 8000000UL

# Thư mục chứa kết quả biên dịch
BUILD_DIR = build

# Đường dẫn Toolchain Atmel Studio 7 (mặc định nếu không có trong PATH)
TOOLCHAIN_DIR ?= C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/bin
PACK_DIR      ?= C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374

# Kiểm tra avr-gcc trong PATH hay dùng đường dẫn mặc định
CC      := "$(TOOLCHAIN_DIR)/avr-gcc.exe"
OBJCOPY := "$(TOOLCHAIN_DIR)/avr-objcopy.exe"
OBJDUMP := "$(TOOLCHAIN_DIR)/avr-objdump.exe"
SIZE    := "$(TOOLCHAIN_DIR)/avr-size.exe"

# Các thư mục Include
INCLUDES = \
	-I. \
	-IAPP \
	-IAPP/APP_DISPLAY \
	-IAPP/TEST_LCD_3 \
	-IAPP_BUTTON \
	-IBSP \
	-ICOMMON \
	-IDATA \
	-IDRIVER \
	-I"$(PACK_DIR)/include"

# Danh sách các file mã nguồn C trong dự án
SRCS = \
	main.c \
	APP/APP_DHT.c \
	APP/APP_LCD_3.c \
	APP/APP_DISPLAY/app_display.c \
	APP/TEST_LCD_3/test_lcd_3.c \
	APP_BUTTON/APP_BUTTON.c \
	APP_BUTTON/DATA_BUTTON.c \
	BSP/BSP_BUTTON.c \
	BSP/BSP_DHT.c \
	BSP/BSP_LCD.c \
	BSP/BSP_LED.c \
	BSP/BSP_TIMER.c \
	DATA/DATA_DHT.c \
	DRIVER/GPIO.c \
	DRIVER/LCD.c

# Tạo danh sách các file object tương ứng đặt trong $(BUILD_DIR)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# Cờ biên dịch cho trình biên dịch C (GCC)
CFLAGS = \
	-mmcu=$(MCU) \
	-B "$(PACK_DIR)/gcc/dev/$(MCU)" \
	-DF_CPU=$(F_CPU) \
	-DDEBUG \
	-Og \
	-g2 \
	-Wall \
	-std=gnu99 \
	-funsigned-char \
	-funsigned-bitfields \
	-fpack-struct \
	-fshort-enums \
	-ffunction-sections \
	-fdata-sections \
	$(INCLUDES)

# Cờ cho Linker
LDFLAGS = \
	-mmcu=$(MCU) \
	-B "$(PACK_DIR)/gcc/dev/$(MCU)" \
	-Wl,-Map="$(BUILD_DIR)/$(TARGET).map" \
	-Wl,--gc-sections \
	-lm

################################################################################
# Các Target trong Makefile
################################################################################

.PHONY: all clean hex size help

all: $(BUILD_DIR)/$(TARGET).elf hex size

# Quy tắc liên kết tạo file .elf
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo [LD] Linking target: $@
	@$(CC) $(LDFLAGS) -o $@ $^

# Quy tắc biên dịch từng file .c thành file .o
$(BUILD_DIR)/%.o: %.c
	@cmd /c if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo [CC] Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Tạo file .hex, .eep, .lss từ file .elf
hex: $(BUILD_DIR)/$(TARGET).elf
	@echo [HEX] Generating Intel HEX: $(BUILD_DIR)/$(TARGET).hex
	@$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "$<" "$(BUILD_DIR)/$(TARGET).hex"
	@echo [EEP] Generating EEPROM: $(BUILD_DIR)/$(TARGET).eep
	@$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "$<" "$(BUILD_DIR)/$(TARGET).eep" || exit 0
	@echo [LSS] Generating Assembly Listing: $(BUILD_DIR)/$(TARGET).lss
	@$(OBJDUMP) -h -S "$<" > "$(BUILD_DIR)/$(TARGET).lss"

# Hiển thị dung lượng bộ nhớ sử dụng
size: $(BUILD_DIR)/$(TARGET).elf
	@echo.
	@echo --- Memory Usage Statistics ---
	@$(SIZE) -C --mcu=$(MCU) "$<"
	@echo.

# Dọn dẹp thư mục build
clean:
	@echo Cleaning build artifacts...
	@cmd /c if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
	@echo Clean finished.

help:
	@echo ========================================================
	@echo Makefile targets:
	@echo   make all   : Bien dich toan bo du an, tao .elf va .hex
	@echo   make hex   : Tao file hex, eep va lss
	@echo   make size  : Kiem tra dung luong Flash va RAM
	@echo   make clean : Xoa sach thu muc build
	@echo ========================================================