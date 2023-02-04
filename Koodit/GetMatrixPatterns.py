#import numpy
import os

MAXNUMBER = 256

#with open("MatrixThings.txt","w") as file:

for x in range(MAXNUMBER):
    
    a = f"{x:08b}"
    print(f"{a[7]} {a[6]} {a[5]}\n{a[4]}   {a[3]}\n{a[2]} {a[1]} {a[0]}\n")
    sus = input(" ")
        #file.write(" ".join(str(a))+"\n\n")
    
    
    #file.close()   


#for looppii ja käytä sitä miten koneet muodostaa numeroita ykkösistä ja nollista eri ratkaisuihin
