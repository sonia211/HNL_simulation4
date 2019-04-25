file = open('var_rank_output_2016_small.txt','r')

entr_dict = {}

for line in file:
    if "entropy" in line:
        
        line_list = line.split('{')
        var  = line_list[0]
        entr = line_list[1].split(',')[0].split(':')[1]
        cut  = line_list[1].split(',')[1].split(':')[1][:-2]
        #print var,entr,cut
        entr_dict[var]=entr

sort_list = sorted(entr_dict,key=entr_dict.__getitem__)
sort_vals = sorted(entr_dict.values())

for i in range(len(sort_list)):
    print sort_list[i],sort_vals[i]



    
