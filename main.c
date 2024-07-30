/*
 * LAZY_CAT:
 * The simple terminal and easy to use when you run at lazy Momments :) "lazyCat".
 *
 * @author(s) : AMZYEI(Amin Azimi)
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/unistd.h>
#include<vte/vte.h>
#include<gtk/gtk.h>
#define NOTIFY_SEND "notify-send "

GtkWidget *win,
*terminal,
*first_box_terminal,
*second_box_terminal,
*third_box_terminal,
*exec_btn_INSTALL_KEY,
*exec_label,
*exec_entry;

static void child_ready(VteTerminal *terminal, GPid pid, GError *error, gpointer user_data)
{
    if (!terminal) return;
    if (pid == -1) gtk_main_quit();
}

/* go to INSTALL_KEY */
static void install_DEB(void){
    const gchar *entry = gtk_entry_get_text(GTK_ENTRY(exec_entry));
    const char *installKey = "pkexec apt install -y ";
    const int len_of_installKey = strlen(installKey);
    const int  len_of_entry = gtk_entry_get_text_length(GTK_ENTRY(exec_entry));
    const int finally_length = len_of_entry+len_of_installKey+1;

    char *cmd_merge_to_exec = (char*)malloc(finally_length*sizeof(char));
    strcpy(cmd_merge_to_exec, installKey);
    strcat(cmd_merge_to_exec, entry);

    /* two qoutation marks & one more for "\0" = 3 */
    int finally_len_notify = strlen(entry) + strlen(NOTIFY_SEND) + 5;

    // assembeling the cmd_done_notify
    char *cmd_done_notify = (char*)malloc(finally_len_notify * sizeof(char));
    strcpy(cmd_done_notify, NOTIFY_SEND);
    strcat(cmd_done_notify, "\"");
    strcat(cmd_done_notify, entry);
    strcat(cmd_done_notify, " installed !");
    strcat(cmd_done_notify, "\"");

    if(system(cmd_merge_to_exec) == 0){
      system(cmd_done_notify);
    }else{
        system("notify-send \"Package not Found\" ");
    }


}


// int main initialization


int main(int argc, char *argv[])
{

    // client home address
    char *home_addr = getenv("HOME");
    char *logo_addr = "/.lazyCat/icon/lazyCat.png";

    int home_addr_len = strlen(home_addr);
    int logo_addr_len = strlen(logo_addr);
    int finally_len = home_addr_len + logo_addr_len+1;

    /* icon path  */

    char *path = (char*)malloc(finally_len*sizeof(char));
    strcpy(path, home_addr);
    strcat(path, logo_addr);

    /* create all widget */



    /* initialize GTK, the window and the terminal */
    gtk_init(&argc, &argv);

    // terminal instance and configuration
    terminal = vte_terminal_new();
    vte_terminal_set_font_scale(VTE_TERMINAL(terminal), 1.3);

    // window instance
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(win), "lazyCat");

    gtk_window_set_icon_from_file(GTK_WINDOW(win), path, NULL);

    /* go to all standard directories GUI  */

    exec_btn_INSTALL_KEY = gtk_button_new_with_label("INSTALL_KEY");


    exec_label = gtk_label_new("Enter your exec : ");

    exec_entry = gtk_entry_new();

    /* main boxes of terminal  */
    first_box_terminal = gtk_box_new(TRUE, 0);
    second_box_terminal = gtk_box_new(FALSE, 0);
    third_box_terminal = gtk_box_new(TRUE, 0);

    /* Start a new shell */
    gchar **envp = g_get_environ();
    gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL };
    g_strfreev(envp);
    vte_terminal_spawn_async(VTE_TERMINAL(terminal),
        VTE_PTY_DEFAULT,
        home_addr,         /* working directory  */
        command,      /* command */
        NULL,         /* environment */
        2,            /* spawn flags */
        NULL, NULL,   /* child setup */
        NULL,         /* child pid */
        -1,           /* timeout */
        NULL,         /* cancellable */
        child_ready,  /* callback */
        NULL);        /* user_data */


    /* Connect some signals */

    g_signal_connect(win, "destroy", gtk_main_quit, NULL);

    g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);

    g_signal_connect(G_OBJECT(exec_btn_INSTALL_KEY),
                    "clicked",
                    G_CALLBACK(install_DEB),
                    (gpointer)win
                  );


    /*
     * add  terminal to the first box (Main Box)
     */
    gtk_box_pack_start(GTK_BOX(first_box_terminal), terminal, TRUE, TRUE, 0 );

   /*
    * combine two box (first_box_terminal and second_box_terminal)
    */

    gtk_box_pack_end(GTK_BOX(first_box_terminal), second_box_terminal, FALSE, FALSE, 0);

   /*
    * add third box to the first box (Main Box)
    */

    gtk_box_pack_end(GTK_BOX(first_box_terminal), third_box_terminal, FALSE, FALSE, 0);



    /*
    * exec exec button for INSTALL_KEY  (GUI)
    */
    gtk_box_pack_end(GTK_BOX(second_box_terminal), exec_btn_INSTALL_KEY, TRUE, TRUE, 4);



    ////////////////////////////////third box/////////////////////////////////////////
    /*
     * add search label to the third box
     */

     gtk_box_pack_start(GTK_BOX(third_box_terminal), exec_label, FALSE, FALSE, 4);
    gtk_box_pack_start(GTK_BOX(third_box_terminal), exec_entry, FALSE, FALSE, 4);

    gtk_container_add(GTK_CONTAINER(win), first_box_terminal);
    const char *text_exec = gtk_entry_get_text(GTK_ENTRY(exec_entry));


    /*
     * render all
     */

    // exec entry get text


    free(path);

    gtk_widget_show_all(win);

    gtk_main();

    return 0;
}
