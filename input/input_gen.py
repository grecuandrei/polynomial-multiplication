import numpy as np
import sys

def main(argv):
    if len(argv) <= 3:
        print("Usage: python3 input_gen.py no_coef_1 no_coef_2 size_high")
        return

    gen_file(argv)

def gen_file(argv):

    file_name = "input_" + argv[1] + "_" + argv[2] + ".in"
    f = open(file_name, "w")
    f.write(argv[1])
    f.write("\n")

    coef_1 = np.random.randint(low=-(int(argv[3])/2), high=(int(argv[3])/2), size=int(argv[1]))
    for i in coef_1:
        f.write(str(i))
        f.write(" ")

    f.write("\n")
    f.write(argv[2])
    f.write("\n")

    coef_2 = np.random.randint(low=-(int(argv[3])/2), high=(int(argv[3])/2), size=int(argv[2]))
    for i in coef_2:
        f.write(str(i))
        f.write(" ")

    f.write("\n")
    f.write(str(np.random.randint(0, int(argv[3]))))
    f.close()

if __name__ == "__main__":
   main(sys.argv)