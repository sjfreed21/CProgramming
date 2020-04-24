#! /bin/bash

run () {
  echo "$*"           # echo the command
  if $*               # execute it and test result
  then echo 'success'
  else echo 'error'
  fi
}

run ./atm < input.txt

exit 0
