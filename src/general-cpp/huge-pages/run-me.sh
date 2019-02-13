#!/bin/sh

shm_key=124	# the shared-memory key used in the code, so don't change this

# remove the shared key in case the program didn't do it normally at the end
sudo ipcrm -M $shm_key 1>/dev/null 2>/dev/null

# run the code
./testshm.exec "$@"