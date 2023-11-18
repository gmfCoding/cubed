# Converts all PNG images inside assets/** into XPM files
# using:
# python xpm saver 0.3.0
# python Pillow

python3 -c "import PIL"
if [[ $? -ne 0 ]]; then
	pip3 install Pillow
fi

python3 -c "import xpm"
if [[ $? -ne 0 ]]; then
	pip3 install xpm
fi

OWD=$(pwd)
cd $(dirname $(realpath $0))

BGREEN="\033[1;32m"
GREEN="\033[0;32m"
BRED="\033[1;31m"
RED="\033[0;31m"
BYELLOW="\033[1;33m"
YELLOW="\033[0;33m"
BBLUE="\033[1;34m"
BLUE="\033[0;34m"
BCYAN="\033[1;36m"
CYAN="\033[0;36m"
NC="\033[0m"

FILES=$(find ../assets/source/ -type f -name "*.png" )
for filename in $FILES; do
    IN=$(realpath -m $filename) # png path
	OUT=$(realpath -m $(echo $filename | sed s,/assets/source/,/assets/,g | sed s,.png,.xpm,g)) # converts png path to xpm path
	mkdir -p $(dirname $OUT)
	printf ""$GREEN"converting $BLUE$IN$NC to$RED $OUT\n$NC"
    python3 -m xpm $IN > $OUT
done

cd $OWD

# TODO automatic asset pipeline refresh?
# BLENDER=/mnt/c/Program Files/Blender Foundation/Blender 3.6/blender-launcher.exe
# $BLENDER -b assets/source/models/cube.blend -x 1 -o //render -f 0 # automatically rerender blend file