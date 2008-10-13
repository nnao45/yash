temp="${TESTTMP}/redir"


echo ===== loop pipe =====

| (while read i; do
	if [ $i -lt 5 ]; then echo $((i+1)); else exit; fi
done) | { echo 0; tee "$temp"; }
cat "$temp"


echo ===== command redirection =====

cat <(echo 1)
cat <(echo 2)-
echo >(cat) 3 | cat

seq () {
	i=1
	while [ "$i" -le "$1" ]; do
		echo "$i"
		i=$((i+1))
	done
	unset i
}

seq 4 >(cat) | grep 4
grep 5 <(seq 5)
! $INVOKE $TESTEE -c '< (:)' 2>(cat>/dev/null)
echo $?


rm -f "$temp"