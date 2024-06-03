html-lint:
	prettier --write portals/*.html

upload:
	arduino-cli upload --port /dev/ttyACM0 --fqbn m5stack:esp32:m5stack_cardputer

compile:
	arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./saturn.ino && esptool.py --chip esp32s3 merge_bin --output build/m5stack.esp32.m5stack_cardputer/saturn.bin 0x0000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bootloader.bin 0x8000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.partitions.bin 0x10000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bin

merge:
	esptool.py --chip esp32s3 merge_bin --output build/m5stack.esp32.m5stack_cardputer/saturn.bin 0x0000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bootloader.bin 0x8000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.partitions.bin 0x10000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bin

.PHONY: html-lint
.PHONY: upload
.PHONY: compile
.PHONY: merge