#include <gtk/gtk.h>
#include <vte/vte.h>

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *term;
	GtkWidget *termscroll;
	GtkWidget *input;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "vtin");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	
	/* create the terminal widget */
	char **term_argv = NULL;
	term = vte_terminal_new();
	
	/* tt++ must be in $PATH */
	g_shell_parse_argv("tt++", NULL, &term_argv, NULL);
	vte_terminal_fork_command_full(VTE_TERMINAL(term), VTE_PTY_DEFAULT, NULL, term_argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	
	/* i would prefer to just disable the damn cursor, but alas, that doesn't seem to be something easy
	 * valid cursor shapes:
	 * VTE_CURSOR_SHAPE_IBEAM
	 * VTE_CURSOR_SHAPE_UNDERLINE
	 * VTE_CURSOR_SHAPE_BLOCK */
	vte_terminal_set_cursor_shape(VTE_TERMINAL(term), VTE_CURSOR_SHAPE_IBEAM);
	
	/* also, turn off cursor blinking */
	vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(term), VTE_CURSOR_BLINK_OFF);
	
	/* -1 so scrollback buffer will hold everything 
	 * if memory is an issue, setting this to a finite value (or 0 to disable it) might be useful */
	vte_terminal_set_scrollback_lines(VTE_TERMINAL(term), -1);
	
	/* need more scrollbar */
	termscroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(termscroll), term);
	
	gtk_box_pack_start(GTK_BOX(box), termscroll, TRUE, TRUE, 0);
	
	/* now we need the input widget */
	input = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(box), input, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), box);
	
	gtk_widget_show(termscroll);
	gtk_widget_show(input);
	gtk_widget_show(term);
	gtk_widget_show(box);
	gtk_widget_show(window);
	
	gtk_main();
	return 0;
}
