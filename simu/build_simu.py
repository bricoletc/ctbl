import os
import pandas as pd 
import numpy as np

taxo_names="taxo_names.txt"
taxo_DB="131-combined_database_metadata.txt"

if not os.path.exists(taxo_names):
   df=pd.read_table(taxo_DB) 
   #df["Strain of origin"]=[str(i).replace(".","") for i in df["Strain of origin"]]
   taxa=df["Strain of origin"].astype(np.string_)
   f=lambda x: "_".join(x.decode().split()[:2])
   taxa=taxa.apply(f).astype(np.string_)
   counts=taxa.value_counts()
   top_199=counts[:199]
   top_199.to_csv(taxo_names,sep="\t")

else:
    top_199=pd.Series.from_csv(taxo_names,sep="\t")

top_199=top_199.sort_index()

###Now construct a DataFrame
num_taxa=len(top_199)
bitReps=[1<<i for i in range(num_taxa)] #Integer representation of the bitArray describing each individual (sorted) taxon.

dataStruct=pd.DataFrame({
    "Newick_rep":top_199.index,
    "bitRep":bitReps,
    "Original_taxon":top_199.index,
    })

allowed_samples=set(range(num_taxa))

true_bitArray=[]
Newick_construct=""

while len(allowed_samples)>1:
    
    sample1=np.random.choice(list(allowed_samples))
    allowed_samples.remove(sample1)
    sample2=np.random.choice(list(allowed_samples))
    
    Newick1,Newick2=dataStruct.loc[sample1,"Newick_rep"],dataStruct.loc[sample2,"Newick_rep"]
    combined_Newick="({},{})".format(Newick1,Newick2)
    
    bitRep1,bitRep2=dataStruct.loc[sample1,"bitRep"],dataStruct.loc[sample2,"bitRep"]
    combined_bitRep=bitRep1|bitRep2
    true_bitArray.append(bin(combined_bitRep)[2:])

    ##Replace the construct that can still be sampled with combined values
    dataStruct.loc[sample2,"Newick_rep"]=combined_Newick
    dataStruct.loc[sample2,"bitRep"]=combined_bitRep

#    print(combined_Newick)

#Remove the last bitArray which is all 1's
true_bitArray.pop()

last_sample=list(allowed_samples)[0]
final_Newick=dataStruct.loc[last_sample,"Newick_rep"]

with open("simulated_problem.txt","w") as f:
    f.write(final_Newick)

with open("simulated_solution.txt","w") as f:
    f.write("\n".join(true_bitArray))
