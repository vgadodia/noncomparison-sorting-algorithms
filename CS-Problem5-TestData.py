# Programming Language: Python 3.6.5
# Development Framework: Sublime Text
# Platform: Mac

# Instructions:
# Run the program and input the number of records you want generated

# Command I used on terminal to generate records into a file (I named the file "input"):
# python CS_Problem5-TestData.py > input
# (You must enter the number of records you want generated)

# I also tested my solution to problem 5 in other ways:
# I used terminal commands to sort the file with data in descending order by the criteria to produce unique test cases for my solution 
# The commands I used to accomplish this (The commands below assume there are 1000000 data items in file "input"):
# tail -1000000 input | sort -s -k1,1nr -k2,2nr -k3,3nr -k4,4nr -k5,5nr > input2

# Since the above commands will sort the file and print frequency, most frequent letter, and string,
# the follwing command will only copy the strings:
# tail -1000000 input| cut -d ' ' -f3 -f4 -f5 -f6 -f7 > input3

listofprimes = [
1000000000100011,
1011001110001111,
1090109110921093,
1111235916285193,
1181118711931201,
1235711131175321,
1238926361552897,
1301477951890177,
1311753223571113,
1311870831664661,
1333333333333333,
1391098979592919,
1510553619999637,
1593350922240001,
1616668118999191,
1680588011350901,
1693182318746371,
1737476797107127,
1867357583296451,
1889080110806881,
1989530586646177,
1990474529917009,
2035802523820057,
2067078579454279,
2222226095589337,
2345678911111111,
2355457523880889,
2380072466365871,
2468642135797531,
2744337540964913,
3129313031303131,
3325997869054417,
3391382115599173,
3931520917431241,
3940518300860411,
4444280714420857,
4564564564564561,
4847464544434241,
5944066965503999,
5953474341373129,
6171054912832631,
6241156164232441,
6435616333396997,
6664666366626661,
7897466719774591,
7897897897897897,
8008808808808813,
8690333381690951,
9007199254740847,
9007199254740881,
9293787934331213,
9949370777987917,
9999999900000001,
10000000002065383,
10112269203786181,
10234567876543201,
10269797835402631,
10939058860032031,
10968523783746901,
11018881818881011,
11333555557777777,
12348516587712457,
12962962592588887,
13107181911273173,
13173779397737131,
13311464115101051,
13457986268975431,
13661181333262459,
13666666666666613,
13666666666666631,
15125111011152151,
15795210542132999,
17000000000000071,
22222223333355757,
22439962446379651,
23456789101112123,
30000006160000003,
33832795028841971,
37033804397792473,
37124508045065437,
43142746595714191,
44444446666688899,
55350776431903243,
55453628211510631,
59604644783353249,
59649589127497217,
66555444443333333,
70000006660000007,
71117012721071117,
71828182828182817,
74747474747474747,
77777777977777777,
91521253335394951,
97654321012345679,
98765432101456789,
98823199699242779,
99194853094755497,
99999988898898889]
#print(len(listofprimes))

#for elem in listofprimes:
    #print(elem)

import random

n = int(input(""))
print(n)
ints = "123456789"
nums = "02468"

def is_Prime(num):
    if(num <= 1):
        return 0;
    elif(num <= 3):
        return 1;
    elif(num%2 == 0 or num%3 == 0):
        return 0;
    i = 5;
    while(i*i <= num):
        if(num%i==0 or num%(i+2) == 0):
            return 0;
        i = i + 6;
    return 1;

#print(is_Prime(77777777977777777))

#primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,47,97,101]
#regularnums = [4,6,8,9,10,12,14,15,16,18,20,21,22,24,25,26,27,28,29,30,32,33,34,35,36,38,39,40,42, 100000000, 10000000000, 1234567890, 9999999999999999, 124638761520, 1726783984764675, 1726783984764675, 1726783984764675, 1726783984764675, 1726783984764675, 1726783984764675, 1726783984764675]

