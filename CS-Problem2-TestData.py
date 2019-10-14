# Programming Language: Python 3.6.5
# Development Framework: Sublime Text
# Platform: Mac

# Instructions:
# Run the program and input the number of records you want generated

# Command I used on terminal to generate records into a file (I named the file "input"):
# python CS-Problem2-TestData.py > input
# (You must enter the number of records you want generated)

# I also tested my solution to problem 2 in other ways:
# I used terminal commands to sort the file with data in ascending/descending order by GPA/Graduation year to produce unique test cases for my solution 
# The commands I used to accomplish this (The commands below assume there are 1000000 data items in file "input"):
# tail -1000000 input | awk '{printf("%s\t%s\t%s\n",$NF,$(NF-1),$0);}' | sort -s -k1,1n -k2,2n | cut -f3 > input2 
# tail -1000000 input | awk '{printf("%s\t%s\t%s\n",$NF,$(NF-1),$0);}' | sort -s -k1,1nr -k2,2n | cut -f3 > input2
# tail -1000000 input | awk '{printf("%s\t%s\t%s\n",$NF,$(NF-1),$0);}' | sort -s -k1,1n -k2,2nr | cut -f3 > input2
# tail -1000000 input | awk '{printf("%s\t%s\t%s\n",$NF,$(NF-1),$0);}' | sort -s -k1,1nr -k2,2nr | cut -f3 > input2

import random
letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'- "

n = int(input(""))
print(n)

for i in range(n):
	# Makes a randomized lastname
    lastname = ""
    for j in range(random.randrange(1,31)):
        lastname += random.choice(letters)
    
    # Makes a randomized firstname
    firstname = ""
    for k in range(random.randrange(1,31)):
        firstname += random.choice(letters)

    # Makes a random GPA
    gpa = round(random.uniform(0.01, 3.99), 2)
    
    # Makes a random graduation year
    gradyear = random.randrange(2018, 2023)
    print(lastname +", "+ firstname + " " + str("%.2f" % gpa) + " " + str(gradyear))

# The code below generates a test case that contains records with the same GPA

# gpa2 = round(random.uniform(0.01, 3.99), 2)
# for i in range(n):
#     lastname = ""
#     for j in range(random.randrange(1,31)):
#         lastname += random.choice(letters)
#     firstname = ""
#     for k in range(random.randrange(1,31)):
#         firstname += random.choice(letters)
#     gradyear = random.randrange(2018, 2023)
#     print(lastname +", "+ firstname + " " + str("%.2f" % gpa2) + " " + str(gradyear))


# The code below generates a test case that contains records with the same graduation year

# gradyear2 = random.randrange(2018, 2023)
# for i in range(n):
#     lastname = ""
#     for j in range(random.randrange(1,31)):
#         lastname += random.choice(letters)
#     firstname = ""
#     for k in range(random.randrange(1,31)):
#         firstname += random.choice(letters)
#     gpa = round(random.uniform(0.01, 3.99), 2)
#     print(lastname +", "+ firstname + " " + str("%.2f" % gpa) + " " + str(gradyear2))

