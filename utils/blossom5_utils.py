import os
import argparse

def preprocess_snap(fp):
    main_directory = os.path.dirname(fp)
    os.chdir(main_directory)
    new_fp = fp + ".blossomv.preprocessed"
    with open(fp, 'r') as f:
        with open(new_fp, 'w') as nf:
            n, m = [int(x) for x in f.readline().rstrip().split()]
            print(n, m)
            nf.write(f"{2*n} {n+m}\n")
            for line in f.readlines():
                e0, e1 = [int(x) for x in line.rstrip().split()]
                nf.write(f"{e0} {e1} -1\n")
            for i in range(n):
                nf.write(f"{i} {i+n} 0\n")

def validate_file(filename):
    if not os.path.exists(filename):
        raise argparse.ArgumentTypeError("{0} does not exist".format(filename))
    return filename


def main():
    parser = argparse.ArgumentParser(description="Process arguments for blossomV utils")
    
    parser.add_argument("-i", "--input", dest="filename", type=validate_file, required=True, help="enter graph file", metavar="FILE")

    args = parser.parse_args()
    print(args.filename)

    preprocess_snap(args.filename)

if __name__ == '__main__':
    main()