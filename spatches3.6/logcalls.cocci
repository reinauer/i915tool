@@
type T;
identifier f;
@@
T f(...){
+fprintf(stderr, "%s\n", __func__);
...
}

