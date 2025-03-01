'''
@file generate-random-data.py
@author Omegaki113r
@date Saturday, 1st March 2025 9:37:52 pm
@copyright Copyright 2025 - 2025 0m3g4ki113r, Xtronic
*//*
Project: test-scripts
File Name: generate-random-data.py
File Created: Saturday, 1st March 2025 9:37:52 pm
Author: Omegaki113r (omegaki113r@gmail.com)
-----
Last Modified: Sunday, 2nd March 2025 12:52:41 am
Modified By: Omegaki113r (omegaki113r@gmail.com)
-----
Copyright 2025 - 2025 0m3g4ki113r, Xtronic
-----
HISTORY:
Date      	By	Comments
----------	---	---------------------------------------------------------
'''
import random
import string

# Function to generate random text
def generate_random_text(length=1000):
    # Generate a random string of uppercase and lowercase letters
    return ''.join(random.choices(string.ascii_letters + string.digits + string.punctuation + " ", k=length))

# Function to generate a large set of random text data
def generate_random_text_data(num_entries=4000, length_per_entry=1000):
    data = []
    
    for _ in range(num_entries):
        random_text = generate_random_text(length_per_entry)
        data.append(random_text)
    
    return data

# Generate 1500 entries of random text, each of length 1000 characters
random_text_data = generate_random_text_data(4000, 1000)

# Save to a file
with open("random_text_data.txt", "w") as file:
    for entry in random_text_data:
        file.write(entry + "\n")

print("random_text_data.txt file created with 4000 random text entries.")
