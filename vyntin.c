#include <gtk/gtk.h>
#include <vte/vte.h>

static void signal_send_line(GtkWidget *widget, gpointer term) {
	/* send line to tintin++ */
	vte_terminal_feed_child(VTE_TERMINAL(term), gtk_entry_get_text(GTK_ENTRY(widget)), -1);
	
	/* don't forget the newline */
	vte_terminal_feed_child(VTE_TERMINAL(term), "\n", -1);
	
	/* highlight last entry */
	gtk_widget_grab_focus(GTK_WIDGET(widget));
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *term;
	GtkWidget *entry;
	GtkWidget *termbox;
	GtkWidget *scrollbar;
	
	gtk_init(&argc, &argv);
	
	/* setup main window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "vtin");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	/* boxes are to put things in */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	termbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	
	/* create the terminal widget */
	char **term_argv = NULL;
	term = vte_terminal_new();
	
	/* remove ability for focus on term */
	gtk_widget_set_can_focus(GTK_WIDGET(term), FALSE);
	
	/* tt++ must be in $PATH */
	/*g_shell_parse_argv("tt++", NULL, &term_argv, NULL);*/
	g_shell_parse_argv("/home/rascul/.local/bin/runlyntin -c /home/rascul/.lyntin.ini", NULL, &term_argv, NULL);
	vte_terminal_fork_command_full(VTE_TERMINAL(term), VTE_PTY_DEFAULT, NULL, term_argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	
	/* i would prefer to just disable the damn cursor, but alas, that doesn't seem to be something easy
	 * however, i might be able to use an ansi escape sequence to do it, or just color the cursor black
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
	
	/* need more scrollbar
	 * thanks to xjuan and chpe in #gtk+ on irc.gnome.org for helping me figure this out */
	scrollbar = gtk_scrollbar_new(GTK_ORIENTATION_VERTICAL, gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(term)));
	
	/* now we need the input widget */
	entry = gtk_entry_new();
	
	/* signal to send stuff to tintin++ when enter is pressed */
	g_signal_connect_object(entry, "activate", G_CALLBACK(signal_send_line), term, 0);
	
	/* pack up */
	gtk_box_pack_start(GTK_BOX(termbox), term, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(termbox), scrollbar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), termbox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);
	
	/* load up */
	gtk_widget_show_all(window);
	
	/* and go home */
	gtk_main();
	return 0;
}
