import sys, re

for line in sys.stdin:
	line = re.sub(r'([^\s]+/)+([^/\s/:]+)', r'\n          \2', line)
	line = re.sub(r'<.*>', '<>', line)
	print(line)
