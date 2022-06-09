#include "tree_sitter.h"

extern VALUE mTreeSitter;

VALUE cNode;

void node_free(TSNode *node) { free(node); }

TSNode *value_to_node(VALUE self) {
  TSNode *node;

  Data_Get_Struct(self, TSNode, node);

  return node;
}

VALUE new_node(const TSNode *node) {
  TSNode *ptr = (TSNode *)malloc(sizeof(TSNode));
  memcpy(ptr, node, sizeof(TSNode));
  return Data_Wrap_Struct(cNode, NULL, node_free, ptr);
}

VALUE node_type(VALUE self) {
  TSNode *node = value_to_node(self);

  return rb_str_new_cstr(ts_node_type(*node));
}

VALUE node_symbol(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_symbol(*node));
}

VALUE node_start_byte(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_start_byte(*node));
}

VALUE node_start_point(VALUE self) {
  TSNode *node = value_to_node(self);
  TSPoint point = ts_node_start_point(*node);

  return new_point(&point);
}

VALUE node_end_byte(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_end_byte(*node));
}

VALUE node_end_point(VALUE self) {
  TSNode *node = value_to_node(self);
  TSPoint point = ts_node_end_point(*node);

  return new_point(&point);
}

VALUE node_string(VALUE self) {
  TSNode *node = value_to_node(self);

  return rb_str_new_cstr(ts_node_string(*node));
}

VALUE node_is_null(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_is_null(*node) ? Qtrue : Qfalse;
}

void init_node(void) {
  cNode = rb_define_class_under(mTreeSitter, "Node", rb_cObject);

  /* Class methods */
  rb_define_method(cNode, "type", node_type, 0);
  rb_define_method(cNode, "symbol", node_symbol, 0);
  rb_define_method(cNode, "start_byte", node_start_byte, 0);
  rb_define_method(cNode, "start_point", node_start_point, 0);
  rb_define_method(cNode, "end_byte", node_end_byte, 0);
  rb_define_method(cNode, "end_point", node_end_point, 0);
  rb_define_method(cNode, "string", node_string, 0);
  rb_define_method(cNode, "to_s", node_string, 0);
  rb_define_method(cNode, "null?", node_is_null, 0);
}
