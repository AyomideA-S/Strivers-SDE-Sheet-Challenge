# Type: Python File


import os
import time
# parse arguments
import argparse
from colorama import init, Fore, Style

RED = '\033[91m' # or '\033[31m'
GREEN = '\033[92m' # or '\033[32m'

# Edit this line to test the variations of the function
# from ... import ... # This is the function you want to test

# initialize colorama
init()

parser = argparse.ArgumentParser()

group = parser.add_mutually_exclusive_group(required=False)
group.add_argument('-v', '--verbose', help='Prints output to stdout', action='store_true', default=True)
group.add_argument('-q', '--quiet', help='Silent mode (does not print output)', action='store_true')

parser.add_argument('input', nargs='?', help='Input file', default=None)
parser.add_argument('-V', '--validate', help='Validate output', action='store_true', default=False)
parser.add_argument('-s', '--solution', help='Solution file', nargs='?', default=None)
parser.add_argument('-t', '--time', help='Calculate execution time', action='store_true', default=False)
parser.add_argument('-a', '--all', help='Run all test cases', action='store_true', default=False)
parser.add_argument('-o', '--output', help='Output file', nargs='?', default=None)

# function to calculate the time taken by the function
def calculate_time(matrix, n, m):
	global exec_time
	global start_time
	global end_time

	start_time = time.time()
	matrix = zeroMatrix(matrix, n, m)
	end_time = time.time()

	exec_time = end_time - start_time
	return exec_time

# the main execution of the program
if __name__ == '__main__':
	args = parser.parse_args()
	if args.validate and not args.solution:
		parser.error('The --solution argument is required when using --validate')

	# if you want to try a specific test case
	if args.input:
		with open(args.input) as file:
	#         if args.quiet:
	#             if args.output:
	#         elif args.verbose:
	#             if args.output:
	#         file.close()
		# if you want to validate your output
		# if args.validate:
		#     with open(args.solution) as file:
		#         if output == solution:
					# make the colour green
					# print('\033[92m' + 'Test Case(s) Passed' + '\033[0m')
					# print('\033[32m' + 'Test Case(s) Passed' + '\033[0m')
					# print(f'{Fore.GREEN}Test Case(s) Passed{Style.RESET_ALL}')
				# else:
					# make the colour red
					# print('\033[91m' + 'Test Case(s) Failed' + '\033[0m')
					# print('\033[31m' + 'Test Case(s) Failed' + '\033[0m')
					# print(f'{Fore.RED}Test Case(s) Passed{Style.RESET_ALL}')
				file.close()
	elif args.all:
		files = os.listdir('in/')
		# get list of files in the input directory
		for i in range(1, len(files)+1):
			path = f'in/input{str(i)}.txt'
			with open(path) as file:
				# if args.quiet:
					# if args.output:
				# elif args.verbose:
					# print(f'Test Case: {i}')
					# if args.output:
				file.close()
	else:
		parser.error('An input file is required else use the -a/--all argument.')

	if args.time:
		print(f'Core Function Execution Time: {exec_time:.6f} seconds')

	exit(0)
