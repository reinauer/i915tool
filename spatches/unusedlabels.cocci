@jumped_to@
identifier l;
position p;
@@
goto l;
...
l@p:


@@
identifier l;
position p != jumped_to.p;
@@
-l@p:

