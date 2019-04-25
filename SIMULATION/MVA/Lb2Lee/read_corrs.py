file_sig = open('corrs_signal_2016_JpsiLee.txt','r')
file_bkg = open('corrs_bkg_2016_JpsiLee.txt','r')

entr_dict = {}

n = 0
for file in [file_sig,file_bkg]:
    n += 1
    print n
    for line in file:        
        list = line.split(" ")
        #print list[3],list[4],list[5]
        if n == 1: start = "SIGNAL: "
        elif n == 2: start = "BKGRND: "
        if not start+list[4]+" vs. "+list[3] in entr_dict:
            entr_dict[start+list[3]+" vs. "+list[4]] = list[5][:-2]

sort_list = sorted(entr_dict,key=entr_dict.__getitem__)
sort_vals = sorted(entr_dict.values())

for i in range(len(sort_list)):
    print sort_list[i],sort_vals[i]
