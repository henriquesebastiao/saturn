import argparse

def process_file(input_file):
    output_file = "dev/output.txt"
    
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            numbers = line.strip().split()
            for number in numbers:
                outfile.write(f"{number},\n")
    
    print(f"O texto formatado foi gravado em {output_file}")

def main():
    parser = argparse.ArgumentParser(description="Processa um arquivo de texto e formata os números.")
    parser.add_argument('-f', '--file', type=str, required=True, help="Nome do arquivo de entrada")

    args = parser.parse_args()

    process_file(args.file)

if __name__ == "__main__":
    main()
