function emitar(){
	print("struct registers *drmreglist[] = {\n")
	for (el in names){
	    if (names[el] ~ /DP_TRAINING_LANE._SET/){
		printf("\t[%s] = (struct registers *)struct_%s,\n", names[el], "DP_TRAINING_LANE3_SET")
	    } else {
		printf("\t[%s] = (struct registers *)struct_%s,\n", names[el], names[el])
	    }
	}
	print("\t[0x100000] = NULL,\n};\n")
}
function structstart(instruct, name) {
	if (instruct == 1) print "\t{NULL, 0},\n};\n"
	printf( "struct registers struct_%s[]={\n", name)
	names[ix++] = name
}

function structmember(line, mask){
	split(line, els)
	print "\t{\"", els[3], "\"," els[3], ", ", mask, "},"
}

function structmembermask(line){
	split(line, els)
	print "\t{\"\",", els[3], "},"
}

function structs(){
	# define in buildregs.awk
	print "//struct registers { char *name; unsigned long value; unsigned long mask; };"
}
	
BEGIN {print "/* generated don't edit */\n#include \"final/i915_reg.h\"";structs();instruct = 0; ix = 0; emitting = 0; }
END {if (instruct == 1) print "};"; emitar();}

/^#define.*0x[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]$/{emitting=1; split($0, regname);  structstart(instruct, regname[2]); instruct = 1;next}
/^#define.*(pipe)/{next;}
/^#define.*(plane)/{next;}
/^#define.*(x)/{next;}
/^#define.*(n)/{next;}
/^#define.*(bit)/{next;}
/^# define.*MASK/{if (emitting == 0) next; if (instruct == 0) next; next}
/^# define.*SHIFT/{if (emitting == 0) next; if (instruct == 0) next; next}
/^# define.*DP_TRAINING_PATTERN/{if (emitting == 0) next; if (instruct == 0) next; structmember($0, "DP_TRAINING_PATTERN_MASK");next}
/^# define.*DP_TRAIN.*SWING/{if (emitting == 0) next; if (instruct == 0) next; structmember($0, "DP_TRAIN_VOLTAGE_SWING_MASK");next}
/^# define.*DP_TRAIN.*EMPHASIS.*/{if (emitting == 0) next; if (instruct == 0) next; structmember($0, "DP_TRAIN_PRE_EMPHASIS_MASK");next}
/^# define.*DP_LINK_BW_/{if (emitting == 0) next; if (instruct == 0) next; structmember($0, "0x1a");next}
/^# define/{if (emitting == 0) next; if (instruct == 0) next; structmember($0, "0xffffffff");next}

# This one is for the dp helper junk. It's a pattern of
# define someting 0x three x digits
# registers have no space between the # and the define; other things do. That tells you when to emit.
# then patterns.
# ending with an empty line. 
#  awk -f buildregs.awk  < final/drm_dp_helper.h |less > buildregs.c
# you almost certainly need to massage it further. Sorry. 
# and if you're smarter than me you'll get rid of other hackery ...
