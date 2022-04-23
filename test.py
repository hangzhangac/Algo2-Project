#!/usr/bin/env python
# coding=utf-8
import os
import datetime
import sys

def test(algo):
    oldtime=datetime.datetime.now()
    for i in range(1,9):
        file_name = "data/"+str(i)+'.in'
        file_ans = "data/"+str(i)+'.out'
        
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
    newtime = datetime.datetime.now()
    print("Elapsed time:",(newtime-oldtime).microseconds/1000,"ms.")

if __name__ == "__main__":
    test(sys.argv[1])


