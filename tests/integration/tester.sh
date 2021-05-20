#!/bin/bash

MYSHELL="$PWD/../../42sh"
REFER="/bin/tcsh -f"

# Undefines any previously defined bash function
for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
  f=`echo $i | /usr/bin/sed s/BASH_FUNC_//g | /usr/bin/sed s/%%//g`
  unset -f $f
done

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

# Gets the value of string properties with the first argument as names
get_string_property() {
  $SED -ne "s/^$1\s*=\s*\(.*\)\s*$/\1/p" | $SED -e "s/^\(\"\(.*\)\"\)\|\('\(.*\)'\)$/\2\4/"
}

# Displays the data of the test $id
display_test()
{
  id=$1
  $CAT test_basic.toml | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script() {
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test() {
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

# Parameters:
# 1 - test file contents
# 2 - test suite
# 3 - test id
# 4 - debug value
run_test() {
  local test_file=$1
  local suite=$2
  local id=$3
  local debug=$4

  local properties=`echo "$test_file" | $SED -ne  "/^\[$id\]\$/,/^\[.*\]$/{/^\[.*\]$/d;p}"`

  # extract 'tests' multiline property first...
  TESTS=`echo "$properties" | $SED -ne '/^tests\s*=\s*"""$/,/^"""$/{/^tests\s*=\s*"""$/d;/^"""$/d;p}'`
  # then remove it from the property list
  properties=`echo "$properties" | $SED -ne '/^tests\s*=\s*"""$/,/^"""$/d;p'`

  SETUP=`echo "$properties" | get_string_property 'setup'`
  CLEAN=`echo "$properties" | get_string_property 'clean'`
  NAME=`echo "$id" | tr '-' ' '`
  TCSHUPDATE=`echo "$properties" | get_string_property 'tcsh-update'`

  # generate run scripts...
  prepare_test
  # then execute them
  $WRAPPER

  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]; then
    if [ $debug -ge 1 ]; then
      echo "[OK] $suite::$id"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e /tmp/.shell.$$
        echo "" 
        echo "Output $REFER :"
        $CAT -e /tmp/.refer.$$
        echo ""
      fi
    fi
  else
    if [ $debug -ge 1 ]; then
      echo "[FAIL] $suite::$id - Check output in /tmp/test.$$/$id/" 
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.shell.$$ /tmp/test.$$/$id/mysh.out
      $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
    else
      echo "KO"
    fi
  fi
}

run_test_suite() {
  local test_file=`cat $1`

  for id in `echo "$test_file" | $SED -ne '/\[.*\]/!d;s/\[\(.*\)\]/\1/p' "$1"`; do
    local path_backup=$PATH
    run_test "$test_file" 'basic' "$id" 1
    export PATH=$path_backup
  done
}

if [ ! -f test_basic.toml ]
then
  echo "No test_basic.toml file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

if [ $# -eq 2 ]
then
  echo "Debug mode" >&2
  echo "Shell : $MYSHELL" >&2
  echo "Reference : $REFER" >&2
  echo ""
fi

if [ $# -eq 0 ]; then
  run_test_suite 'test_basic.toml'
else
  if [ $# -eq 1 ]
  then
    run_test $1 0
  else
    if [ "X$1" = "X-d" ]
    then
      run_test $2 2
    else
      run_test $1 2
    fi
  fi
fi
