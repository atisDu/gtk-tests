#include <gtk/gtk.h>
#include <stdlib.h>

static gchar bg_color_hex[16] = {0};
static gchar fg_color_hex[16] = {0};
static gchar border_color_hex[16] = {0};

static gchar krasa[16] = {0};

static gchar atvertais_fails[100] = {0};
static gchar komanda[180] = {0};

static void on_color_set(GtkColorButton *button, gpointer user_data) {
    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &color);
    gchar *color_hex = user_data;
    // Convert the RGBA color to a hex string
    snprintf(color_hex, 16, "#%02X%02X%02X",
            (int)(color.red * 255), (int)(color.green * 255), (int)(color.blue * 255));

    // Print out the hex color to verify
    printf("Selected color: %s\n", color_hex);
}



static void faila_apstrade (GtkFileChooserButton *button, gpointer user_data){
  
  user_data = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
  // Labs! C nevar mainīt stringu vērtības vienkārši tā ievadot, jāzimanto piemēram strcopy
  strcpy(atvertais_fails, user_data);
 
}

static void saglabat (GtkWidget *widget, gpointer data){
  g_print ("Hexis1: %s, Hexis2: %s, Hexis3 %s\n", bg_color_hex, fg_color_hex, border_color_hex);
  g_print("Ievadītā taka: %s", atvertais_fails);
  
  
  int i;
  for (i = 5; i>0 ;i--){
    
    switch (i)
    {
    case 5:
      strcpy(krasa, bg_color_hex);
    case 4:
      strcpy(krasa, fg_color_hex);
      break;
    case 3:
      strcpy(krasa, fg_color_hex);      
      break;
    case 2:
      strcpy(krasa, border_color_hex);
    case 1:
      strcpy(krasa, bg_color_hex);
    default:
      break;
    }
    
    // Šo vajag salabot
    snprintf(komanda, 180, "grep -m %d \'\"#\' %s | sed \'s/#\\([0-9a-fA-F]\\{3,7\\}\\)/%s/g\' -i %s", i, atvertais_fails, krasa, atvertais_fails);
    printf("\nkomanda: %s\ni ir %d", komanda, i);
    system(komanda);

  }

/*
#!/bin/bash

# Jauno krāsu saraksts
declare -a colors=("red" "blue" "green")

# Faila nosaukums
file="filename.txt"

# Izgūst un aizstāj krāsas
for color in "${colors[@]}"; do
  # Atrast pirmo nepārveidoto krāsu
  old_color=$(grep -o -m 1 '#[0-9a-fA-F]\{3,6\}' $file)
  
  # Ja old_color nav tukšs, aizstāt to
  if [[ ! -z "$old_color" ]]; then
    sed -i "s/$old_color/$color/" $file
  fi
done
*/


}

static void activate (GtkApplication *app, gpointer        user_data){
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *color_button;
  GtkWidget *label;
  GtkWidget *atvert_failu;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Sadirsējs 2000");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  //gtk_window_set_keep_above (GTK_WINDOW (window), 1);
  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  label = gtk_label_new ("Izvēlies bg krāsu: ");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
 



  color_button = gtk_color_button_new ();
  g_signal_connect(color_button, "color-set", G_CALLBACK(on_color_set), &bg_color_hex);
  gtk_grid_attach (GTK_GRID (grid), color_button, 1, 0, 1, 1);
  
  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */






  label = gtk_label_new ("Izvēlies fg krāsu: ");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 1, 1, 1);
  



  color_button = gtk_color_button_new ();
  gtk_grid_attach (GTK_GRID (grid), color_button, 1, 1, 1, 1);
  g_signal_connect(color_button, "color-set", G_CALLBACK(on_color_set), &fg_color_hex);

 label = gtk_label_new ("Izvēlies robežu (border) krāsu: ");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 2, 1, 1);
  



  color_button = gtk_color_button_new ();
  gtk_grid_attach (GTK_GRID (grid), color_button, 1, 2, 1, 1); 
  g_signal_connect(color_button, "color-set", G_CALLBACK(on_color_set), &border_color_hex);
  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  label = gtk_label_new ("Izvēlies CONFIG failu: ");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 3, 1, 1);

  atvert_failu = gtk_file_chooser_button_new ("taka", 0);
  gtk_grid_attach (GTK_GRID (grid), atvert_failu, 1, 3, 1, 1); 
  g_signal_connect(atvert_failu, "file-set", G_CALLBACK(faila_apstrade), &atvertais_fails);

  button = gtk_button_new_with_label ("Saglabāt");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (saglabat), "NULL");

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 2, 1);
 

  button = gtk_button_new_with_label ("Iziet bez saglabāšanas");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 2, 1);

  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.dirsejs", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
