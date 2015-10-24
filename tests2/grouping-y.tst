# grouping-y.tst: yash-specific test of grouping commands

test_oE 'effect of empty subshell'
echo 1
()
echo 2
__IN__
1
2
__OUT__

test_OE -e 11 'exit status of empty subshell'
sh -c 'exit 11'
()
__IN__

test_oE 'effect of empty brace grouping'
echo 1
{ }
echo 2
__IN__
1
2
__OUT__

test_OE -e 13 'exit status of empty brace grouping'
sh -c 'exit 13'
{ }
__IN__

(
posix="true"

test_Oe -e 2 'empty subshell (single line)'
()
__IN__
syntax error: commands are missing between `(' and `)'
__ERR__
#'`'`

test_Oe -e 2 'empty subshell (multi-line)'
(
)
__IN__
syntax error: commands are missing between `(' and `)'
__ERR__
#'`'`

test_Oe -e 2 'empty brace grouping (single line)'
{ }
__IN__
syntax error: commands are missing between `{' and `}'
__ERR__
#'`'`

test_Oe -e 2 'empty brace grouping (multi-line)'
{
}
__IN__
syntax error: commands are missing between `{' and `}'
__ERR__
#'`'`

)

test_Oe -e 2 'unpaired )'
)
__IN__
syntax error: encountered `)' without a matching `('
__ERR__
#'`'`

test_Oe -e 2 'unpaired }'
}
__IN__
syntax error: encountered `}' without a matching `{'
__ERR__
#'`'`

test_Oe -e 2 'unclosed subshell'
(
echo foo
__IN__
syntax error: `)' is missing
__ERR__
#'`

test_Oe -e 2 'unclosed brace grouping'
{
echo foo
__IN__
syntax error: `}' is missing
__ERR__
#'`

# vim: set ft=sh ts=8 sts=4 sw=4 noet:
