function emitar(){
	print("struct registers *reglist[] = {\n")
	for (el in names){
		printf("\t[%s] = (struct registers *)struct_%s,\n", names[el], names[el])
	}
	print("\t[0x100000] = NULL,\n};\n")
}
function structstart(instruct, name) {
	if (instruct == 1) print "\t{NULL, 0},\n};\n"
	printf( "struct registers struct_%s[]={\n", name)
	names[ix++] = name
}

function structmember(line){
	split(line, els)
	print "\t{\"", els[2], "\"," els[2], "},"
}

function structs(){
	print "struct registers { char *name; int value; };"
}
	
BEGIN {print "/* generated don't edit */\n#include \"final/i915_reg.h\"";structs();instruct = 0; ix = 0; emitting = 0; }
END {if (instruct == 1) print "};"; emitar();}

/^#define.*0x[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][\t ]/{emitting=1; split($0, regname);  structstart(instruct, regname[2]); instruct = 1;next}
/^#define.*0x[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]$/{if (emitting == 0) next; split($0, regname);  structstart(instruct, regname[2]); instruct = 1;next}
/^#define.*(pipe)/{next;}
/^#define.*(plane)/{next;}
/^#define.*(x)/{next;}
/^#define.*(n)/{next;}
/^#define.*(bit)/{next;}
/^#define/{if (emitting == 0) next; if (instruct == 0) next; structmember($0);next}

#  awk -f buildregs.awk  < final/i915_reg.h |less > buildregs.c
# you almost certainly need to massage it further. Sorry. 