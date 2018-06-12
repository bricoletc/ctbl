import pandas as pd
def integer_set(fi):
    with open(fi) as f:
        answer=f.readlines()

    lambdaf=lambda x:int(x.strip(),2)

    answer=set(map(lambdaf,answer))

    return answer

answer_file="answer.txt"
solution_file="simulated_solution.txt"

#answer=integer_set(answer_file)
solution=integer_set(solution_file)

taxo_index=pd.Series.from_csv("taxo_names.txt",sep="\t")

num_taxa=len(taxo_index.index)

taxo_index=taxo_index.sort_index()

new_index=[i.replace(".","") for i in taxo_index.index]

indices=pd.Series(range(num_taxa),index=taxo_index.index)
print(indices)

with open("answer_file_withTaxo.txt") as fii:
    for line in fii:
        if line[0]=="0" or line[0]=="1":
            int_set=line.strip()
        else:
            taxo=line.strip().split("\t")
            binAr=[0]*num_taxa 
            for tax in taxo:
                binAr[indices[tax.strip()]]=1
            print("{}\n{}".format(binAr,int_set))
