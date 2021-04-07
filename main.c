#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

int num1_i = 0;
int num2_i = 0;
int processing_first_number = 1;
static GtkWidget *screen_text;

int operation = 0;

struct number_container {
  char *num1;
  char *num2;
};

void reset(struct number_container *numbers) 
{
  char *num1 = numbers->num1;
  char *num2 = numbers->num2;

  memset(num1, 0, 100);
  memset(num2, 0, 100);

  processing_first_number = 1;
}

void calculate(GtkWidget *calcButton, gpointer data)
{
  struct number_container *numbers = (struct number_container *) data;
  char *num1_string = numbers->num1;
  char *num2_string = numbers->num2;

  int num1 = atoi(num1_string);
  int num2 = atoi(num2_string);

  char ans[100];
  
  if (operation == 1) {
    sprintf(ans, "%d", num1 + num2);
  } else if (operation == 2) {
    sprintf(ans, "%d", num1 - num2);
  } else if (operation == 3) {
    sprintf(ans, "%d", num1 * num2);
  } else {
    sprintf(ans, "%d", num1 / num2);
  }

  num2_i = 0;
  num1_i = 0;

  gtk_label_set_text((GtkLabel *)screen_text, ans);
  reset(data);
}

void clear_input(GtkWidget *clear_button, gpointer data)
{
  processing_first_number = 1;
  num1_i = 0;
  num2_i = 0;
  reset((struct number_container *)data);
  gtk_label_set_text((GtkLabel *)screen_text, "");
}

void process_operator(GtkWidget *operator_button, gpointer data) 
{
  char operator = gtk_button_get_label((GtkButton *)operator_button)[0];
  if (operator == '+') {
    operation = 1;
  } else if (operator == '-') {
    operation = 2;
  } else if (operator == 'x') {
    operation = 3;
  } else {
    operation = 4;
  }

  if (processing_first_number) {
    processing_first_number = 0;
    num1_i = 0;
  }
}

void process_input(GtkWidget *num_button, gpointer data)
{
  if (processing_first_number) {
    char *num1 = ((struct number_container *)data)->num1;
    printf("%c", gtk_button_get_label((GtkButton *)num_button)[0]);
    printf("\n");
    num1[num1_i++] = gtk_button_get_label((GtkButton *)num_button)[0];
    gtk_label_set_text((GtkLabel *)screen_text, num1);
  } else {
    char *num2 = ((struct number_container *)data)->num2;
    num2[num2_i++] = gtk_button_get_label((GtkButton *)num_button)[0];
    gtk_label_set_text((GtkLabel *)screen_text, num2);
  }
}

void add_operator_buttons(GtkWidget *operator_grid)
{
  GtkWidget *plus = gtk_button_new_with_label("+");
  GtkWidget *minus = gtk_button_new_with_label("-");
  GtkWidget *multiply = gtk_button_new_with_label("x");
  GtkWidget *divide = gtk_button_new_with_label("/");

  g_signal_connect(plus, "clicked", G_CALLBACK(process_operator), NULL);
  g_signal_connect(minus, "clicked", G_CALLBACK(process_operator), NULL);
  g_signal_connect(multiply, "clicked", G_CALLBACK(process_operator), NULL);
  g_signal_connect(divide, "clicked", G_CALLBACK(process_operator), NULL);

  gtk_grid_attach(GTK_GRID(operator_grid), plus, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(operator_grid), minus, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(operator_grid), multiply, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(operator_grid), divide, 0, 3, 1, 1);
}
void add_num_buttons(GtkWidget* number_grid, struct number_container *numbers)
{
  GtkWidget *clear = gtk_button_new_with_label("C");
  GtkWidget *zero = gtk_button_new_with_label("0");
  GtkWidget *one = gtk_button_new_with_label("1");
  GtkWidget *two = gtk_button_new_with_label("2");
  GtkWidget *three = gtk_button_new_with_label("3");
  GtkWidget *four = gtk_button_new_with_label("4");
  GtkWidget *five = gtk_button_new_with_label("5");
  GtkWidget *six = gtk_button_new_with_label("6");
  GtkWidget *seven = gtk_button_new_with_label("7");
  GtkWidget *eight = gtk_button_new_with_label("8");
  GtkWidget *nine = gtk_button_new_with_label("9");
  GtkWidget *equal = gtk_button_new_with_label("=");

  g_signal_connect(clear, "clicked", G_CALLBACK(clear_input), numbers);
  g_signal_connect(zero, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(one, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(two, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(three, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(four, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(five, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(six, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(seven, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(eight, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(nine, "clicked", G_CALLBACK(process_input), numbers);
  g_signal_connect(equal, "clicked", G_CALLBACK(calculate), numbers);

  gtk_grid_attach(GTK_GRID(number_grid), one, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), two, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), three, 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), four, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), five, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), six, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), seven, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), eight, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), nine, 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), zero, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), clear, 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(number_grid), equal, 1, 3, 1, 1);
}

// gcc 007_gtk.c -o 007_gtk `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
  GtkWidget *window, *calculator, *number_grid, *operator_grid;
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


  calculator = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), calculator);

  // Screen Text
  screen_text = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(calculator), screen_text, 0, 0, 12, 1);

  // Number Buttons
  number_grid = gtk_grid_new();
  struct number_container *numbers = malloc(sizeof(struct number_container));
  numbers->num1 = malloc(100);
  numbers->num2 = malloc(100);

  add_num_buttons(number_grid, numbers);
  gtk_grid_attach(GTK_GRID(calculator), number_grid, 0, 1, 1, 1);

  // Operation Buttons
  operator_grid = gtk_grid_new();
  add_operator_buttons(operator_grid);
  gtk_grid_attach(GTK_GRID(calculator), operator_grid, 1, 1, 1, 1);

  GtkWidget *view2 = gtk_text_view_new();
  gtk_grid_attach(GTK_GRID(calculator), view2, 0, 2, 0, 0);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
