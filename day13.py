import argparse
import numpy as np
import re
import matplotlib.pyplot as plt


def load_data(args):
    print("FILE: {}".format(args.file))
    with open(args.file, 'r') as fp:
        lines = fp.readlines()
#    print(lines)

    args.coords = []
    args.folds = []
    coords_re = re.compile('^([0-9]+),([0-9]+)')
    folds_re = re.compile('fold along ([xy])=([0-9]+)')

    for ln in lines:
        ln = ln.rstrip()
        match = coords_re.search(ln)
        if match:
            args.coords.append((int(match.group(1)), int(match.group(2))))
        match = folds_re.search(ln)
        if match:
            args.folds.append((match.group(1), int(match.group(2))))

    dmax = [0, 0]
    nc = 0
    for coord in args.coords:
        if coord[0] > dmax[0]:
            dmax[0] = coord[0]
        if coord[1] > dmax[1]:
            dmax[1] = coord[1]
        print(coord)
        nc += 1

    print("size {},{} ncoords:{}".format( dmax[0], dmax[1], nc))
    args.XX = dmax[0]+1
    args.YY = dmax[1]+1

    for fold in args.folds:
        print(fold)

def print_array(args):
    print("shape {} dots {}".format(args.a0.shape, np.count_nonzero(args.a0)))
    
    plt.matshow(args.a0)
    plt.show()
    return
    for yy in range(0, args.YY):
        pl = ""
        for xx in range(0, args.XX):
            #pl += str(args.a0[xx,yy])
            pl += "#" if args.a0[xx,yy] else "."
        print(pl)


def make_array(args):
    zz = np.zeros(args.XX*args.YY)
    args.a0 = np.reshape(zz, (args.XX, args.YY))
    for cd in args.coords:
        args.a0[cd[0],cd[1]] = 1

    print_array(args)

def make_fold(args, axis, line):
    axis_len = args.a0.shape[0 if axis == 'x' else 1] 
    line1 = axis_len - line
    
    if axis == 'x':
        print("make_fold({} {} {} {})".format(axis, axis_len, line, line1))
        
        if line1 > line:
            print("gt")     
            a0 = args.a0[:line,:]
            a1 = args.a0[line+1:,:]
        elif line < line1:
            print("lt")
            a0 = args.a0[:line-1,:]
            a1 = args.a0[line:,:]
        else:
            print("eq")
            a0 = args.a0[:line-1,:]
            a1 = args.a0[line+1:,:]
        a1 = np.flipud(a1)
        args.a0 = np.logical_or(a0, a1)        
        args.XX = line
    else:
        print("make_fold({} {} {} {})".format(axis, axis_len, line, line1)) 
        
        if line1 > line: 
            print("gt")
            a0 = args.a0[:,:line]
            a1 = args.a0[:,line+1:]    
        elif line1 < line:
            print("lt")  
            a0 = args.a0[:,:line-1]
            a1 = args.a0[:,line:] 
        else:
            print("eq")
            a0 = args.a0[:,:line-1]
            a1 = args.a0[:,line+1:]  
         
        #a1 = np.flipud(a1)
        a1 = np.fliplr(a1)
        args.a0 = np.logical_or(a0, a1)
        args.YY = line
      

def main():
    parser = argparse.ArgumentParser(description = "AoC 21 #13 folding")
    parser.add_argument('file', nargs=1, help="folding description")
    args = parser.parse_args()
    args.file = args.file[0]

    load_data(args)
    make_array(args)
    _len = len(args.folds)
    for fold in args.folds:
        _len = _len - 1
        print("make_fold {} {}".format(fold, _len))
        make_fold(args, fold[0], fold[1])
        print_array(args)

if __name__ == '__main__':
    main()

