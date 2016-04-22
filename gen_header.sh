
if [ ! -n $1 ]
then
    echo "usage: bash $0 filename"
    exit 0
fi

name=$1
name_word=${name%.h}
file_name=${name_word}.h
macro_key=_$(echo ${name_word} | tr '[a-z]' '[A-Z]')_H

echo "gen $file_name ..."

cat >$file_name <<EOF
#ifndef ${macro_key}
#define ${macro_key}

#endif

/* end of file $file_name */
EOF

echo "done"

