Prompt=(
	"echo>outfile"
	"echo >outfile"
	"echo> outfile"
	"echo > outfile"
	"echo>>outfile"
	"echo >>outfile"
	"echo>> outfile"
	"echo >> outfile"
	"echo \"this\"and' that'>> outfile"
)

for i in "${Prompt[@]}"; do
	echo
	echo "- - - - - - - - - -  - - - - -"
	echo "$i" | ./minishell
done