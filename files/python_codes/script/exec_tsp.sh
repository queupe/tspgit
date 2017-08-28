#!/bin/bash
config_names='sh_names.txt'
names_lines=`cat $config_names`
echo Start
for line in $names_lines ; do
    echo -e './tsp' $line 'teste'
done
