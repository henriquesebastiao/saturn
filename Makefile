PORT := /dev/ttyACM0

html-lint:
	prettier --write portals/*.html

upload:
	arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./saturn.ino && arduino-cli upload --port $(PORT) --fqbn m5stack:esp32:m5stack_cardputer

compile:
	arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./saturn.ino && esptool.py --chip esp32s3 merge_bin --output build/m5stack.esp32.m5stack_cardputer/saturn.bin 0x0000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bootloader.bin 0x8000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.partitions.bin 0x10000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bin

merge:
	esptool.py --chip esp32s3 merge_bin --output build/m5stack.esp32.m5stack_cardputer/saturn.bin 0x0000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bootloader.bin 0x8000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.partitions.bin 0x10000 build/m5stack.esp32.m5stack_cardputer/saturn.ino.bin

monitor:
	arduino-cli monitor --port $(PORT)

format:
	clang-format -i --style=google src/*.h && blue .

format-raw:
	python scripts/format_raw.py -f dev/input.txt

format-pronto:
	python scripts/format_pronto.py -f dev/input.txt

format-ir:
	./scripts/format_ir.sh

black:
	black .

lint:
	cppcheck --check-level=exhaustive --error-exitcode=1 --force --language=c++ src/*.h && blue --check . --diff && ruff check .

mac-prefixes:
	rm mac-prefixes && wget https://raw.githubusercontent.com/nmap/nmap/master/nmap-mac-prefixes && mv nmap-mac-prefixes mac-prefixes && rm src/macprefixes.h && python scripts/generate_mac_file.py && clang-format -i --style=google src/macprefixes.h

.PHONY: html-lint
.PHONY: upload
.PHONY: compile
.PHONY: merge
.PHONY: monitor
.PHONY: format
.PHONY: format-raw
.PHONY: format-pronto
.PHONY: format-ir
.PHONY: black
.PHONY: lint
.PHONY: mac-prefixes