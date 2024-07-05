INPUT_FILE = 'mac-prefixes'
OUTPUT_FILE = 'src/macprefixes.h'
MANUFACTURERS = [
    'Routerboard.com',
    'TP-Link',
    'D-Link',
    'Ubiquiti',
    'Intelbras',
    'Huawei',
    'Google',
    'Asus',
    'ASUSTek',
    'Mercury',
    'Mercusys',
]


def read_mac_file(file_path: str) -> tuple[list, int, int]:
    mac_data = []
    max_prefix_len = 0
    max_manufacturer_len = 0

    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if line and not line.startswith('#'):
                prefix, manufacturer = line.split(maxsplit=1)
                manufacturer = manufacturer.split()[
                    0
                ]  # Take only the first word of the manufacturer's name

                if manufacturer in MANUFACTURERS:
                    mac_data.append((prefix, manufacturer))

                    max_prefix_len = max(max_prefix_len, len(prefix))
                    max_manufacturer_len = max(
                        max_manufacturer_len, len(manufacturer)
                    )

    return mac_data, max_prefix_len, max_manufacturer_len


def generate_cpp_code(
    mac_data: list, selected_manufacturers: list, max_manufacturer_len: int
) -> str:
    filtered_data = [
        entry for entry in mac_data if entry[1] in selected_manufacturers
    ]
    filtered_data.sort()

    # Split data into blocks of up to 250 items
    chunks = [
        filtered_data[i : i + 200] for i in range(0, len(filtered_data), 250)
    ]

    struct_def = (
        f'struct MacEntry {{\n'
        f'    char prefix[11];\n'
        f'    char manufacturer[{max_manufacturer_len + 1}];\n'  # +1 for the null character
        f'}};\n\n'
    )

    array_defs = ''
    for idx, chunk in enumerate(chunks):
        array_init = f'MacEntry mac_entries_{idx}[] = {{\n'
        for prefix, manufacturer in chunk:
            array_init += f'    {{"{prefix}", "{manufacturer}"}},\n'
        array_init = array_init.rstrip(',\n') + '\n};\n'
        array_defs += array_init + '\n'

    func_def = (
        '\n'
        'String findManufacturer(String mac_address) {\n'
        '    mac_address.replace(":", "");\n'
        '    MacEntry* mac_arrays[] = {'
    )

    for idx in range(len(chunks)):
        func_def += f'mac_entries_{idx}, '

    func_def = func_def.rstrip(', ') + '};\n'

    func_def += '    size_t array_sizes[] = {'

    for chunk in chunks:
        func_def += f'{len(chunk)}, '

    func_def = func_def.rstrip(', ') + '};\n'

    func_def += (
        '    for (size_t array_idx = 0; array_idx < sizeof(mac_arrays) / sizeof(mac_arrays[0]); ++array_idx) {\n'
        '        MacEntry* entries = mac_arrays[array_idx];\n'
        '        size_t size = array_sizes[array_idx];\n'
        '        int low = 0;\n'
        '        int high = size - 1;\n'
        '        while (low <= high) {\n'
        '            int mid = (low + high) / 2;\n'
        '            int cmp = mac_address.substring(0, 6).compareTo(entries[mid].prefix);\n'
        '            if (cmp == 0) {\n'
        '                return String(entries[mid].manufacturer);\n'
        '            } else if (cmp > 0) {\n'
        '                low = mid + 1;\n'
        '            } else {\n'
        '                high = mid - 1;\n'
        '            }\n'
        '        }\n'
        '    }\n'
        '    return String("Unknown");\n'
        '}\n'
    )

    return struct_def + array_defs + func_def


def write_cpp_file(output_path, cpp_code):
    with open(output_path, 'w', encoding='utf-8') as file:
        file.write(cpp_code)


def main():
    mac_data, max_prefix_len, max_manufacturer_len = read_mac_file(INPUT_FILE)
    cpp_code = generate_cpp_code(mac_data, MANUFACTURERS, max_manufacturer_len)
    write_cpp_file(OUTPUT_FILE, cpp_code)
    print(f'C++ code generated in {OUTPUT_FILE}')
    print(f'Max prefix length: {max_prefix_len}')
    print(f'Max manufacturer length: {max_manufacturer_len}')


if __name__ == '__main__':
    main()
