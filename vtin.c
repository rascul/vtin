#include <gtk/gtk.h>
#include <vte/vte.h>

static void print_hello(GtkWidget *widget, gpointer data) {
	g_print("hello world\n");
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *term;
 	GtkWidget *input;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "vtin");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	char **term_argv = NULL;
	term = vte_terminal_new();
	g_shell_parse_argv("tt++", NULL, &term_argv, NULL);
	vte_terminal_fork_command_full(VTE_TERMINAL(term), VTE_PTY_DEFAULT, NULL, term_argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	gtk_box_pack_start(GTK_BOX(box), term, TRUE, TRUE, 0);
	
	input = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(box), input, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), box);
	
	gtk_widget_show(input);
	gtk_widget_show(term);
	gtk_widget_show(box);	
	gtk_widget_show(window);
	
	gtk_main();
	return 0;
}
