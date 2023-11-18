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

FILES=$(find ../assets -type f -name "*.png" )

for filename in $FILES; do
    IN=$(realpath -m $filename) # png path
	OUT=$(realpath -m $(echo $filename | sed s,/assets/png/,/assets/,g | sed s,.png,.xpm,g)) # converts png path to xpm path
	mkdir -p $(dirname $OUT)
    python3 -m xpm $IN > $OUT
done