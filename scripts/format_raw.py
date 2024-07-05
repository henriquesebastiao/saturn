import argparse


def process_file(input_file):
    output_file = 'dev/output.txt'

    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            numbers = line.strip().split()
            for number in numbers:
                outfile.write(f'{number},\n')

    print(f'The formatted text was written to {output_file}')


def main():
    parser = argparse.ArgumentParser(
        description='Processes a text file and formats the numbers.'
    )
    parser.add_argument(
        '-f', '--file', type=str, required=True, help='Input file name'
    )

    args = parser.parse_args()

    process_file(args.file)


if __name__ == '__main__':
    main()
