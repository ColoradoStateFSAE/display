#!/bin/bash

clear
set -e

# Define the new download directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DBC_DIR="$SCRIPT_DIR/src/dbc"

# Ensure the dbc directory exists
mkdir -p "$DBC_DIR"

echo "UPDATING DBC FILES"

# Get all the URLs of the release files
URLS=$(wget -qO- https://api.github.com/repos/ColoradoStateFSAE/dbc/releases/latest | grep "browser_download_url" | cut -d '"' -f 4)

# Loop over each URL and download the corresponding file
for URL in $URLS; do
    echo "Downloading: $URL"
    wget --show-progress -q "$URL" -O "$DBC_DIR/$(basename "$URL")"
done

# Remove existing files that have the same name as the new downloads (if needed)
for URL in $URLS; do
    FILE_NAME=$(basename "$URL")
    rm -f "$DBC_DIR/$FILE_NAME"
done

echo "DBC DOWNLOAD COMPLETE"

# Ensure the build directory exists
mkdir -p build

# Run QMake and Make
/opt/qt5/bin/qmake -makefile display.pro
make -s -j$(nproc)

# Change into the build directory and strip the binary
cd build
/opt/buildroot/output/host/arm-buildroot-linux-gnueabihf/bin/strip display

echo "BUILD COMPLETE"
echo "UPLOADING TO DISPLAY... (ctrl+c to cancel)"

# If the display binary exists, transfer and execute it
if test -e display; then
    rsync -Ph -e "ssh -i ~/.ssh/qtc_id" -avz display root@192.168.1.1:/root
    clear
    ssh -i ~/.ssh/qtc_id root@192.168.1.1 \
        "killall -9 display || true &&
        killall -9 /root/display || true &&
        clear &&
        /root/display;"
fi