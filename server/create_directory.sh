# Directory
DIRECTORY=(log_authentication)
# Check if the directory exists
if [ ! -d "$DIRECTORY" ]; then
	# Creates
	mkdir log_authentication
fi