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
CHMOD=`which chmod`
CP=`which cp`
DIFF=`which diff`
TEST=`which test`
TPUT=`which tput`
DATE=`which date`
BC=`which bc`
PRINTF=`which printf`

# Check if stdout is a terminal
if test -t 1; then
  # Check the number of colors supported
  ncolors=`$TPUT colors`

  if test -n "$ncolors" && test $ncolors -ge 8; then
    NC="$($TPUT sgr0)"
    BOLD="$(tput bold)"
    RED="$($TPUT setaf 1)"
    GREEN="$($TPUT setaf 2)"
    BLUE="$($TPUT setaf 4)"
  fi
fi

# Gets the value of string properties with the first argument as names
get_string_property() {
  $SED -ne "s/^$1\s*=\s*\(.*\)\s*$/\1/p" | $SED -e "s/^\(\"\(.*\)\"\)\|\('\(.*\)'\)$/\2\4/"
}

# Displays the data of the test $id
display_test() {
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

  $CHMOD 755 $testfn
  $CHMOD 755 $runnerfn
}

# Parameters:
# 1 - test file contents
# 2 - test suite
# 3 - test id
run_test() {
  local test_file=$1
  local suite=$2
  local id=$3

  local properties=`echo "$test_file" | $SED -ne  "/^\[$id\]\$/,/^\[.*\]$/{/^\[.*\]$/d;p}"`

  # extract 'tests' multiline property first...
  TESTS=`echo "$properties" | $SED -ne '/^tests\s*=\s*"""$/,/^"""$/{/^tests\s*=\s*"""$/d;/^"""$/d;p}'`
  # then remove it from the property list
  properties=`echo "$properties" | $SED -ne '/^tests\s*=\s*"""$/,/^"""$/d;p'`

  SETUP=`echo "$properties" | get_string_property 'setup'`
  CLEAN=`echo "$properties" | get_string_property 'clean'`
  NAME=`echo "$id"`
  TCSHUPDATE=`echo "$properties" | get_string_property 'tcsh-update'`

  # generate run scripts...
  prepare_test
  local start=$($DATE +%s.%N)
  # then execute them
  $WRAPPER
  
  # measure time elapsed
  local end=$($DATE +%s.%N)
  local test_time=$(echo $end - $start | $BC | xargs $PRINTF %.2fs)

  if diff -U3 /tmp/.refer.$$ /tmp/.shell.$$ > /tmp/.diff.$$; then
    echo -e "[${GREEN}PASS${NC}] $suite::$id ($test_time)"
    return 0
  else
    local description=`echo "$properties" | get_string_property 'description'`

    echo -e "[${RED}FAIL${NC}] $suite::$id ($test_time)" 
    [ ! -z "$description" ] && echo -e "[${BLUE}----${NC}] Description: $description"
    echo -e "[${BLUE}----${NC}] Outputs differ:"
    while IFS= read -r line; do
      echo -e "[${BLUE}----${NC}] $line"
    done < /tmp/.diff.$$
    return 1
  fi
}

run_test_suite() {
  local test_file=`$CAT $1`
  local suite_properties=`echo "$test_file" | $SED -ne '1,/^\[.*\]$/{/^\[.*\]$/d;p}'`
  local suite=`echo "$suite_properties" | get_string_property 'suite'`
  local tested=0
  local passing=0
  local failing=0

  for id in `echo "$test_file" | $SED -ne '/\[.*\]/!d;s/\[\(.*\)\]/\1/p' "$1"`; do
    local path_backup=$PATH

    if run_test "$test_file" "$suite" "$id" 1; then
      passing=$(($passing + 1))
    else
      failing=$(($failing + 1))
    fi
    tested=$(($tested + 1))
    export PATH=$path_backup
  done
  echo -e "[${BLUE}====${NC}] ${BOLD}Synthesis: Tested:${NC} ${BLUE}${tested}${NC} | ${BOLD}Passing:${NC} ${GREEN}${passing}${NC} | ${BOLD}Failing:${NC} ${RED}${failing}${NC}"
}

if [ ! -f test_basic.toml ]; then
  echo "No test_basic.toml file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]; then
  echo "$MYSHELL not found" >&2
  exit 1
fi

run_test_suite 'test_basic.toml'
