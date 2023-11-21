# Converts all PNG images inside assets/** into XPM files
# using:
# python xpm saver 0.3.0
# python Pillow

if [[ "$@" =~ '--help' ]]
then
	(echo -e "Asset refresh:
	./refresh.sh [-hu]

	Converts all PNG files found in ../assets/source to XPM files in ../assets

	Dependencies: (auto fetcjed)
		Python3.8+
		pip3
		Python.PIL: pip install Pillow
		XPM: pip install git+https://github.com/gmfCoding/xpm_argb.git@master
		 ^ This is a fork of PyPI:xpm that supports more features

	--help
		displays this help message.

	-u --update
		Updates the python xpm module (no automatic way)
	")
	exit;
fi

UPDATE=0
while [[ $#>0 ]]; do
	case "$1" in 
		'-u'|'--update')
			UPDATE=1
			shift 1
			continue
	esac
	break
done

python3 -c "import PIL"
if [[ $? -ne 0 ]]; then
	pip3 install Pillow
fi

if [[ $? -ne 0 ]] | [[ $UPDATE == 1 ]]; then
	pip3 install git+https://github.com/gmfCoding/xpm_argb.git@master
fi

OWD=$(pwd)
cd $(cd $(dirname $0); pwd -P)

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