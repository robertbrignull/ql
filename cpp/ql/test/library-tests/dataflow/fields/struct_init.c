void sink(void *o);
void *user_input(void);

struct AB {
  void *a;
  void *b;
};

struct Outer {
  struct AB nestedAB;
  struct AB *pointerAB;
};

void absink(struct AB *ab) {
  sink(ab->a); // flow (three sources)
  sink(ab->b); // no flow
}

int struct_init(void) {
  struct AB ab = { user_input(), 0 };

  sink(ab.a); // flow
  sink(ab.b); // no flow
  absink(&ab);

  struct Outer outer = {
    { user_input(), 0 },
    &ab,
  };

  sink(outer.nestedAB.a); // flow
  sink(outer.nestedAB.b); // no flow
  sink(outer.pointerAB->a); // flow
  sink(outer.pointerAB->b); // no flow

  absink(&outer.nestedAB);
}

int struct_init2(void) {
  struct AB ab = { user_input(), 0 };
  struct Outer outer = {
    { user_input(), 0 },
    &ab,
  };

  absink(outer.pointerAB);
}
