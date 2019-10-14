# Programming Language: Python 3.6.5
# Development Framework: Sublime Text
# Platform: Mac

# Instructions:
# Run the program and input the number of records you want generated

# Command I used on terminal to generate records into a file (I named the file "input"):
# python CS-Problem4-TestData.py > input
# (You must enter the number of records you want generated)

# I also tested my solution to problem 4 in other ways:
# I used terminal commands to sort the file with data in ascending/descending order by most frequent letter and its frequency to produce unique test cases for my solution 
# The commands I used to accomplish this (The commands below assume there are 1000000 data items in file "input"):
# The following commands are only used to sort a file with frequency, most frequent letter, and string
# tail -1000000 input | sort -s -k1,1n -k2,2 -k3,3 > input2
# tail -1000000 input | sort -s -k1,1n -k2,2r -k3,3 > input2
# tail -1000000 input | sort -s -k1,1n -k2,2 -k3,3r > input2
# tail -1000000 input | sort -s -k1,1n -k2,2r -k3,3r > input2
# tail -1000000 input | sort -s -k1,1nr -k2,2r -k3,3 > input2
# tail -1000000 input | sort -s -k1,1nr -k2,2 -k3,3r > input2
# tail -1000000 input | sort -s -k1,1nr -k2,2r -k3,3r > input2

# Since the input data will still have the frequency and most frequent letter, the following command only copies the strings
# tail -1000000 input2| cut -d ' ' -f3 > input3
# Then I added 1000000 manually on the first line of input3


n = int(input(""))
print(n)
#print(n*40)
lets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

import random

for i in range(n):
 	word = ""
 	for j in range(random.randrange(1,41)):
 		word += lets[random.randrange(0,25)]
 	temp = ''.join(sorted(word))
 	max = 0
 	maxlet = ""
 	for k in range(len(temp)):
 		if temp.count(temp[k]) > max:
 			max = temp.count(temp[k])
 			maxlet = temp[k]
 	# The following line prints frequency, most frequent letter, and string in order to be sorted by using a terminal command
 	#print(str(max) + " " + str(maxlet) + " " + str(word))
 	print(str(word))



# Some other test cases I came up with to further test my code

# for i in range(n):
# 	word = ""
# 	for j in range(40):
# 		word = ((lets[random.randrange(0,25)]*j)+lets[random.randrange(0,25)])
# 		temp = ''.join(sorted(word))
# 		max = 0
# 		maxlet = ""
# 		for k in range(len(temp)):
# 			if temp.count(temp[k]) > max:
# 				max = temp.count(temp[k])
# 				maxlet = temp[k]
# 		The following line prints frequency, most frequent letter, and string in order to be sorted by using a terminal command
# 		print(str(max) + " " + str(maxlet) + " " + str(word))
#		print(str(word))

# for i in range(n):
# 	word2 = lets[random.randrange(0,25)]
# 	for j in range(1, 41):
# 		word = word2*j
# 		temp = ''.join(sorted(word))
# 		max = 0
# 		maxlet = ""
# 		for k in range(len(temp)):
# 			if temp.count(temp[k]) > max:
# 				max = temp.count(temp[k])
# 				maxlet = temp[k]
# 		The following line prints frequency, most frequent letter, and string in order to be sorted by using a terminal command
# 		print(str(max) + " " + str(maxlet) + " " + str(word))
#		print(str(word))