for i in range(n):
    choice = random.randrange(1,6)
    first = str(listofprimes[random.randrange(0,90)])
    #first = str(primes[random.randrange(0,16)])
    second = str(random.randrange(1,9))
    for j in range(random.randrange(1,16)):
        second += str(nums[random.randrange(0,4)])
    third = str(random.randrange(1,9))
    for j in range(random.randrange(1,16)):
        third += str(nums[random.randrange(0,4)])
    fourth = str(random.randrange(1,9))
    for j in range(random.randrange(1,16)):
        fourth += str(nums[random.randrange(0,4)])
    fifth = str(random.randrange(1,9))
    for j in range(random.randrange(1,16)):
        fifth += str(nums[random.randrange(0,4)])
    if choice == 1:
        # Following line prints position, prime number, and then sequence of numbers --> This is to be used by the sorting command on terminal
        #print("0 " + str(first) + " " + str(first) + " " + second + " " + third + " " + fourth + " " + fifth)
        print(str(first) + " " + second + " " + third + " " + fourth + " " + fifth)
    elif choice == 2:
        # Following line prints position, prime number, and then sequence of numbers --> This is to be used by the sorting command on terminal
        #print("1 " + str(first) + " " + fifth + " " + str(first) + " " + second + " " + third + " " + fourth)
        print(fifth + " " + str(first) + " " + second + " " + third + " " + fourth)
    elif choice == 3:
        # Following line prints position, prime number, and then sequence of numbers --> This is to be used by the sorting command on terminal
        #print("2 " + str(first) + " " + fourth + " " + fifth + " " + str(first) + " " + second + " " + third)
        print(fourth + " " + fifth + " " + str(first) + " " + second + " " + third)
    elif choice == 4:
        # Following line prints position, prime number, and then sequence of numbers --> This is to be used by the sorting command on terminal
        #print("3 " + str(first) + " " + third + " " + fourth + " " + fifth + " " + str(first) + " " + second)
        print(third + " " + fourth + " " + fifth + " " + str(first) + " " + second)
    else:
        # Following line prints position, prime number, and then sequence of numbers --> This is to be used by the sorting command on terminal
        #print("4 " + str(first) + " " + second + " " + third + " " + fourth + " " + fifth + " " + str(first))
        print(second + " " + third + " " + fourth + " " + fifth + " " + str(first))



# Program with same position of prime numbers

# choice2 = random.randrange(1,6)
# for i in range(n):
#     first = str(listofprimes[random.randrange(0,90)])
#     #first = str(primes[random.randrange(0,16)])
#     second = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         second += str(nums[random.randrange(0,4)])
#     third = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         third += str(nums[random.randrange(0,4)])
#     fourth = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         fourth += str(nums[random.randrange(0,4)])
#     fifth = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         fifth += str(nums[random.randrange(0,4)])
#     if choice2 == 1:
#         print(str(first) + " " + second + " " + third + " " + fourth + " " + fifth)
#     elif choice2 == 2:
#         print(fifth + " " + str(first) + " " + second + " " + third + " " + fourth)
#     elif choice2 == 3:
#         print(fourth + " " + fifth + " " + str(first) + " " + second + " " + third)
#     elif choice2 == 4:
#         print(third + " " + fourth + " " + fifth + " " + str(first) + " " + second)
#     else:
#         print(second + " " + third + " " + fourth + " " + fifth + " " + str(first))


# Program for same position and value of prime number

# choice2 = random.randrange(1,6)
# prime = str(listofprimes[random.randrange(0,90)])
# for i in range(n):
#     #first = str(primes[random.randrange(0,16)])
#     second = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         second += str(nums[random.randrange(0,4)])
#     third = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         third += str(nums[random.randrange(0,4)])
#     fourth = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         fourth += str(nums[random.randrange(0,4)])
#     fifth = str(random.randrange(1,9))
#     for j in range(random.randrange(1,16)):
#         fifth += str(nums[random.randrange(0,4)])
#     if choice2 == 1:
#         print(str(prime) + " " + second + " " + third + " " + fourth + " " + fifth)
#     elif choice2 == 2:
#         print(fifth + " " + str(prime) + " " + second + " " + third + " " + fourth)
#     elif choice2 == 3:
#         print(fourth + " " + fifth + " " + str(prime) + " " + second + " " + third)
#     elif choice2 == 4:
#         print(third + " " + fourth + " " + fifth + " " + str(prime) + " " + second)
#     else:
#         print(second + " " + third + " " + fourth + " " + fifth + " " + str(prime))
