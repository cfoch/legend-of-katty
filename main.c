#include "lok.h"

int
main (int argc, char ** argv)
{
  GtkWidget *bag_pack_widget;
  TArray *elements;
  LokBagPack *bag_pack;


  gtk_init (&argc, &argv);

  elements = lok_element_create_elements (LOK_ELEMENT_TYPE_ARM);
  bag_pack = lok_bag_pack_new (NULL);

  lok_bag_pack_add_element (bag_pack, LOK_ELEMENT (t_array_index (elements, 0)));
  lok_bag_pack_add_element (bag_pack, LOK_ELEMENT (t_array_index (elements, 4)));
  lok_bag_pack_add_element (bag_pack, LOK_ELEMENT (t_array_index (elements, 1)));
  lok_bag_pack_add_element (bag_pack, LOK_ELEMENT (t_array_index (elements, 3)));
  lok_bag_pack_add_element (bag_pack, LOK_ELEMENT (t_array_index (elements, 5)));

  printf ("HOLA\n");
  /* LOK_DEBUG_ELEMENTS (elements); */

  bag_pack_widget = lok_bag_pack_widget_new (bag_pack);

  gtk_widget_show_all (bag_pack_widget);
  gtk_main ();

  return 0;
}
