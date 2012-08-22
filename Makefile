# Use this makefile to build the targets you want
build3.4:
	make -f Makefile3.4

transform3.4:
	sh transform3.4

alltags: 
	ctags *.[ch] final/*.[ch]
	etags.emacs *.[ch] final/*.[ch]

clean:
	rm -f *.o video probe gttdump dumpscreen gttbreak gttset
	rm -f edid timegttsetup ports panel dpms
	rm -f g6reset cli fillscreen

moreclean:  clean
	rm -f final/* per-file-changes/* tmp/* tags

superclean: moreclean
	rm -f inputs/*
