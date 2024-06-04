# Saturn

Saturn aims to be a simple and functional firmware that implements several functionalities for vulnerability analysis and even simple day-to-day tasks that can be performed with an ESP32.

## How to install

### Compile it yourself (with Arduino CLI)

- Install Arduino CLI
- Add M5Stack Index to Arduino Core
- Add M5Stack Libraries

```bash
# Install m5stack boards
arduino-cli core install m5stack:esp32  --additional-urls https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json --log-level warn --verbose

# Install required library
arduino-cli lib install M5Cardputer --log-level warn --verbose

# Compile
arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./saturn.ino
```

- This will create multiple binaries based on partition sketch, you can merge a single binary using `esptool`
- Install esptool `pip install -U esptool`

```bash
esptool.py --chip esp32s3 merge_bin --output final.bin 0x0000 m5stick-nemo.ino.bootloader.bin 0x8000 m5stick-nemo.ino.partitions.bin 0x10000 m5stick-nemo.ino.bin
```

- You can now flash the merged binary firmware using `esptool`

```bash
esptool.exe write_flash -z 0 final.bin
```

## Disclaimer

The functionalities present in this firmware are for educational purposes only, being tested only in controlled and isolated environments. The maintainers are not responsible for any misuse of this tool.