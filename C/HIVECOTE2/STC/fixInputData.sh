#/bin/dash!

# Check if a filename is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

# Use sed to remove 'array[' from the specified file
sed -i 's/array(//g' $1
sed -i 's/\])/}/g' $1
sed -i 's/\]/}/g' $1
sed -i 's/\[/\{/g' $1
sed -i "s/np.str_('1')/'1'/g" $1
sed -i "s/np.str_('2')/'2'/g" $1
sed -i 's/)/}/g' $1
sed -i 's/(/\{/g' $1
