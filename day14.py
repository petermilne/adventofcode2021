''' day14 '''

import argparse

import re

def load_data(args):
    print("FILE: {}".format(args.file))
    with open(args.file, 'r') as fp:
        lines = fp.readlines()
        
    args.seed = ""
    args.rules = {}
    rules_re = re.compile('^([A-Z][A-Z]) -> ([A-Z])')
    
    for ln in lines:
        ln = ln.rstrip()
        if len(ln)  < 1:
            continue
        if len(args.seed) == 0:
            args.seed = ln
        else:
            match = rules_re.search(ln)
            if match:
                args.rules[match.group(1)] = match.group(2)
            else:
                print("error no match {}". format(ln))
                
    print("seed: {}".format(args.seed))
    print("rules: {}".format(args.rules))
    
def expand(args):
    str0 = args.seed
    str1 = ""
    for ii in range(0,len(str0)-1):
        str1 += str0[ii]
        str1 += args.rules[str0[ii:ii+2]]
       
    str1 += str0[ii+1]
    args.seed = str1
    
def main():
    parser = argparse.ArgumentParser(description = "AoC 21 #14 expansion")
    parser.add_argument('--steps', default=1, type=int)
    parser.add_argument('file', nargs=1, help="datafile description")
    args = parser.parse_args()
    args.file = args.file[0]

    load_data(args)
    for step in range(1, args.steps):
        expand(args)
        print("step:{} length:{}  value:{}".format(step, len(args.seed), args.seed[0:10]))
        
        
    hg = {}
    for cc in args.seed:
        if cc not in hg:
            hg[cc] = 1
        else:
            hg[cc] += 1
        
    print(hg)
    fmin = 999999999999
    fmax = 0
    for cc in hg:
        if hg[cc] < fmin:
            fmin = hg[cc]
        if hg[cc] > fmax:
            fmax = hg[cc]
            
    print("fmin {} fmax {} diff {}".format(fmin, fmax, fmax-fmin))
        
    

if __name__ == '__main__':
    main()
