#!/usr/bin/env python
# coding=utf-8
import os
#import datetime
import time
import sys

def test(algo, testsetid):
    fullname = {'dn':'Dinic','ek':'Edmonds-Karp','pr':'Push-Relabel'}
    x = 9
    if testsetid == "2":
        x = 12
    oldtime=time.time()
    for i in range(1,x):
        file_name = "data"+testsetid+"/"+str(i)+'.in'
        file_ans = "data"+testsetid+"/"+str(i)+'.out'
        
        command_exec = "./"+ algo +" < " + file_name + " > output.out"
        os.system(command_exec)
        fr = open(file_ans,'r')
        ans = fr.read().strip()
        myfr = open('output.out','r')
        myans = myfr.read().strip()
        assert(ans == myans)
        fr.close();
        myfr.close();
        print("Test"+str(i)+" passed.")
        os.system("rm output.out")
    newtime = time.time()
    print("Elapsed time of",fullname[algo]+":",format(newtime-oldtime, '.3f'),"seconds.")

if __name__ == "__main__":
    test(sys.argv[1], sys.argv[2])


