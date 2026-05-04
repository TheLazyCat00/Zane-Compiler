import sys, re

for line in sys.stdin:
	# Skip prettifying lines with [LOG ...] or [PRINT ...] prefixes
	if re.match(r'^\[(LOG|PRINT) ', line):
		print(line, end='')
	else:
		# For other lines (like ASan output), prettify all paths
		line = re.sub(r'([^\s]+/)+([^/\s/:]+)', r'\n          \2', line)
		line = re.sub(r'<.*>', '<>', line)
		print(line, end='')
